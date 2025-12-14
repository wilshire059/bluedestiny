#!/usr/bin/env python3
"""Batch fix all B_* Actor Blueprint files - fix missing U/A/F prefixes"""
import os
import re
import glob

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"
b_files = glob.glob(os.path.join(base_path, "B_*.h"))

def fix_actor_blueprint_file(filepath):
    """Fix type prefixes in an Actor Blueprint file"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Fix Actor/Pawn/Controller types
    content = re.sub(r'\b(?<!A)(Actor\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(Pawn\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(Controller\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(PlayerController\*)', r'A\1', content)
    
    # Fix Component types
    content = re.sub(r'\b(?<!U)(WidgetComponent\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SceneComponent\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SkeletalMeshComponent\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(CharacterMovementComponent\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(CapsuleComponent\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(TimelineComponent\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(InputComponent\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(PawnMovementComponent\*)', r'U\1', content)
    
    # Fix Animation types
    content = re.sub(r'\b(?<!U)(AnimMontage\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(AnimInstance\*)', r'U\1', content)
    
    # Fix Material/Sound/Effect types
    content = re.sub(r'\b(?<!U)(MaterialInterface\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SoundBase\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SoundAttenuation\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SoundConcurrency\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(NiagaraSystem\*)', r'U\1', content)
   
    # Fix Data Asset types
    content = re.sub(r'\b(?<!U)(PDA_[A-Za-z_]*)\*', r'U\1*', content)
    
    # Fix Object type
    content = re.sub(r'(?<!T)(?<!<)(?<!,\s)\b(Object\*)', r'U\1', content)
    
    # Fix struct types
    content = re.sub(r'\b(?<!F)(Vector\b)(?!\*)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Rotator\b)(?!\*)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Transform\b)(?!\*)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(HitResult\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(GameplayTag\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(InstancedStruct\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(PlatformUserId\b)', r'F\1', content)
    content = re.sub(r'(InitialActiveSoundParams\*)', r'F\1', content)
    
    # Fix TSubclassOf template arguments
    content = re.sub(r'TSubclassOf<(?!U|A)Object>', 'TSubclassOf<UObject>', content)
    content = re.sub(r'TSubclassOf<(?!A)Actor>', 'TSubclassOf<AActor>', content)
    content = re.sub(r'TSubclassOf<(?!U)CameraShakeBase>', 'TSubclassOf<UCameraShakeBase>', content)
    content = re.sub(r'TSubclassOf<(?!U)InputComponent>', 'TSubclassOf<UInputComponent>', content)
    
    # Fix TSoftObjectPtr template arguments
    content = re.sub(r'TSoftObjectPtr<(?!U)Object>', 'TSoftObjectPtr<UObject>', content)
    content = re.sub(r'TSoftObjectPtr<(?!U)AnimMontage>', 'TSoftObjectPtr<UAnimMontage>', content)
    content = re.sub(r'TSoftObjectPtr<(?!U)SoundBase>', 'TSoftObjectPtr<USoundBase>', content)
    content = re.sub(r'TSoftObjectPtr<(?!U)NiagaraSystem>', 'TSoftObjectPtr<UNiagaraSystem>', content)
    
    # Fix TSoftClassPtr template arguments
    content = re.sub(r'TSoftClassPtr<(?!A)Actor>', 'TSoftClassPtr<AActor>', content)
    
    # Fix TMap - needs special handling
    content = re.sub(r'\bTMap\b(?!\<)', r'TMap<FGameplayTag, double>', content)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return os.path.basename(filepath)

# Process all B_* Actor Blueprint files
print(f"\n=== Processing {len(b_files)} Actor Blueprint (B_*) files ===")
fixed_count = 0
for filepath in sorted(b_files):
    filename = fix_actor_blueprint_file(filepath)
    print(f"✓ Fixed: {filename}")
    fixed_count += 1
    
    if fixed_count % 20 == 0:
        print(f"  ... {fixed_count}/{len(b_files)} files processed")

print(f"\n✅ Batch processing complete! Fixed {fixed_count} files total.")
