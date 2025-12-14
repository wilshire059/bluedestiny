#!/usr/bin/env python3
"""
Comprehensive type prefix fixer - handles ALL missing F/U/A/E prefixes in generated C++ files
Based on manual JSON verification findings
"""
import os
import re
import glob

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"
all_h_files = glob.glob(os.path.join(base_path, "*.h"))

def fix_all_type_prefixes(filepath):
    """Comprehensively fix ALL type prefix issues"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original_content = content
    
    # Fix UObject-derived class types that are missing U prefix
    # Animation types
    content = re.sub(r'\b(?<!U)(AnimMontage\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(AnimSequenceBase\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(AnimInstance\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(AnimNotify(?!State)\b)', r'U\1', content)  # AnimNotify but not AnimNotifyState
    content = re.sub(r'\b(?<!U)(AnimNotifyState\b)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SkeletalMeshComponent\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(BlendProfile\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(CurveFloat\*)', r'U\1', content)
    
    # Fix struct types missing F prefix
    # Animation structs
    content = re.sub(r'\b(?<!F)(PoseLink\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(PoseSnapshot\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(MontageBlendSettings\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(AlphaBlendArgs\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(MarkerSyncAnimPosition\b)', r'F\1', content)
    
    # Common UE structs
    content = re.sub(r'\b(?<!F)(Vector(?!2D)\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Rotator\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Transform\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(HitResult\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(GameplayTag\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(InstancedStruct\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(LinearColor\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Color\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Vector2D\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Key\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Name\b)(?!\s*\()', r'F\1', content)  # FName but not in function calls
   
    # Fix Actor types missing A prefix
    content = re.sub(r'\b(?<!A)(Actor\*)(?!>)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(Pawn\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(Controller\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(PlayerController\*)', r'A\1', content)
    
    # Fix TSubclassOf template arguments
    content = re.sub(r'TSubclassOf<(?!U|A)(AnimNotify(?!State))>', r'TSubclassOf<U\1>', content)
    content = re.sub(r'TSubclassOf<(?!U)(AnimNotifyState)>', r'TSubclassOf<U\1>', content)
    content = re.sub(r'TSubclassOf<(?!U)(AnimInstance)>', r'TSubclassOf<U\1>', content)
    
    # Fix TArray template arguments for pointers
    content = re.sub(r'TArray<(?!U|A|F)(AnimInstance)\*>', r'TArray<U\1*>', content)
    
    # Fix enum types missing E prefix (where appropriate)
    content = re.sub(r'\b(?<!E)(RootMotionMode\b)', r'E\1', content)
    content = re.sub(r'\b(?<!E)(TeleportType\b)', r'E\1', content)
    content = re.sub(r'\b(?<!E)(TransitionRequestQueueMode\b)', r'E\1', content)
    content = re.sub(r'\b(?<!E)(TransitionRequestOverwriteMode\b)', r'E\1', content)  
    content = re.sub(r'\b(?<!E)(MontagePlayReturnType\b)', r'E\1', content)
    content = re.sub(r'\b(?<!E)(AnimCurveType\b)', r'E\1', content)
    
    return content if content != original_content else None

# Process all header files
print(f"\n=== Comprehensive Type Prefix Fix for {len(all_h_files)} files ===\n")

fixed_count = 0
unchanged_count = 0

for filepath in sorted(all_h_files):
    result = fix_all_type_prefixes(filepath)
    if result:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(result)
        print(f"✓ Fixed: {os.path.basename(filepath)}")
        fixed_count += 1
    else:
        unchanged_count += 1
    
    if (fixed_count + unchanged_count) % 50 == 0:
        print(f"  ... {fixed_count + unchanged_count}/{len(all_h_files)} files processed ({fixed_count} fixed, {unchanged_count} unchanged)")

print(f"\n✅ Complete! Fixed {fixed_count} files, {unchanged_count} already correct.")
