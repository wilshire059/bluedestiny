"""
Comprehensive Blueprint Component Exporter for Unreal Engine 5.7
================================================================
Exports component settings, hierarchies, and type-specific data 
that NodeToCode JSON doesn't capture.

Features:
- Component parent/child hierarchy
- Support for different Blueprint types (Actor, AnimBP, Widget, etc.)
- Batch export all Blueprints to project folder
- Exports to: [ProjectDir]/Saved/BlueprintComponentExports/

Run in Unreal Editor: File > Execute Python Script
"""

import unreal
import json
import os
from datetime import datetime

# ============================================================================
# CONFIGURATION - Scanning entire SoulslikeFramework folder for all Blueprints
# ============================================================================
BLUEPRINT_FOLDER = "/Game/SoulslikeFramework"  # Scans ALL subfolders recursively
OUTPUT_DIR = None  # Will be set to BlueDestiny's Saved folder

# ============================================================================
# PROPERTY LISTS FOR DIFFERENT COMPONENT TYPES
# ============================================================================

# Common properties for all primitive components
PRIMITIVE_COMPONENT_PROPS = [
    "collision_enabled",
    "collision_profile_name",
    "collision_object_type",
    "generate_overlap_events",
    "can_ever_affect_navigation",
    "visible",
    "hidden_in_game",
    "cast_shadow",
    "simulate_physics",
    "mass_in_kg",
    "linear_damping",
    "angular_damping",
    "enable_gravity",
]

# Geometry Collection / Chaos physics
GEOMETRY_COLLECTION_PROPS = [
    "collision_profile_per_level",
    "enable_damage_from_collision",
    "notify_breaks",
    "notify_collisions",
    "notify_removals",
    "notify_trailing",
    "rest_collection",
    "object_type",
    "damage_threshold",
    "damage_model",
    "cluster_group_index",
    "max_cluster_level",
    "initial_velocity_type",
    "initial_linear_velocity",
    "initial_angular_velocity",
]

# Skeletal Mesh Component (for characters/animations)
SKELETAL_MESH_PROPS = [
    "skeletal_mesh",
    "anim_class",
    "animation_mode",
    "kinematic_bones_update_type",
]

# Static Mesh Component
STATIC_MESH_PROPS = [
    "static_mesh",
    "override_materials",
]

# Audio Component
AUDIO_COMPONENT_PROPS = [
    "sound",
    "attenuation_settings",
    "sound_class_override",
    "auto_activate",
    "volume_multiplier",
    "pitch_multiplier",
]

# Capsule/Sphere/Box Components
SHAPE_COMPONENT_PROPS = [
    "capsule_half_height",
    "capsule_radius",
    "sphere_radius",
    "box_extent",
]

# Character Movement
CHARACTER_MOVEMENT_PROPS = [
    "max_walk_speed",
    "max_walk_speed_crouched",
    "jump_z_velocity",
    "air_control",
    "gravity_scale",
    "max_acceleration",
    "braking_deceleration_walking",
    "ground_friction",
    "rotation_rate",
]

# Widget Component
WIDGET_COMPONENT_PROPS = [
    "widget_class",
    "draw_size",
    "pivot",
    "widget_space",
]

# Camera Component
CAMERA_COMPONENT_PROPS = [
    "field_of_view",
    "ortho_width",
    "projection_mode",
    "post_process_blend_weight",
]

# Spring Arm Component
SPRING_ARM_PROPS = [
    "target_arm_length",
    "socket_offset",
    "target_offset",
    "enable_camera_lag",
    "camera_lag_speed",
    "enable_camera_rotation_lag",
    "camera_rotation_lag_speed",
    "inherit_pitch",
    "inherit_yaw",
    "inherit_roll",
    "do_collision_test",
]

# Niagara Component
NIAGARA_COMPONENT_PROPS = [
    "asset",
    "auto_activate",
    "auto_destroy",
]

# ============================================================================
# HELPER FUNCTIONS
# ============================================================================

def get_output_dir():
    """Get the output directory - hardcoded to BlueDestiny for AI access."""
    return r"C:\scripts\BlueDestiny\Saved\BlueprintComponentExports"

def serialize_value(value):
    """Convert a UE value to JSON-serializable format."""
    if value is None:
        return None
    if isinstance(value, (bool, int, float, str)):
        return value
    if isinstance(value, unreal.Name):
        return str(value)
    if isinstance(value, unreal.Vector):
        return {"x": value.x, "y": value.y, "z": value.z}
    if isinstance(value, unreal.Rotator):
        return {"pitch": value.pitch, "yaw": value.yaw, "roll": value.roll}
    if isinstance(value, unreal.Transform):
        return {
            "location": serialize_value(value.translation),
            "rotation": serialize_value(value.rotation.rotator()),
            "scale": serialize_value(value.scale3d)
        }
    if hasattr(value, '__iter__') and not isinstance(value, str):
        return [serialize_value(item) for item in value]
    if hasattr(value, 'get_path_name'):
        return value.get_path_name()
    if hasattr(value, 'get_name'):
        return value.get_name()
    return str(value)

