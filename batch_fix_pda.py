#!/usr/bin/env python3
"""Batch fix PDA (Primary Data Asset) files - CRITICAL parent class bug"""
import os
import re
import glob

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"
pda_files = glob.glob(os.path.join(base_path, "PDA_*.h"))

def fix_pda_file(filepath):
    """Fix CRITICAL parent class bug in PDA files"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # CRITICAL: Fix parent class AActor → UPrimaryDataAsset
    content = re.sub(
        r'(class SLF_5_7_API UPDA_[A-Za-z_]+) : public AActor',
        r'\1 : public UPrimaryDataAsset',
        content
    )
    
    # Fix type prefixes
    content = re.sub(r'\b(?<!U)(Object\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(DataTable\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(Texture2D\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(MaterialInterface\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SkeletalMesh\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(AnimMontage\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SoundBase\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(NiagaraSystem\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(CurveFloat\*)', r'U\1', content)
    
    # Fix nested PDA types
    content = re.sub(r'\b(?<!U)(PDA_[A-Za-z_]*)\*', r'U\1*', content)
    
    # Fix Actor types
    content = re.sub(r'\b(?<!A)(Actor\*)(?!>)', r'A\1', content)
    
    # Fix struct types
    content = re.sub(r'\b(?<!F)(GameplayTag\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Vector\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(LinearColor\b)', r'F\1', content)
    
    # Fix TSubclassOf template arguments
    content = re.sub(r'TSubclassOf<(?!U|A)Object>', 'TSubclassOf<UObject>', content)
    content = re.sub(r'TSubclassOf<(?!A)Actor>', 'TSubclassOf<AActor>', content)
    
    # Fix TSoftObjectPtr template arguments
    content = re.sub(r'TSoftObjectPtr<(?!U)Object>', 'TSoftObjectPtr<UObject>', content)
    content = re.sub(r'TSoftObjectPtr<(?!U)Texture2D>', 'TSoftObjectPtr<UTexture2D>', content)
    content = re.sub(r'TSoftObjectPtr<(?!U)DataTable>', 'TSoftObjectPtr<UDataTable>', content)
    
    # Fix TMap without args
    content = re.sub(r'\bTMap\b(?!\s*<)', r'TMap<FGameplayTag, double>', content)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return os.path.basename(filepath)

# Process all PDA files
print(f"\n=== Processing {len(pda_files)} PDA (Primary Data Asset) files ===")
print("CRITICAL: Fixing parent class AActor → UPrimaryDataAsset\n")

fixed_count = 0
for filepath in sorted(pda_files):
    filename = fix_pda_file(filepath)
    print(f"✓ Fixed: {filename}")
    fixed_count += 1
    
    if fixed_count % 20 == 0:
        print(f"  ... {fixed_count}/{len(pda_files)} files processed")

print(f"\n✅ All {len(pda_files)} PDA files fixed!")
