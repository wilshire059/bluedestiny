#!/usr/bin/env python3
"""Batch fix BFL/BML Blueprint Function/Macro Library files - CRITICAL parent class bug"""
import os
import re
import glob

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"

# Find all BFL and BML files
bfl_bml_files = glob.glob(os.path.join(base_path, "BFL_*.h")) + glob.glob(os.path.join(base_path, "BML_*.h"))

def fix_bfl_bml_file(filepath):
    """Fix CRITICAL parent class bug in BFL/BML files"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # CRITICAL: Fix parent class AActor → UBlueprintFunctionLibrary
    content = re.sub(
        r'(class SLF_5_7_API U(BFL|BML)_[A-Za-z_]+) : public AActor',
        r'\1 : public UBlueprintFunctionLibrary',
        content
    )
    
    # Fix type prefixes in function signatures
    content = re.sub(r'\b(?<!U)(Object\*)', r'U\1', content)
    content = re.sub(r'\b(?<!A)(Actor\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(Controller\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(Pawn\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(PlayerController\*)', r'A\1', content)
    
    # Fix UObject types
    content = re.sub(r'\b(?<!U)(InputMappingContext\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(InputAction\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(PDA_[A-Za-z_]*)\*', r'U\1*', content)
    content = re.sub(r'\b(?<!U)(EnhancedInputUserSettings\*)', r'U\1', content)
    
    # Fix struct types
    content = re.sub(r'\b(?<!F)(GameplayTag\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Transform\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(HitResult\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Vector\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Key\b)', r'F\1', content)
    
    # Fix TMap without template args
    content = re.sub(r'\bTMap\b(?!\s*<)', r'TMap<FGameplayTag, double>', content)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return os.path.basename(filepath)

# Process all BFL/BML files
print(f"\n=== Processing {len(bfl_bml_files)} BFL/BML files ===")
print("CRITICAL: Fixing parent class AActor → UBlueprintFunctionLibrary\n")

for filepath in sorted(bfl_bml_files):
    filename = fix_bfl_bml_file(filepath)
    print(f"✓ Fixed: {filename}")

print(f"\n✅ All {len(bfl_bml_files)} BFL/BML files fixed!")
