#!/usr/bin/env python3
"""Batch fix Blueprint Interface files - fix missing U/A/F prefixes in function signatures"""
import os
import re

bpi_files = [
    "BPI_AIC.h",
    "BPI_BossDoor.h",
    "BPI_Controller.h",
    "BPI_DestructibleHelper.h",
    "BPI_Enemy.h",
    "BPI_EnemyHealthbar.h",
    "BPI_Executable.h",
    "BPI_ExecutionIndicator.h",
    "BPI_GameInstance.h",
    "BPI_GenericCharacter.h",
    "BPI_Interactable.h",
    "BPI_Item.h",
    "BPI_MainMenu.h",
    "BPI_NPC.h",
    "BPI_Player.h",
    "BPI_Projectile.h",
    "BPI_RestingPoint.h",
    "BPI_StatEntry.h",
]

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"

def fix_bpi_file(filepath):
    """Fix type prefixes in a Blueprint Interface file"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Fix actor/pawn/controller types
    content = re.sub(r'\b(Actor\*)', r'A\1', content)
    content = re.sub(r'\b(Pawn\*)', r'A\1', content)
    content = re.sub(r'\b(Controller\*)', r'A\1', content)
    
    # Fix UObject types
    content = re.sub(r'\b(AnimMontage\*)', r'U\1', content)
    content = re.sub(r'\b(AnimInstance\*)', r'U\1', content)
    content = re.sub(r'\b(SkeletalMesh\*)', r'U\1', content)
    content = re.sub(r'\b(MaterialInterface\*)', r'U\1', content)
    content = re.sub(r'\b(SoundBase\*)', r'U\1', content)
    content = re.sub(r'\b(SoundAttenuation\*)', r'U\1', content)
    content = re.sub(r'\b(SoundConcurrency\*)', r'U\1', content)
    content = re.sub(r'\b(NiagaraSystem\*)', r'U\1', content)
    content = re.sub(r'\b(LevelSequence\*)', r'U\1', content)
    content = re.sub(r'\b(InputMappingContext\*)', r'U\1', content)
    content = re.sub(r'\b(SceneComponent\*)', r'U\1', content)
    content = re.sub(r'\b(PDA_Item\*)', r'U\1', content)
    
    # Fix struct types
    content = re.sub(r'\b(?<!F)(Vector\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Rotator\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Transform\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(GameplayTag\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(InstancedStruct\b)', r'F\1', content)
    content = re.sub(r'(MovieSceneSequencePlaybackSettings)', r'F\1', content)
    content = re.sub(r'(InitialActiveSoundParams\*)', r'F\1', content)
    
    # Fix TSubclassOf and TSoftObjectPtr template arguments
    content = re.sub(r'TSubclassOf<Actor>', 'TSubclassOf<AActor>', content)
    content = re.sub(r'TSubclassOf<CameraShakeBase>', 'TSubclassOf<UCameraShakeBase>', content)
    content = re.sub(r'TSoftObjectPtr<AnimMontage>', 'TSoftObjectPtr<UAnimMontage>', content)
    content = re.sub(r'TSoftObjectPtr<SkeletalMesh>', 'TSoftObjectPtr<USkeletalMesh>', content)
    content = re.sub(r'TSoftObjectPtr<SoundBase>', 'TSoftObjectPtr<USoundBase>', content)
    content = re.sub(r'TSoftObjectPtr<NiagaraSystem>', 'TSoftObjectPtr<UNiagaraSystem>', content)
    content = re.sub(r'TSoftObjectPtr<Object>', 'TSoftObjectPtr<UObject>', content)
    content = re.sub(r'TSoftClassPtr<Actor>', 'TSoftClassPtr<AActor>', content)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print(f"✓ Fixed: {os.path.basename(filepath)}")

# Process all Blueprint Interface files
print(f"\n=== Processing {len(bpi_files)} Blueprint Interface (BPI_) files ===")
for filename in bpi_files:
    filepath = os.path.join(base_path, filename)
    if os.path.exists(filepath):
        fix_bpi_file(filepath)
    else:
        print(f"⚠ Not found: {filename}")

print(f"\n✅ Batch processing complete! Fixed {len(bpi_files)} files total.")
