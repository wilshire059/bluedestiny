import json
import os

EXPORT_DIR = r"C:\scripts\BlueDestiny\Saved\NodeToCode\ExportedBlueprints"
OUTPUT_BASE = r"C:\scripts\BlueDestiny\Source\SLF_5_7\Generated"
ENUMS_DIR = os.path.join(OUTPUT_BASE, "Enums")
STRUCTS_DIR = os.path.join(OUTPUT_BASE, "Structs")

def ensure_dirs():
    os.makedirs(ENUMS_DIR, exist_ok=True)
    os.makedirs(STRUCTS_DIR, exist_ok=True)

def cpp_type(bp_type):
    # Mapping from BP types to C++ types
    if bp_type == "bool": return "bool"
    if bp_type == "int32": return "int32"
    if bp_type == "double": return "double"
    if bp_type == "float": return "float"
    if bp_type == "FString": return "FString"
    if bp_type == "FText": return "FText"
    if bp_type == "FName": return "FName"
    if bp_type == "Vector": return "FVector"
    if bp_type == "Rotator": return "FRotator"
    if bp_type == "Transform": return "FTransform"
    if bp_type.startswith("TArray"): return bp_type # Simplified
    if bp_type.startswith("TMap"): return bp_type # Simplified
    if bp_type == "Actor*": return "AActor*"
    if bp_type == "Object*": return "UObject*"
    # Add more mappings as needed
    return bp_type

def generate_enum(data):
    name = data['name']
    values = data.get('values', [])
    
    content = f"#pragma once\n\n#include \"CoreMinimal.h\"\n\n"
    content += f"UENUM(BlueprintType)\nenum class {name} : uint8\n{{\n"
    
    for val in values:
        val_name = val['name'].replace(" ", "")
        if val_name == "-": val_name = "None"
        content += f"\t{val_name} UMETA(DisplayName=\"{val['name']}\"),\n"
        
    content += "};\n"
    return content

def sanitize_name(name):
    return name.replace("?", "").replace(" ", "").replace("-", "_")

def sanitize_type(type_name):
    # Handle TSoftClassPtr<B_Item_C> -> TSoftClassPtr<AB_Item>
    if "_C>" in type_name:
        type_name = type_name.replace("_C>", ">")
        # Heuristic: if it starts with B_, replace with A (Actor) or U (Object)
        # This is tricky. For now, let's just strip _C.
    return type_name

def generate_struct(data, all_definitions):
    name = data['name']
    members = data.get('members', [])
    
    includes = set()
    includes.add(f'"{name}.generated.h"')
    includes.add('"GameplayTagContainer.h"')
    
    # Identify dependencies
    for member in members:
        mem_type = member['typeName']
        # Clean up type to find base name
        base_type = mem_type
        if "<" in base_type:
            base_type = base_type.split("<")[1].split(">")[0]
        
        if base_type in all_definitions:
            if all_definitions[base_type]['type'] == 'enum':
                includes.add(f'"../Enums/{base_type}.h"')
            else:
                includes.add(f'"{base_type}.h"')
        
        # UE Includes
        if "AnimMontage" in base_type: includes.add('"Animation/AnimMontage.h"')
        if "SoundBase" in base_type: includes.add('"Sound/SoundBase.h"')
        if "Texture2D" in base_type: includes.add('"Engine/Texture2D.h"')
        if "MaterialInterface" in base_type: includes.add('"Materials/MaterialInterface.h"')
        if "ParticleSystem" in base_type: includes.add('"Particles/ParticleSystem.h"')
        if "NiagaraSystem" in base_type: includes.add('"NiagaraSystem.h"')
        if "StaticMesh" in base_type: includes.add('"Engine/StaticMesh.h"')
        if "SkeletalMesh" in base_type: includes.add('"Engine/SkeletalMesh.h"')
        if "CurveFloat" in base_type: includes.add('"Curves/CurveFloat.h"')
        if "CurveVector" in base_type: includes.add('"Curves/CurveVector.h"')
        if "DataTable" in base_type: includes.add('"Engine/DataTable.h"')

    content = "#pragma once\n\n#include \"CoreMinimal.h\"\n"
    for inc in sorted(includes):
        content += f"#include {inc}\n"
    
    content += f"\nUSTRUCT(BlueprintType)\nstruct {name}\n{{\n\tGENERATED_BODY()\n\n"
    
    for member in members:
        mem_name = sanitize_name(member['name'])
        mem_type = sanitize_type(member['typeName'])
        
        # Basic type cleanup
        if mem_type == "GameplayTag": mem_type = "FGameplayTag"
        if mem_type == "GameplayTagContainer": mem_type = "FGameplayTagContainer"
        
        content += f"\tUPROPERTY(EditAnywhere, BlueprintReadWrite)\n\t{mem_type} {mem_name};\n\n"
        
    content += "};\n"
    return content

def main():
    ensure_dirs()
    
    definitions = {}
    
    for filename in os.listdir(EXPORT_DIR):
        if not filename.endswith(".json"): continue
        
        filepath = os.path.join(EXPORT_DIR, filename)
        with open(filepath, 'r', encoding='utf-8') as f:
            try:
                data = json.load(f)
            except:
                continue
                
        # Enums
        for enum in data.get('enums', []):
            name = enum['name']
            if name not in definitions:
                definitions[name] = {'type': 'enum', 'data': enum}
                
        # Structs
        for struct in data.get('structs', []):
            name = struct['name']
            if name in ["FVector", "FRotator", "FTransform", "FString", "FText", "FName", "FGuid", "FLinearColor", "FColor", "FVector2D", "FObject", "FFloat", "FInt", "FBool"]:
                continue
            if name not in definitions:
                definitions[name] = {'type': 'struct', 'data': struct}

    # Generate files
    for name, info in definitions.items():
        if info['type'] == 'enum':
            content = generate_enum(info['data'])
            with open(os.path.join(ENUMS_DIR, f"{name}.h"), 'w') as f:
                f.write(content)
        elif info['type'] == 'struct':
            content = generate_struct(info['data'], definitions)
            with open(os.path.join(STRUCTS_DIR, f"{name}.h"), 'w') as f:
                f.write(content)
                
    print(f"Generated {len(definitions)} types.")

if __name__ == "__main__":
    main()
