"""
Blueprint to C++ Class Generator - Fixed Version

Generates C++ header and source files from Blueprint JSON exports.
NOW CORRECTLY HANDLES COLLECTION TYPES (TArray, TMap, TSet)!
"""

import json
import os
import re
from pathlib import Path

EXPORT_DIR = r"C:\scripts\BlueDestiny\Saved\NodeToCode\ExportedBlueprints"
OUTPUT_BASE = r"C:\scripts\BlueDestiny\Source\SLF_5_7\Generated"
CLASSES_DIR = os.path.join(OUTPUT_BASE, "Classes")
PRIVATE_DIR = os.path.join(OUTPUT_BASE, "Private")

# Parent class overrides
PARENT_CLASS_OVERRIDES = {
    "B_Soulslike_Enemy_Guard": "AB_Soulslike_Enemy",
    "B_Soulslike_Enemy_Showcase": "AB_Soulslike_Enemy",
    "B_Soulslike_NPC": "AB_Soulslike_Character",
    "B_Soulslike_NPC_ShowcaseGuide": "AB_Soulslike_NPC",
    "B_Soulslike_NPC_ShowcaseVendor": "AB_Soulslike_NPC",
}

def ensure_dirs():
    os.makedirs(CLASSES_DIR, exist_ok=True)
    os.makedirs(PRIVATE_DIR, exist_ok=True)

def extract_properties_from_json(data):
    """
    Extract property types WITH collection flags from JSON graph nodes.
    Returns dict: {property_name: cpp_type_string}
    """
    properties = {}
    class_defaults = data.get('classDefaults', {})
    
    # Find VariableGet/Set nodes in graphs
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
                    
                    # Convert JSON type to C++
                    base_type = convert_type(prop_type, sub_type)
                    
                    # Apply collection wrappers
                    if is_map:
                        key_type = convert_key_type(pin.get('keyType', 'Int'), pin.get('keyTypeName', ''))
                        final_type = f"TMap<{key_type}, {base_type}>"
                    elif is_set:
                        final_type = f"TSet<{base_type}>"
                    elif is_array:
                        final_type = f"TArray<{base_type}>"
                    else:
                        final_type = base_type
                    
                    properties[var_name] = final_type
                    break
    
    # For properties not in graphs
    for prop_name in class_defaults:
        if prop_name not in properties:
            properties[prop_name] = "UObject*"
    
    return properties

def convert_type(prop_type, sub_type):
    """Convert JSON type to C++ type."""
    if prop_type in ["Boolean", "Bool"]:
        return "bool"
    elif prop_type == "Byte":
        return sub_type if sub_type else "uint8"
    elif prop_type == "Int":
        return "int32"
    elif prop_type == "Int64":
        return "int64"
    elif prop_type in ["Float", "Double"]:
        return "double" if "double" in str(sub_type) else "float"
    elif prop_type == "String":
        return "FString"
    elif prop_type == "Name":
        return "FName"
    elif prop_type == "Text":
        return "FText"
    elif prop_type == "Struct":
        if sub_type and not sub_type.startswith("F"):
            return f"F{sub_type}"
        return sub_type or "FStruct"
    elif prop_type == "Object":
        if sub_type and sub_type != "self":
            # Determine prefix (A for Actors, U for Objects)
            if sub_type.startswith("B_") or "Character" in sub_type or sub_type == "Actor" or sub_type == "Pawn":
                prefix = "A"
            else:
                prefix = "U"
            
            if not sub_type.startswith((prefix, "A", "U")):
                return f"{prefix}{sub_type}*"
            return f"{sub_type}*"
        return "UObject*"
    elif prop_type == "Class":
        if sub_type:
            if not sub_type.startswith(("U", "A")):
                sub_type = f"U{sub_type}"
            return f"TSubclassOf<{sub_type}>"
        return "TSubclassOf<UObject>"
    else:
        return prop_type or "UObject*"

def convert_key_type(key_type, key_typename):
    """Convert map key type."""
    if key_type == "Struct" and key_typename:
        return f"F{key_typename}" if not key_typename.startswith("F") else key_typename
    elif key_type == "Name":
        return "FName"
    elif key_type == "String":
        return "FString"
    return "int32"

def determine_parent_class(name):
    """Determine C++ parent class based on naming convention."""
    if name in PARENT_CLASS_OVERRIDES:
        return PARENT_CLASS_OVERRIDES[name]
    elif name.startswith("ABP_"):
        return "UAnimInstance"
    elif name.startswith("AC_"):
        return "UActorComponent"
    elif name.startswith("W_"):
        return "UUserWidget"
    elif name.startswith("GI_"):
        return "UGameInstance"
    elif name.startswith("GM_"):
        return "AGameModeBase"
    elif name.startswith("GS_"):
        return "AGameStateBase"
    elif name.startswith("PC_"):
        return "APlayerController"
    elif name.startswith("SG_"):
        return "USaveGame"
    elif name.startswith("AN_"):
        return "UAnimNotify"
    elif name.startswith("ANS_"):
        return "UAnimNotifyState"
    elif name.startswith("BPI_"):
        return "UInterface"
    elif name.startswith(("BFL_", "BML_")):
        return "UBlueprintFunctionLibrary"
    elif name.startswith("PDA_"):
        return "UPrimaryDataAsset"
    else:
        return "AActor"

