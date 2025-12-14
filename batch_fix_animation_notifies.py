#!/usr/bin/env python3
"""Batch fix Animation Notify files - change parent class from AActor to UAnimNotify/UAnimNotifyState"""
import os
import re

# Animation Notify files (should inherit from UAnimNotify)
an_files = [
    "AN_FootstepTrace.h",
    "AN_InterruptMontage.h",
    "AN_LaunchField.h",
    "AN_PlayCameraSequence.h",
    "AN_SetAiState.h",
    "AN_SetMovementMode.h",
    "AN_SpawnProjectile.h",
    "AN_TryGuard.h",
    "AN_WorldCameraShake.h",
]

# Animation Notify State files (should inherit from UAnimNotifyState)
ans_files = [
    "ANS_AI_FistTrace.h",
    "ANS_AI_RotateTowardsTarget.h",
    "ANS_AI_Trail.h",
    "ANS_AI_WeaponTrace.h",
    "ANS_FistTrace.h",
    "ANS_InputBuffer.h",
    "ANS_InvincibilityFrame.h",
    "ANS_RegisterAttackSequence.h",
    "ANS_ToggleChaosField.h",
    "ANS_Trail.h",
    "ANS_WeaponTrace.h",
]

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"

def fix_file(filepath, is_notify_state=False):
    """Fix parent class and function signatures in a single file"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Determine correct parent class
    if is_notify_state:
        old_parent = "public AActor"
        new_parent = "public UAnimNotifyState"
    else:
        old_parent = "public AActor"
        new_parent = "public UAnimNotify"
    
    #Fix parent class
    content = re.sub(old_parent, new_parent, content)
    
    # Fix function signatures - add U prefix and const ref for EventReference
    content = re.sub(r'\bSkeletalMeshComponent\*', 'USkeletalMeshComponent*', content)
    content = re.sub(r'\bAnimSequenceBase\*', 'UAnimSequenceBase*', content)
    content = re.sub(r'\bAnimNotifyEventReference\b(?!\&)', 'const FAnimNotifyEventReference&', content)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print(f"✓ Fixed: {os.path.basename(filepath)}")

# Process AN_ files
print(f"\n=== Processing {len(an_files)} Animation Notify (AN_) files ===")
for filename in an_files:
    filepath = os.path.join(base_path, filename)
    if os.path.exists(filepath):
        fix_file(filepath, is_notify_state=False)
    else:
        print(f"⚠ Not found: {filename}")

# Process ANS_ files  
print(f"\n=== Processing {len(ans_files)} Animation Notify State (ANS_) files ===")
for filename in ans_files:
    filepath = os.path.join(base_path, filename)
    if os.path.exists(filepath):
        fix_file(filepath, is_notify_state=True)
    else:
        print(f"⚠ Not found: {filename}")

print(f"\n✅ Batch processing complete! Fixed {len(an_files) + len(ans_files)} files total.")
