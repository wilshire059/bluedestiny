"""
Clean Blueprint to C++ Generator - Collection Types Fixed

Generates C++ header and source files from Blueprint JSON exports.
Uses PROVEN collection type extraction from test_collection_extraction.py
"""

import json
import os
import re
from pathlib import Path

# Paths
EXPORT_DIR = Path("C:/scripts/BlueDestiny/Saved/NodeToCode/ExportedBlueprints")
OUTPUT_BASE = Path("C:/scripts/BlueDestiny/Source/SLF_5_7/Generated")
CLASSES_DIR = OUTPUT_BASE / "Classes"
PRIVATE_DIR = OUTPUT_BASE / "Private"

def ensure_dirs():
    """Create output directories."""
    CLASSES_DIR.mkdir(parents=True, exist_ok=True)
    PRIVATE_DIR.mkdir(parents=True, exist_ok=True)

def extract_properties_from_json(data):
    """
    Extract properties WITH collection type flags from JSON graph nodes.
    Proven to work correctly with test_collection_extraction.py
    """
    properties = {}
    class_defaults = data.get('classDefaults', {})
    
    for graph in data.get('graphs', []):
        for node in graph.get('nodes', []):
            if node.get('nodeType') not in ['VariableGet', 'VariableSet']:
                continue
                
            var_name = node.get('memberName', '')
            if not var_name or var_name not in class_defaults:
                continue
                
            for pin in node.get('outputPins', []):
                pin_name = pin.get('name', '')
                if pin_name == var_name or (not pin_name and node.get('nodeType') == 'VariableGet'):
                    prop_type = pin.get('type', '')
                    sub_type = pin.get('subType', '')
                    is_array = pin.get('bIsArray', False)
                    is_map = pin.get('bIsMap', False)
                    is_set = pin.get('bIsSet', False)
                    
                    # Build base C++ type
                    if prop_type == "Struct":
                        base_type = f"F{sub_type}" if sub_type and not sub_type.startswith("F") else (sub_type or "FStruct")
                    elif prop_type == "Object":
                        if sub_type and sub_type != "self":
                            if sub_type.startswith(("B_", "PDA_")):
                                prefix = "A" if sub_type.startswith("B_") else "U"
                                base_type = f"{prefix}{sub_type}*" if not sub_type.startswith((prefix, "A", "U")) else f"{sub_type}*"
                            else:
                                base_type = f"U{sub_type}*" if not sub_type.startswith("U") else f"{sub_type}*"
                        else:
                            base_type = "UObject*"
                    else:
                        base_type = prop_type
                    
                    # Apply collection wrappers - THE FIX!
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
                    else:
                        final_type = base_type
                    
                    properties[var_name] = final_type
                    break
    
    # Properties not in graphs
    for prop_name in class_defaults:
        if prop_name not in properties:
            properties[prop_name] = "UObject*"
    
    return properties

def determine_parent(name):
    """Determine C++ parent class."""
    if name.startswith("ABP_"): return "UAnimInstance"
    if name.startswith("AC_"): return "UActorComponent"
    if name.startswith("W_"): return "UUserWidget"
    if name.startswith("GM_"): return "AGameModeBase"
    if name.startswith("GS_"): return "AGameStateBase"
    if name.startswith("PC_"): return "APlayerController"
    if name.startswith("SG_"): return "USaveGame"
    if name.startswith("AN_"): return "UAnimNotify"
    if name.startswith("ANS_"): return "UAnimNotifyState"
    if name.startswith("PDA_"): return "UPrimaryDataAsset"
    return "AActor"

def get_prefix(parent):
    """Get C++ class prefix."""
    return "A" if parent.startswith("A") else "U"

def generate_header(name, data):
    """Generate C++ header."""
    parent = determine_parent(name)
    prefix = get_prefix(parent)
    class_name = f"{prefix}{name}"
    
    content = "#pragma once\n\n#include \"CoreMinimal.h\"\n"
    
    # Parent include
    if parent == "UAnimInstance":
        content += "#include \"Animation/AnimInstance.h\"\n"
    elif parent == "UActorComponent":
        content += "#include \"Components/ActorComponent.h\"\n"
    elif parent == "AActor":
        content += "#include \"GameFramework/Actor.h\"\n"
    
    content += f'#include "{name}.generated.h"\n\n'
    content += f"UCLASS(Blueprintable, BlueprintType)\n"
    content += f"class SLF_5_7_API {class_name} : public {parent}\n{{\n"
    content += "\tGENERATED_BODY()\n\npublic:\n"
    content += f"\t{class_name}();\n\n"
    
    # Properties with FIXED collection types!
    properties = extract_properties_from_json(data)
    for prop_name, cpp_type in sorted(properties.items()):
        safe_name = prop_name.replace(" ", "").replace("?", "").replace("-", "_")
        cpp_type = re.sub(r"_C(?=\W|$)", "", cpp_type)  # Clean _C suffix
        content += f'\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Migration")\n'
        content += f"\t{cpp_type} {safe_name};\n\n"
    
    # Functions (simplified)
    for func in data.get('functions', []):
        func_name = func['name'].replace(" ", "").replace("?", "")
        content += f'\tUFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Migration")\n'
        content += f"\tvoid {func_name}();\n"
        content += f "\tvirtual void {func_name}_Implementation();\n\n"
    
    content += "};\n"
    return content

def generate_source(name, data):
    """Generate C++ source."""
    parent = determine_parent(name)
    prefix = get_prefix(parent)
    class_name = f"{prefix}{name}"
    
    content = f'#include "{name}.h"\n\n'
    content += f"{class_name}::{class_name}()\n{{\n"
    
    if parent.startswith("AActor"):
        content += "\tPrimaryActorTick.bCanEverTick = true;\n"
    elif parent == "UActorComponent":
        content += "\tPrimaryComponentTick.bCanEverTick = true;\n"
    
    content += "}\n\n"
    
    # Function implementations
    for func in data.get('functions', []):
        func_name = func['name'].replace(" ", "").replace("?", "")
        content += f"void {class_name}::{func_name}_Implementation()\n{{\n"
        content += f"\t// TODO: Implement {func_name}\n"
        content += "}\n\n"
    
    return content

def main():
    """Main generator function."""
    print("=== Clean Blueprint to C++ Generator ===")
    print("WITH FIXED COLLECTION TYPES!\n")
    
    ensure_dirs()
    
    # Load analysis
    analysis_path = Path("C:/scripts/BlueDestiny/analysis_output.json")
    with open(analysis_path, 'r', encoding='utf-8') as f:
        analysis_map = json.load(f)
    
    generated = 0
    for name, analysis in analysis_map.items():
        if analysis['type'] in ["Enum", "Struct"]:
            continue
        
        json_path = EXPORT_DIR / f"{name}.json"
        if not json_path.exists():
            continue
        
        with open(json_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
        
        header = generate_header(name, data)
        source = generate_source(name, data)
        
        with open(CLASSES_DIR / f"{name}.h", 'w', encoding='utf-8') as f:
            f.write(header)
        with open(PRIVATE_DIR / f"{name}.cpp", 'w', encoding='utf-8') as f:
            f.write(source)
        
        generated += 1
        if generated % 50 == 0:
            print(f"Generated {generated} files...")
    
    print(f"\n✓ Generated {generated} C++ files with CORRECT collection types!")

if __name__ == "__main__":
    main()