def get_props_safe(obj, prop_names):
    """Safely get multiple properties from an object."""
    props = {}
    for prop_name in prop_names:
        try:
            # Try direct attribute access first
            if hasattr(obj, prop_name):
                value = getattr(obj, prop_name)
                if value is not None:
                    props[prop_name] = serialize_value(value)
        except:
            pass
        
        # Also try get_editor_property
        if prop_name not in props:
            try:
                value = obj.get_editor_property(prop_name)
                if value is not None:
                    props[prop_name] = serialize_value(value)
            except:
                pass
    
    return props

def get_component_props(component):
    """Get properties based on component class."""
    comp_class = component.get_class().get_name()
    props = {"_class": comp_class}
    
    # Always get primitive component props for primitives
    if isinstance(component, unreal.PrimitiveComponent):
        props.update(get_props_safe(component, PRIMITIVE_COMPONENT_PROPS))
    
    # Type-specific properties
    if "GeometryCollection" in comp_class:
        props.update(get_props_safe(component, GEOMETRY_COLLECTION_PROPS))
    elif "SkeletalMesh" in comp_class:
        props.update(get_props_safe(component, SKELETAL_MESH_PROPS))
    elif "StaticMesh" in comp_class:
        props.update(get_props_safe(component, STATIC_MESH_PROPS))
    elif "Audio" in comp_class:
        props.update(get_props_safe(component, AUDIO_COMPONENT_PROPS))
    elif "Capsule" in comp_class or "Sphere" in comp_class or "Box" in comp_class:
        props.update(get_props_safe(component, SHAPE_COMPONENT_PROPS))
    elif "CharacterMovement" in comp_class:
        props.update(get_props_safe(component, CHARACTER_MOVEMENT_PROPS))
    elif "Widget" in comp_class:
        props.update(get_props_safe(component, WIDGET_COMPONENT_PROPS))
    elif "Camera" in comp_class:
        props.update(get_props_safe(component, CAMERA_COMPONENT_PROPS))
    elif "SpringArm" in comp_class:
        props.update(get_props_safe(component, SPRING_ARM_PROPS))
    elif "Niagara" in comp_class:
        props.update(get_props_safe(component, NIAGARA_COMPONENT_PROPS))
    
    # Get transform for scene components
    if isinstance(component, unreal.SceneComponent):
        try:
            props["relative_transform"] = serialize_value(component.get_relative_transform())
        except:
            pass
    
    return props

def build_component_hierarchy(components):
    """Build parent/child hierarchy of components."""
    hierarchy = []
    component_map = {}
    
    # First, create entries for all components
    for comp in components:
        entry = {
            "ComponentName": comp.get_name(),
            "ComponentClass": comp.get_class().get_name(),
            "Children": [],
            "Properties": get_component_props(comp)
        }
        component_map[comp] = entry
    
    # Now build hierarchy
    root_components = []
    for comp in components:
        parent = None
        if isinstance(comp, unreal.SceneComponent):
            try:
                parent = comp.get_attach_parent()
            except:
                pass
        
        if parent and parent in component_map:
            component_map[parent]["Children"].append(component_map[comp])
        else:
            root_components.append(component_map[comp])
    
    return root_components

# ============================================================================
# BLUEPRINT TYPE HANDLERS
# ============================================================================

def export_animation_blueprint_data(bp_asset):
    """Export Animation Blueprint specific data."""
    data = {"AnimBlueprintData": {}}
    
    try:
        # Get target skeleton
        skeleton = bp_asset.get_editor_property("target_skeleton")
        if skeleton:
            data["AnimBlueprintData"]["TargetSkeleton"] = skeleton.get_path_name()
    except:
        pass
    
    try:
        # Get anim graph
        data["AnimBlueprintData"]["HasAnimGraph"] = True
    except:
        pass
    
    return data

def export_widget_blueprint_data(bp_asset):
    """Export Widget Blueprint specific data."""
    data = {"WidgetBlueprintData": {}}
    
    try:
        # Widget tree would require special handling
        data["WidgetBlueprintData"]["Type"] = "UserWidget"
    except:
        pass
    
    return data

# ============================================================================
# MAIN EXPORT FUNCTIONS
# ============================================================================