def get_class_prefix(name, parent):
    """Get C++ class prefix (A/U/I)."""
    if parent == "UInterface" or name.startswith("BPI_"):
        return "I"
    elif parent.startswith("A"):
        return "A"
    else:
        return "U"

def generate_header(name, data):
    """Generate C++ header file."""
    parent = determine_parent_class(name)
    prefix = get_class_prefix(name, parent)
    class_name = f"{prefix}{name}"
    
    # Start header
    content = "#pragma once\n\n"
    content += "#include \"CoreMinimal.h\"\n"
    
    # Add parent include
    if parent == "UAnimInstance":
        content += "#include \"Animation/AnimInstance.h\"\n"
    elif parent == "UActorComponent":
        content += "#include \"Components/ActorComponent.h\"\n"
    elif parent == "UUserWidget":
        content += "#include \"Blueprint/UserWidget.h\"\n"
    elif parent == "AGameModeBase":
        content += "#include \"GameFramework/GameModeBase.h\"\n"
    elif parent == "AGameStateBase":
        content += "#include \"GameFramework/GameStateBase.h\"\n"
    elif parent == "APlayerController":
        content += "#include \"GameFramework/PlayerController.h\"\n"
    elif parent == "USaveGame":
        content += "#include \"GameFramework/SaveGame.h\"\n"
    elif parent == "UInterface":
        content += "#include \"UObject/Interface.h\"\n"
    elif parent == "UBlueprintFunctionLibrary":
        content += "#include \"Kismet/BlueprintFunctionLibrary.h\"\n"
    elif parent == "UPrimaryDataAsset":
        content += "#include \"Engine/DataAsset.h\"\n"
    elif parent == "AActor":
        content += "#include \"GameFramework/Actor.h\"\n"
    
    content += f'#include "{name}.generated.h"\n\n'
    
    # Generate class
    content += "UCLASS(Blueprintable, BlueprintType)\n"
    content += f"class SLF_5_7_API {class_name} : public {parent}\n{{\n"
    content += "\tGENERATED_BODY()\n\n"
    content += "public:\n"
    content += f"\t{class_name}();\n\n"
    
    # Properties - NOW WITH COLLECTION TYPES!
    properties = extract_properties_from_json(data)
    for prop_name, cpp_type in sorted(properties.items()):
        safe_name = prop_name.replace(" ", "").replace("?", "").replace("-", "_")
        # Clean _C suffix
        cpp_type = re.sub(r"_C(?=\W|$)", "", cpp_type)
        content += f'\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Migration")\n'
        content += f"\t{cpp_type} {safe_name};\n\n"
    
    # Functions
    functions = data.get('functions', [])
    for func in functions:
        func_name = func['name'].replace(" ", "").replace("?", "")
        content += f'\tUFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Migration")\n'
        content += f"\tvoid {func_name}();\n"
        content += f"\tvirtual void {func_name}_Implementation();\n\n"
    
    content += "};\n"
    return content

def generate_source(name, data):
    """Generate C++ source file."""
    parent = determine_parent_class(name)
    prefix = get_class_prefix(name, parent)
    class_name = f"{prefix}{name}"
    
    content = f'#include "{name}.h"\n\n'
    content += f"{class_name}::{class_name}()\n{{\n"
    
    # Set tick
    if parent.startswith("AActor"):
        content += "\tPrimaryActorTick.bCanEverTick = true;\n"
    elif parent == "UActorComponent":
        content += "\tPrimaryComponentTick.bCanEverTick = true;\n"
    
    content += "}\n\n"
    
    ensure_dirs()
    
    # Load analysis
    with open(r"C:\scripts\BlueDestiny\analysis_output.json", 'r', encoding='utf-8') as f:
        analysis_map = json.load(f)
    
    generated = 0
    for name in analysis_map.keys():
        # Skip enums and structs
        if analysis_map[name]['type'] in ["Enum", "Struct"]:
            continue
        
        # Load JSON
        json_path = os.path.join(EXPORT_DIR, f"{name}.json")
        if not os.path.exists(json_path):
            continue
        
        with open(json_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
        
        # Generate
        header = generate_header(name, data)
        source = generate_source(name, data)
        
        # Write
        with open(os.path.join(CLASSES_DIR, f"{name}.h"), 'w', encoding='utf-8') as f:
            f.write(header)
        with open(os.path.join(PRIVATE_DIR, f"{name}.cpp"), 'w', encoding='utf-8') as f:
            f.write(source)
        
        generated += 1
        if generated % 50 == 0:
            print(f"Generated {generated} files...")
    
    print(f"\n✓ Generated {generated} C++ files with CORRECT collection types!")

if __name__ == "__main__":
    main()
