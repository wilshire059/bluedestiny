"""
Complete Component Property Dumper
Dumps ALL properties from a Blueprint's components for migration reference.
"""

import unreal
import json
import os
from datetime import datetime

OUTPUT_DIR = r"C:\scripts\BlueDestiny\Saved\BlueprintComponentExports"

def get_all_properties(component):
    """Get ALL accessible properties from a component, not just a predefined list."""
    properties = {}
    
    if not component:
        return properties
    
    component_class = component.get_class()
    properties["_class"] = component_class.get_name() if component_class else "Unknown"
    
    # Get all property names from the component class
    try:
        # Try to enumerate all properties
        for prop in component_class.get_editor_property_names() if hasattr(component_class, 'get_editor_property_names') else []:
            try:
                value = component.get_editor_property(prop)
                properties[prop] = serialize_value(value)
            except:
                pass
    except:
        pass
    
    # Also try common property access methods
    property_getters = [
        # Transform
        ("relative_location", lambda c: serialize_vector(c.get_relative_location()) if hasattr(c, 'get_relative_location') else None),
        ("relative_rotation", lambda c: serialize_rotator(c.get_relative_rotation()) if hasattr(c, 'get_relative_rotation') else None),
        ("relative_scale", lambda c: serialize_vector(c.get_relative_scale3d()) if hasattr(c, 'get_relative_scale3d') else None),
        ("world_location", lambda c: serialize_vector(c.get_world_location()) if hasattr(c, 'get_world_location') else None),
        
        # Visibility/Rendering
        ("visible", lambda c: c.is_visible() if hasattr(c, 'is_visible') else None),
        ("hidden_in_game", lambda c: c.get_editor_property('hidden_in_game') if hasattr(c, 'get_editor_property') else None),
        ("cast_shadow", lambda c: c.get_editor_property('cast_shadow') if hasattr(c, 'get_editor_property') else None),
        
        # Static Mesh specific
        ("static_mesh", lambda c: str(c.get_editor_property('static_mesh')) if hasattr(c, 'get_editor_property') else None),
        
        # Light specific
        ("intensity", lambda c: c.get_editor_property('intensity') if hasattr(c, 'get_editor_property') else None),
        ("attenuation_radius", lambda c: c.get_editor_property('attenuation_radius') if hasattr(c, 'get_editor_property') else None),
        ("light_color", lambda c: serialize_color(c.get_editor_property('light_color')) if hasattr(c, 'get_editor_property') else None),
        ("cast_shadows", lambda c: c.get_editor_property('cast_shadows') if hasattr(c, 'get_editor_property') else None),
        ("source_radius", lambda c: c.get_editor_property('source_radius') if hasattr(c, 'get_editor_property') else None),
        ("soft_source_radius", lambda c: c.get_editor_property('soft_source_radius') if hasattr(c, 'get_editor_property') else None),
        ("source_length", lambda c: c.get_editor_property('source_length') if hasattr(c, 'get_editor_property') else None),
        
        # Niagara specific
        ("asset", lambda c: str(c.get_editor_property('asset')) if hasattr(c, 'get_editor_property') else None),
        ("auto_activate", lambda c: c.get_editor_property('auto_activate') if hasattr(c, 'get_editor_property') else None),
    ]
    
    for prop_name, getter in property_getters:
        if prop_name not in properties:
            try:
                value = getter(component)
                if value is not None:
                    properties[prop_name] = value
            except:
                pass
    
    return properties

def serialize_value(value):
    """Convert any value to JSON-serializable format."""
    if value is None:
        return None
    
    # Basic types
    if isinstance(value, (bool, int, float, str)):
        return value
    
    # Unreal types
    type_name = type(value).__name__
    
    if hasattr(value, 'x') and hasattr(value, 'y') and hasattr(value, 'z'):
        return serialize_vector(value)
    
    if hasattr(value, 'pitch') and hasattr(value, 'yaw') and hasattr(value, 'roll'):
        return serialize_rotator(value)
    
    if hasattr(value, 'r') and hasattr(value, 'g') and hasattr(value, 'b'):
        return serialize_color(value)
    
    # Arrays/Lists
    if isinstance(value, (list, tuple)):
        return [serialize_value(v) for v in value]
    
    # Enums
    if hasattr(value, 'name') and hasattr(value, 'value'):
        return f"{type_name}.{value.name}"
    
    # Objects
    if hasattr(value, 'get_path_name'):
        return value.get_path_name()
    
    # Fallback
    return str(value)

def serialize_vector(vec):
    """Serialize a vector to dict."""
    if vec is None:
        return None
    return {"x": vec.x, "y": vec.y, "z": vec.z}

def serialize_rotator(rot):
    """Serialize a rotator to dict."""
    if rot is None:
        return None
    return {"pitch": rot.pitch, "yaw": rot.yaw, "roll": rot.roll}

def serialize_color(color):
    """Serialize a color to dict."""
    if color is None:
        return None
    if hasattr(color, 'r'):
        return {"r": color.r, "g": color.g, "b": color.b, "a": getattr(color, 'a', 1.0)}
    return str(color)

