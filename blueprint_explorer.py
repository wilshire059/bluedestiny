"""
Debug script to discover Blueprint property names in UE5.7
Run this first to see what properties are available.
"""

import unreal
import json
import os

def list_all_properties(obj, obj_name="Object"):
    """List all accessible properties on an object."""
    props = []
    
    # Get the object's class
    try:
        obj_class = obj.get_class()
        print(f"\n=== {obj_name} (Class: {obj_class.get_name()}) ===")
    except:
        print(f"\n=== {obj_name} ===")
    
    # List all attributes
    for attr in dir(obj):
        if not attr.startswith('_'):
            try:
                value = getattr(obj, attr)
                if callable(value):
                    props.append(f"  [METHOD] {attr}()")
                else:
                    value_str = str(value)[:80] if value is not None else "None"
                    props.append(f"  [PROP] {attr} = {value_str}")
            except Exception as e:
                props.append(f"  [ERROR] {attr}: {str(e)[:50]}")
    
    return props

def explore_blueprint(blueprint_path):
    """Explore what's available on a Blueprint object."""
    
    print(f"\n{'='*60}")
    print(f"EXPLORING: {blueprint_path}")
    print(f"{'='*60}")
    
    # Load the blueprint
    bp_asset = unreal.EditorAssetLibrary.load_asset(blueprint_path)
    
    if not bp_asset:
        print(f"ERROR: Could not load blueprint: {blueprint_path}")
        return
    
    print(f"\nLoaded: {bp_asset.get_name()}")
    print(f"Type: {type(bp_asset)}")
    print(f"Class: {bp_asset.get_class().get_name()}")
    
    # List blueprint properties
    bp_props = list_all_properties(bp_asset, "Blueprint")
    
    # Write to file for easier reading
    output = []
    output.append(f"Blueprint: {blueprint_path}")
    output.append(f"Type: {type(bp_asset)}")
    output.append(f"Class: {bp_asset.get_class().get_name()}")
    output.append("")
    output.append("=== ALL BLUEPRINT PROPERTIES/METHODS ===")
    output.extend(bp_props)
    
    # Save to file
    filepath = r"c:\temp\blueprint_properties.txt"
    with open(filepath, 'w') as f:
        f.write('\n'.join(output))
    
    print(f"\nWrote property list to: {filepath}")
    print(f"Total items found: {len(bp_props)}")
    
    # Print some key ones to console
    print("\n=== KEY PROPERTIES (look for 'class', 'component', 'construction') ===")
    for prop in bp_props:
        prop_lower = prop.lower()
        if any(keyword in prop_lower for keyword in ['class', 'component', 'construction', 'script', 'scs', 'node', 'template']):
            print(prop)


# Run exploration
explore_blueprint("/Game/SoulslikeFramework/Blueprints/_WorldActors/LevelDesign/B_Destructible")

print("\nDone! Check c:\\temp\\blueprint_properties.txt for full list.")