def export_blueprint(blueprint_path, output_dir=None):
    """Export a single Blueprint's component settings with hierarchy."""
    
    if output_dir is None:
        output_dir = get_output_dir()
    
    # Load blueprint
    bp_asset = unreal.EditorAssetLibrary.load_asset(blueprint_path)
    if not bp_asset:
        unreal.log_error(f"Could not load: {blueprint_path}")
        return None
    
    blueprint_name = bp_asset.get_name()
    bp_class_name = bp_asset.get_class().get_name()
    
    unreal.log(f"Exporting: {blueprint_name} ({bp_class_name})")
    
    export_data = {
        "BlueprintPath": blueprint_path,
        "BlueprintName": blueprint_name,
        "BlueprintType": bp_class_name,
        "ExportTime": datetime.now().isoformat(),
        "ParentClass": "",
        "ComponentHierarchy": []
    }
    
    # Handle different Blueprint types
    if "AnimBlueprint" in bp_class_name:
        export_data.update(export_animation_blueprint_data(bp_asset))
        # Anim BPs don't have actor components in the same way
        
    elif "WidgetBlueprint" in bp_class_name:
        export_data.update(export_widget_blueprint_data(bp_asset))
        # Widget BPs use a different structure
        
    else:
        # Actor-based Blueprints - spawn and get components
        try:
            bp_class = bp_asset.generated_class()
            if bp_class:
                export_data["ParentClass"] = bp_class.get_name()
                
                # Spawn temporary actor
                spawn_loc = unreal.Vector(0, 0, -100000)
                actor = unreal.EditorLevelLibrary.spawn_actor_from_class(bp_class, spawn_loc)
                
                if actor:
                    # Get all components and build hierarchy
                    components = actor.get_components_by_class(unreal.ActorComponent)
                    export_data["ComponentHierarchy"] = build_component_hierarchy(components)
                    export_data["TotalComponents"] = len(components)
                    
                    # Clean up
                    actor.destroy_actor()
                    
                    unreal.log(f"  Found {len(components)} components")
        except Exception as e:
            unreal.log_warning(f"  Error getting components: {str(e)}")
    
    # Save to file
    os.makedirs(output_dir, exist_ok=True)
    
    # Create subfolder based on blueprint path
    rel_path = blueprint_path.replace("/Game/", "").replace("/", "_")
    filename = f"{rel_path}.json"
    filepath = os.path.join(output_dir, filename)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        json.dump(export_data, f, indent=2, default=str)
    
    return filepath

def export_all_blueprints(folder_path=None, output_dir=None):
    """Export ALL Blueprints in a folder recursively."""
    
    if folder_path is None:
        folder_path = BLUEPRINT_FOLDER
    if output_dir is None:
        output_dir = get_output_dir()
    
    unreal.log(f"\n{'='*60}")
    unreal.log(f"BATCH EXPORT: {folder_path}")
    unreal.log(f"Output: {output_dir}")
    unreal.log(f"{'='*60}\n")
    
    # Get all assets in folder
    assets = unreal.EditorAssetLibrary.list_assets(folder_path, recursive=True, include_folder=False)
    
    unreal.log(f"Found {len(assets)} total assets in {folder_path}")
    
    exported = []
    errors = []
    skipped = 0
    
    total = len(assets)
    for i, asset_path in enumerate(assets):
        try:
            asset_data = unreal.EditorAssetLibrary.find_asset_data(asset_path)
            
            # Use asset_class_path (non-deprecated) to check if it's a Blueprint
            try:
                class_path = asset_data.asset_class_path
                class_name = str(class_path.asset_name) if class_path else ""
            except:
                # Fallback to deprecated asset_class if needed
                class_name = str(asset_data.asset_class)
            
            # Ensure it's a string for comparison
            class_name = str(class_name)
            
            # Check if it's any type of Blueprint
            is_blueprint = any(bp_type in class_name for bp_type in [
                "Blueprint", 
                "AnimBlueprint",
                "WidgetBlueprint",
                "BehaviorTree",
                "BlackboardData"
            ])
            
            if not is_blueprint:
                skipped += 1
                continue
            
            # Remove the object name suffix for loading
            bp_path = asset_path.split('.')[0]
            
            unreal.log(f"[{i+1}/{total}] Exporting: {bp_path} ({class_name})")
            
            result = export_blueprint(bp_path, output_dir)
            if result:
                exported.append(result)
            else:
                errors.append(bp_path)
                
        except Exception as e:
            errors.append(f"{asset_path}: {str(e)}")
    
    unreal.log(f"\nSkipped {skipped} non-Blueprint assets")
    
    # Create summary file
    summary = {
        "ExportTime": datetime.now().isoformat(),
        "SourceFolder": folder_path,
        "TotalExported": len(exported),
        "TotalErrors": len(errors),
        "ExportedFiles": exported,
        "Errors": errors
    }
    
    summary_path = os.path.join(output_dir, "_export_summary.json")
    os.makedirs(output_dir, exist_ok=True)
    with open(summary_path, 'w', encoding='utf-8') as f:
        json.dump(summary, f, indent=2)
    
    unreal.log(f"\n{'='*60}")
    unreal.log(f"EXPORT COMPLETE")
    unreal.log(f"Exported: {len(exported)} blueprints")
    unreal.log(f"Errors: {len(errors)}")
    unreal.log(f"Output: {output_dir}")
    unreal.log(f"{'='*60}\n")
    
    return summary

# ============================================================================
# RUN EXPORT
# ============================================================================

# To export a single blueprint:
# export_blueprint("/Game/SoulslikeFramework/Blueprints/_WorldActors/LevelDesign/B_Destructible")

# To export ALL blueprints in the configured folder:
summary = export_all_blueprints()

print(f"\nExport complete!")
print(f"Exported {summary['TotalExported']} blueprints to:")
print(f"  {get_output_dir()}")
print(f"\nYou can now access these files directly for C++ conversion reference.")
