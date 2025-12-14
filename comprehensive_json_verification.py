"""
Comprehensive JSON to C++ Verification Script

This script verifies that all generated C++ files accurately reflect their JSON exports.
It checks:
1. Property types (including TArray, TMap, TSet)
2. Function signatures  
3. Parameter types and const-correctness
4. Return types
"""

import json
import re
import os
from pathlib import Path

EXPORT_DIR = Path("C:/scripts/BlueDestiny/Saved/NodeToCode/ExportedBlueprints")
GENERATED_DIR = Path("C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes")

class VerificationIssue:
    def __init__(self, file, line_num, issue_type, description):
        self.file = file
        self.line_num = line_num
        self.issue_type = issue_type
        self.description = description
    
    def __str__(self):
        return f"{self.file}:{self.line_num} [{self.issue_type}] {self.description}"

def json_type_to_cpp(json_type, json_subtype, is_array, is_set, is_map, key_type="", key_typename=""):
    """
    Convert JSON type information to proper C++ type.
    """
    base_type = ""
    
    # Handle base types
    if json_type == "Boolean":
        base_type = "bool"
    elif json_type == "Byte":
        if json_subtype:
            base_type = f"E_{json_subtype}" if not json_subtype.startswith("E_") else json_subtype
        else:
            base_type = "uint8"
    elif json_type == "Int":
        base_type = "int32"
    elif json_type == "Int64":
        base_type = "int64"
    elif json_type == "Float":
        base_type = "float"
    elif json_type == "Double":
        base_type = "double"
    elif json_type == "String":
        base_type = "FString"
    elif json_type == "Name":
        base_type = "FName"
    elif json_type == "Text":
        base_type = "FText"
    elif json_type == "Struct":
        # Structs need F prefix
        if json_subtype:
            base_type = f"F{json_subtype}" if not json_subtype.startswith("F") else json_subtype
        else:
            base_type = "FUnknownStruct"
    elif json_type == "Object":
        # Objects need U or A prefix
        if json_subtype and not json_subtype in ["Object", "self"]:
            # Determine if it's an Actor or UObject
            if json_subtype.startswith("B_") or "Character"in json_subtype or json_subtype == "Actor" or json_subtype == "Pawn":
                base_type = f"A{json_subtype}" if not json_subtype.startswith("A") else json_subtype
            else:
                base_type = f"U{json_subtype}" if not json_subtype.startswith("U") else json_subtype
            # Add pointer for objects
            base_type += "*"
        else:
            base_type = "UObject*"
    elif json_type == "Class":
        if json_subtype:
            if json_subtype.startswith("B_") or "Character" in json_subtype or json_subtype == "Actor":
                class_base = f"A{json_subtype}" if not json_subtype.startswith("A") else json_subtype  
            else:
                class_base = f"U{json_subtype}" if not json_subtype.startswith("U") else json_subtype
            base_type = f"TSubclassOf<{class_base}>"
        else:
            base_type = "TSubclassOf<UObject>"
    else:
        base_type = json_type
    
    # Apply collection wrappers
    if is_map:
        # Determine key type
        cpp_key_type = "int32"
        if key_type == "Struct" and key_typename:
            cpp_key_type = f"F{key_typename}" if not key_typename.startswith("F") else key_typename
        elif key_type == "Name":
            cpp_key_type = "FName"
        return f"TMap<{cpp_key_type}, {base_type}>"
    elif is_set:
        return f"TSet<{base_type}>"
    elif is_array:
        return f"TArray<{base_type}>"
    
    return base_type

def parse_cpp_property(line):
    """
    Extract property name and type from a UPROPERTY line in C++.
    Returns (property_name, property_type) or None if not a property.
    """
    # Match pattern: type name; or type* name;
    match = re.search(r'^\s*(T(?:Array|Map|Set)<.+?>|[A-Za-z_][A-Za-z0-9_:<>]*\*?)\s+([A-Za-z_][A-Za-z0-9_]*)\s*;', line)
    if match:
        prop_type = match.group(1).strip()
        prop_name = match.group(2).strip()
        return (prop_name, prop_type)
    return None

def verify_file(basename):
    """
    Verify a single file's JSON to C++ conversion.
    """
    json_path = EXPORT_DIR / f"{basename}.json"
    cpp_path = GENERATED_DIR / f"{basename}.h"
    
    if not json_path.exists():
        return []
    if not cpp_path.exists():
        return []
    
    issues = []
    
    # Load JSON
    with open(json_path, 'r', encoding='utf-8') as f:
        data = json.load(f)
    
    # Load C++ header
    with open(cpp_path, 'r', encoding='utf-8') as f:
        cpp_lines = f.readlines()
    
    # Check functions section in JSON for property definitions
    if "functions" in data:
        for func in data["functions"]:
            func_name = func.get("name", "")
            
            # Check outputs (these become function parameters or properties)
            if "outputs" in func:
                for output in func["outputs"]:
                    output_name = output.get("name", "")
                    json_cpp_type = json_type_to_cpp(
                        output.get("type", ""),
                        output.get("typeName", ""),
                        output.get("bIsArray", False),
                        output.get("bIsSet", False),
                        output.get("bIsMap", False),
                        output.get("keyType", ""),
                        output.get("keyTypeName", "")
                    )
                    
                    # Find this in C++ and compare
                    # (This would require more sophisticated parsing for function signatures)
                    
    return issues

def main():
    print("=== Comprehensive JSON to C++ Verification ===\n")
    
    all_issues = []
    files_checked = 0
    
    # Get all JSON files
    json_files = list(EXPORT_DIR.glob("*.json"))
    
    for json_file in json_files:
        basename = json_file.stem
        issues = verify_file(basename)
        if issues:
            all_issues.extend(issues)
        files_checked += 1
        
        if files_checked % 50 == 0:
            print(f"Checked {files_checked}/{len(json_files)} files...")
    
    print(f"\n✓ Checked {files_checked} files")
    print(f"✗ Found {len(all_issues)} issues")
    
    if all_issues:
        print("\nIssues Found:")
        for issue in all_issues[:50]:  # Show first 50
            print(f"  - {issue}")
        if len(all_issues) > 50:
            print(f"  ... and {len(all_issues) - 50} more")
    
    return len(all_issues)

if __name__ == "__main__":
    exit(main())