def get_all_editor_properties(component):
    """Try to get ALL editor properties using reflection."""
    properties = {}
    
    if not component:
        return properties
    
    # Get the class
    comp_class = component.get_class()
    class_name = comp_class.get_name() if comp_class else "Unknown"
    properties["_class"] = class_name
    
    # Common properties to try for all components
    common_props = [
        # Scene Component
        "relative_location", "relative_rotation", "relative_scale3d",
        "absolute_location", "absolute_rotation", "absolute_scale",
        "mobility", "detail_mode", "hidden_in_game", "visible",
        
        # Primitive Component  
        "collision_enabled", "collision_profile_name", "collision_object_type",
        "generate_overlap_events", "can_ever_affect_navigation",
        "cast_shadow", "cast_static_shadow", "cast_dynamic_shadow",
        "affect_dynamic_indirect_lighting", "affect_distance_field_lighting",
        "cast_far_shadow", "cast_inset_shadow", "cast_cinematic_shadow",
        "cast_hidden_shadow", "cast_shadow_as_two_sided",
        "simulate_physics", "mass_in_kg", "linear_damping", "angular_damping",
        "enable_gravity", "physics_volume_changed_delegate_deprecated",
        "override_materials",
        
        # Static Mesh
        "static_mesh", "override_wireframe_color", "wireframe_color_override",
        "force_mip_streaming", "override_min_lod",
        "evaluate_world_position_offset",
        
        # Light Component
        "intensity", "light_color", "attenuation_radius",
        "cast_shadows", "cast_static_shadows", "cast_dynamic_shadows",
        "affect_translucent_lighting", "transmission",
        "use_temperature", "temperature", "indirect_lighting_intensity",
        "volumetric_scattering_intensity", "samples_per_pixel",
        "source_radius", "soft_source_radius", "source_length",
        "inverse_squared_falloff", "use_inverse_squared_falloff",
        
        # Point Light
        "light_falloff_exponent",
        
        # Niagara
        "asset", "auto_activate", "auto_destroy", "pooling_method",
        "force_solo", "allow_scalability", "preview_lod_distance",
        
        # Billboard  
        "sprite", "screen_size",
    ]
    
    for prop in common_props:
        try:
            value = component.get_editor_property(prop)
            serialized = serialize_value(value)
            if serialized is not None:
                properties[prop] = serialized
        except:
            pass
    
    return properties

def export_complete_component_data(blueprint_path, output_path=None):
    """Export complete component data for a single blueprint."""
    if output_path is None:
        output_path = OUTPUT_DIR
    
    os.makedirs(output_path, exist_ok=True)
    
    # Load the blueprint
    bp_asset = unreal.EditorAssetLibrary.load_asset(blueprint_path)
    if not bp_asset:
        unreal.log_error(f"Failed to load: {blueprint_path}")
        return None
    
    bp_name = bp_asset.get_name()
    unreal.log(f"Exporting complete data for: {bp_name}")
    
    # Get generated class
    generated_class = bp_asset.generated_class()
    if not generated_class:
        unreal.log_error(f"No generated class for: {bp_name}")
        return None
    
    # Spawn temporary actor to get component instances
    world = unreal.EditorLevelLibrary.get_editor_world()
    spawn_location = unreal.Vector(-100000, -100000, -100000)
    
    try:
        actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
            generated_class, spawn_location)
    except Exception as e:
        unreal.log_error(f"Cannot spawn actor for {bp_name}: {e}")
        return None
    
    if not actor:
        unreal.log_error(f"Failed to spawn: {bp_name}")
        return None
    
    try:
        components = actor.get_components_by_class(unreal.ActorComponent)
        
        # Get parent class name safely
        parent_class_name = "Actor"
        try:
            if hasattr(generated_class, 'get_super_class'):
                super_class = generated_class.get_super_class()
                if super_class:
                    parent_class_name = super_class.get_name()
        except:
            pass
        
        export_data = {
            "BlueprintPath": blueprint_path,
            "BlueprintName": bp_name,
            "ExportTime": datetime.now().isoformat(),
            "ParentClass": parent_class_name,
            "ActorProperties": get_all_properties(actor),
            "Components": []
        }
        
        for comp in components:
            comp_data = {
                "Name": comp.get_name(),
                "Class": comp.get_class().get_name() if comp.get_class() else "Unknown",
                "Properties": get_all_editor_properties(comp)
            }
            
            # Get attachment info for scene components
            if isinstance(comp, unreal.SceneComponent):
                parent = comp.get_attach_parent()
                comp_data["AttachedTo"] = parent.get_name() if parent else None
                
                # Get relative transform via editor properties
                try:
                    rel_loc = comp.get_editor_property('relative_location')
                    rel_rot = comp.get_editor_property('relative_rotation')
                    rel_scale = comp.get_editor_property('relative_scale3d')
                    comp_data["RelativeTransform"] = {
                        "Location": serialize_vector(rel_loc) if rel_loc else {"x": 0, "y": 0, "z": 0},
                        "Rotation": serialize_rotator(rel_rot) if rel_rot else {"pitch": 0, "yaw": 0, "roll": 0}, 
                        "Scale": serialize_vector(rel_scale) if rel_scale else {"x": 1, "y": 1, "z": 1}
                    }
                except:
                    comp_data["RelativeTransform"] = None
            
            export_data["Components"].append(comp_data)
        
        # Save to file
        filename = f"{bp_name}_COMPLETE.json"
        filepath = os.path.join(output_path, filename)
        
        with open(filepath, 'w', encoding='utf-8') as f:
            json.dump(export_data, f, indent=2)
        
        unreal.log(f"Exported: {filepath}")
        return filepath
        
    finally:
        # Clean up spawned actor
        if actor:
            actor.destroy_actor()

# Run for B_Door
if __name__ == "__main__":
    result = export_complete_component_data("/Game/SoulslikeFramework/Blueprints/_WorldActors/Interactables/B_Door")
    if result:
        unreal.log(f"SUCCESS: {result}")
    else:
        unreal.log_error("FAILED to export B_Door")
