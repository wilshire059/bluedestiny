"""
Test script to verify collection type extraction from JSON works correctly.
Tests with AC_ActionManager to confirm AvailableActions becomes TMap.
"""
import json

# Load JSON
with open('Saved/NodeToCode/ExportedBlueprints/AC_ActionManager.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

class_defaults = data.get('classDefaults', {})
print(f"Found {len(class_defaults)} properties in classDefaults\\n")

# Extract properties using the new method
properties = {}
for graph in data.get('graphs', []):
    for node in graph.get('nodes', []):
        if node.get('nodeType') not in ['VariableGet', 'VariableSet']:
            continue
            
        var_name = node.get('memberName', '')
        if not var_name or var_name not in class_defaults:
            continue
            
        # Get type from output pins
        for pin in node.get('outputPins', []):
            pin_name = pin.get('name', '')
            if pin_name == var_name or (not pin_name and node.get('nodeType') == 'VariableGet'):
                prop_type = pin.get('type', '')
                sub_type = pin.get('subType', '')
                is_array = pin.get('bIsArray', False)
                is_map = pin.get('bIsMap', False)
                is_set = pin.get('bIsSet', False)
                
                # Build C++ type
                base_type = ""
                if prop_type == "Struct":
                    base_type = f"F{sub_type}" if sub_type and not sub_type.startswith("F") else sub_type
                elif prop_type == "Object":
                    if sub_type and sub_type != "self":
                        if sub_type.startswith(("B_", "PDA_")):
                            base_type = f"A{sub_type}*" if sub_type.startswith("B_") and not sub_type.startswith("A") else f"U{sub_type}*" if sub_type.startswith("PDA_") and not sub_type.startswith("U") else f"{sub_type}*"
                        else:
                            base_type = f"U{sub_type}*" if not sub_type.startswith("U") else f"{sub_type}*"
                    else:
                        base_type = "UObject*"
                else:
                    base_type = prop_type
                
                # Apply collection wrappers
                final_type = base_type
                if is_map:
                    key_type_raw = pin.get('keyType', 'Int')
                    key_typename = pin.get('keyTypeName', '')
                    key_cpp = "int32"
                    if key_type_raw == "Struct" and key_typename:
                        key_cpp = f"F{key_typename}" if not key_typename.startswith("F") else key_typename
                    elif key_type_raw == "Name":
                        key_cpp = "FName"
                    final_type = f"TMap<{key_cpp}, {base_type}>"
                elif is_set:
                    final_type = f"TSet<{base_type}>"
                elif is_array:
                    final_type = f"TArray<{base_type}>"
                
                properties[var_name] = {
                    'cpp_type': final_type,
                    'is_array': is_array,
                    'is_map': is_map,
                    'is_set': is_set,
                    'base_type': base_type
                }
                break

print("=== Extracted Properties ===\\n")
for prop_name, prop_info in sorted(properties.items()):
    flags = []
    if prop_info['is_map']: flags.append("MAP")
    if prop_info['is_array']: flags.append("ARRAY")
    if prop_info['is_set']: flags.append("SET")
    flag_str = f" [{','.join(flags)}]" if flags else ""
    print(f"{prop_name:25s} → {prop_info['cpp_type']}{flag_str}")

print(f"\\n=== Key Properties to Check ===")
print(f"AvailableActions: {properties.get('AvailableActions', {}).get('cpp_type', 'NOT FOUND')}")
print(f"    Expected: TMap<FGameplayTag, AB_Action*>")
print(f"ActionAssetsCache: {properties.get('ActionAssetsCache', {}).get('cpp_type', 'NOT FOUND')}")  
print(f"    Expected: TArray<UPDA_Action*>")
print(f"ActionTagsCache: {properties.get('ActionTagsCache', {}).get('cpp_type', 'NOT FOUND')}")
print(f"    Expected: TArray<FGameplayTag>")
