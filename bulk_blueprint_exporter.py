import unreal
import os
import json
import time
from datetime import datetime

OUTPUT_DIR = r"C:\scripts\BlueDestiny\Saved\BlueprintComponentExports"

def serialize_value(value):
    if value is None: return None
    if isinstance(value, (bool, int, float, str)): return value
    if hasattr(value, 'x') and hasattr(value, 'y') and hasattr(value, 'z'):
        return {"x": value.x, "y": value.y, "z": value.z}
    if hasattr(value, 'pitch') and hasattr(value, 'yaw') and hasattr(value, 'roll'):
        return {"pitch": value.pitch, "yaw": value.yaw, "roll": value.roll}
    if hasattr(value, 'r') and hasattr(value, 'g') and hasattr(value, 'b'):
        return {"r": value.r, "g": value.g, "b": value.b, "a": getattr(value, 'a', 1.0)}
    if isinstance(value, (list, tuple)):
        return [serialize_value(v) for v in value]
    if hasattr(value, 'name') and hasattr(value, 'value'): # Enum
        return f"{type(value).__name__}.{value.name}"
    if hasattr(value, 'get_path_name'):
        return value.get_path_name()
    return str(value)

def get_properties_from_uobject(uobject):
    """Reflect properties from an object instance or CDO."""
    if not uobject: return {}
    properties = {}
    uclass = uobject.get_class()
    properties["_class"] = uclass.get_name() if uclass else "Unknown"
    
    # Python API: properties accessible via get_editor_property
    if hasattr(uclass, 'get_editor_property_names'):
        for prop in uclass.get_editor_property_names():
            try:
                # Skip circular or heavy properties if needed
                val = uobject.get_editor_property(prop)
                properties[prop] = serialize_value(val)
            except: 
                pass
            
    return properties

def safe_is_child_of(klass, parent_class):
    if not klass: return False
    try:
        # Standard check
        return klass.is_child_of(parent_class)
    except AttributeError:
        # Fallback: Cast using unreal.Class
        try:
            return unreal.Class.cast(klass).is_child_of(parent_class)
        except:
            pass
    return False

def export_blueprint(bp_asset_data, output_dir):
    bp_path = bp_asset_data.package_name
    bp_name = bp_asset_data.asset_name
    
    try:
        # Load asset
        bp_asset = unreal.EditorAssetLibrary.load_asset(bp_path)
        if not bp_asset: 
            unreal.log_warning(f"Skipping {bp_name}: Failed to load asset")
            return "LoadFailed"
        
        # Get Generated Class
        generated_class = None
        if hasattr(bp_asset, "generated_class"):
            generated_class = bp_asset.generated_class()
        
        if not generated_class:
            # Maybe it's a BlueprintGeneratedClass asset directly?
            if isinstance(bp_asset, unreal.BlueprintGeneratedClass):
                generated_class = bp_asset
            else:
                 unreal.log_warning(f"Skipping {bp_name}: No generated class")
                 return "NoGeneratedClass"

        data = {
            "BlueprintPath": str(bp_path),
            "BlueprintName": str(bp_name),
            "ExportTime": datetime.now().isoformat(),
            "Type": "Unknown",
            "ActorProperties": {},
            "Components": []
        }

        # Strategy Check
        is_actor = False
        try:
            is_actor = unreal.EditorAssetLibrary.do_assets_exist([bp_path]) and safe_is_child_of(generated_class, unreal.Actor)
        except:
             pass

        if is_actor:
            data["Type"] = "Actor"
            # Spawn Actor to get full component hierarchy
            world = unreal.EditorLevelLibrary.get_editor_world()
            spawn_loc = unreal.Vector(-100000, -100000, -100000)
            actor = None
            try:
                actor = unreal.EditorLevelLibrary.spawn_actor_from_class(generated_class, spawn_loc)
            except Exception as e:
                unreal.log_warning(f"Actor Spawn Failed for {bp_name}: {e}. Retrying with CDO.")
            
            if actor:
                try:
                    data["ActorProperties"] = get_properties_from_uobject(actor)
                    
                    # Components
                    if hasattr(actor, "get_components_by_class"):
                        comps = actor.get_components_by_class(unreal.ActorComponent)
                        for comp in comps:
                            c_data = {
                                "Name": comp.get_name(),
                                "Class": comp.get_class().get_name(),
                                "Properties": get_properties_from_uobject(comp)
                            }
                            if isinstance(comp, unreal.SceneComponent):
                                parent = comp.get_attach_parent()
                                c_data["AttachedTo"] = parent.get_name() if parent else None
                            data["Components"].append(c_data)
                finally:
                    actor.destroy_actor()
            else:
                # Actor spawn failed, fallback to CDO
                cdo = unreal.get_default_object(generated_class)
                data["ActorProperties"] = get_properties_from_uobject(cdo)
                data["Note"] = "Exported from CDO (Spawn Failed)"

        else:
            # Not an Actor (Widget, Component, Object, AnimInstance)
            # Use CDO
            data["Type"] = "Object/Other"
            if safe_is_child_of(generated_class, unreal.UserWidget): data["Type"] = "Widget"
            elif safe_is_child_of(generated_class, unreal.ActorComponent): data["Type"] = "Component"
            
            cdo = unreal.get_default_object(generated_class)
            data["ActorProperties"] = get_properties_from_uobject(cdo)
            data["Note"] = "Exported from CDO"

        # Write to file
        filename = f"{bp_name}_COMPLETE.json"
        filepath = os.path.join(output_dir, filename)
        with open(filepath, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2)
            
        return "Success"

    except Exception as e:
        unreal.log_error(f"CRITICAL ERROR exporting {bp_name}: {e}")
        return f"Error: {e}"

def run_bulk_export():
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    
    # Broaden filter to include Utilities and ControlRigs
    filter = unreal.ARFilter(
        class_names=[
            "Blueprint", 
            "BlueprintGeneratedClass", 
            "WidgetBlueprint", 
            "AnimBlueprint",
            "EditorUtilityBlueprint",
            "EditorUtilityWidgetBlueprint",
            "ControlRigBlueprint"
        ],
        package_paths=["/Game"],
        recursive_paths=True
    )
    
    assets = asset_registry.get_assets(filter)
    unreal.log(f"Found {len(assets)} potential assets. Starting export...")
    
    summary = {"Success": 0, "Failed": 0, "NoGeneratedClass": 0, "LoadFailed": 0}
    
    with unreal.ScopedSlowTask(len(assets), "Exporting Blueprints...") as task:
        task.make_dialog(True)
        
        for i, asset in enumerate(assets):
            if task.should_cancel(): break
            
            bp_name = asset.asset_name
            task.enter_progress_frame(1, f"[{i}/{len(assets)}] {bp_name}")
            
            result = export_blueprint(asset, OUTPUT_DIR)
            
            if result == "Success":
                summary["Success"] += 1
            else:
                summary["Failed"] += 1
                unreal.log_warning(f"Failed {bp_name}: {result}")
            
            # Print periodic status
            if i % 20 == 0:
                unreal.log(f"Progress: {i}/{len(assets)} - Succeeded: {summary['Success']}")

    unreal.log(f"Bulk Export Complete. Summary: {summary}")

if __name__ == "__main__":
    run_bulk_export()
