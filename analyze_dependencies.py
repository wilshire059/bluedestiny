import json
import os
import re

EXPORT_DIR = r"C:\scripts\BlueDestiny\Saved\NodeToCode\ExportedBlueprints"

def analyze_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        try:
            data = json.load(f)
        except json.JSONDecodeError:
            print(f"Error decoding {filepath}")
            return None

    filename = os.path.basename(filepath)
    name = data.get('metadata', {}).get('name', filename.replace('.json', ''))
    
    # Infer type
    bp_type = "Unknown"
    if filename.startswith("E_"): bp_type = "Enum"
    elif filename.startswith("F") or filename.startswith("Struct_"): bp_type = "Struct" # Heuristic
    elif filename.startswith("BPI_"): bp_type = "Interface"
    elif filename.startswith("AC_"): bp_type = "ActorComponent"
    elif filename.startswith("B_"): bp_type = "Blueprint"
    elif filename.startswith("W_"): bp_type = "Widget"
    
    # Structs and Enums defined inside
    internal_structs = [s['name'] for s in data.get('structs', [])]
    internal_enums = [e['name'] for e in data.get('enums', [])]
    
    # Variables (Inferred from classDefaults)
    variables = {}
    class_defaults = data.get('classDefaults', {})
    for key, value in class_defaults.items():
        inferred_type = "Unknown"
        if isinstance(value, str):
            if value.lower() in ["true", "false"]: inferred_type = "bool"
            elif re.match(r"^-?\d+(\.\d+)?$", value): inferred_type = "double"
            elif value.startswith("/Script/Engine.Sound"): inferred_type = "object/SoundBase"
            elif value.startswith("/Script/Engine.StaticMesh"): inferred_type = "object/StaticMesh"
            elif value.startswith("/Script/Engine.SkeletalMesh"): inferred_type = "object/SkeletalMesh"
            elif value.startswith("/Script/Engine.ParticleSystem"): inferred_type = "object/ParticleSystem"
            elif value.startswith("/Script/Niagara.NiagaraSystem"): inferred_type = "object/NiagaraSystem"
            elif "Vector" in value and "X=" in value: inferred_type = "struct/Vector"
            elif "Rotator" in value and "Pitch=" in value: inferred_type = "struct/Rotator"
            elif "(" in value and "=" in value: inferred_type = "struct/UnknownStruct" # Complex struct
        
        # Heuristic based on name
        if inferred_type == "Unknown" or inferred_type == "struct/UnknownStruct":
            if key == "ItemInfo": inferred_type = "struct/FItemInfo"
            elif key == "StatInfo": inferred_type = "struct/FStatInfo"
            elif key == "EquipmentDetails": inferred_type = "struct/FEquipmentInfo"
            elif key == "CraftingDetails": inferred_type = "struct/FCraftingInfo"
            elif key == "LockInfo": inferred_type = "struct/FDoorLockInfo"
            
        variables[key] = inferred_type

    # Refine variable types from VariableGet nodes
    graphs = data.get('graphs', [])
    for graph in graphs:
        nodes = graph.get('nodes', [])
        for node in nodes:
            if node.get('nodeType') == 'VariableGet':
                var_name = node.get('name') # This is the pin name usually, memberName is the var name
                member_name = node.get('memberName')
                member_parent = node.get('memberParent')
                
                if member_name in variables:
                    # memberParent might be "bool", "int", "struct/FMyStruct", "object/MyClass"
                    variables[member_name] = member_parent

    # Parent Class Inference
    # We look for "ParentClass" key if it exists (unlikely based on exploration)
    # Or we look for CallFunction nodes where memberParent is NOT self and NOT a library
    parent_class = "Actor" # Default
    if bp_type == "ActorComponent": parent_class = "ActorComponent"
    if bp_type == "Widget": parent_class = "UserWidget"
    
    # Check if we can find a better parent
    # This is hard without a global map.
    
    return {
        "name": name,
        "type": bp_type,
        "internal_structs": internal_structs,
        "internal_enums": internal_enums,
        "variables": variables,
        "parent_class": parent_class # Placeholder
    }

def main():
    results = {}
    if not os.path.exists(EXPORT_DIR):
        print(f"Directory not found: {EXPORT_DIR}")
        return

    for filename in os.listdir(EXPORT_DIR):
        if filename.endswith(".json"):
            filepath = os.path.join(EXPORT_DIR, filename)
            analysis = analyze_file(filepath)
            if analysis:
                results[analysis['name']] = analysis

    # Post-process to infer parents?
    # For now, just dump the results for a few key files
    
    with open('analysis_output.json', 'w', encoding='utf-8') as f:
        json.dump(results, f, indent=2)

if __name__ == "__main__":
    main()
