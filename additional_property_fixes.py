#!/usr/bin/env python3
"""
Additional property type fixes - handles component types and other UObject-derived properties
"""
import os
import re
import glob

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"
all_h_files = glob.glob(os.path.join(base_path, "*.h"))

def fix_property_types(filepath):
    """Fix remaining property type issues"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original_content = content
    
    # Fix component types in UPROPERTY declarations that are missing U prefix
    # These patterns specifically target property declarations
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(CharacterMovementComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(SceneComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(StaticMeshComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(SkeletalMeshComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(CapsuleComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(BoxComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(SphereComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(WidgetComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(AudioComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(PointLightComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(SpotLightComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(ChildActorComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(TimelineComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(NiagaraComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(TextRenderComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(ArrowComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(BillboardComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(CameraComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(InputComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(PawnMovementComponent\*)', r'\1U\2', content)
    content = re.sub(r'(UPROPERTY[^\n]*\n\s+)(?<!U)(NavMovementComponent\*)', r'\1U\2', content)
    
    # Fix Unknown properties that should be proper types based on naming
    # GroundSpeed, IsFalling should be double, bool
    content = re.sub(r'/\* Unknown \*/ UObject\* GroundSpeed;', r'double GroundSpeed;', content)
    content = re.sub(r'/\* Unknown \*/ UObject\* IsFalling;', r'bool IsFalling;', content)
    content = re.sub(r'/\* Unknown \*/ UObject\* IsJumping;', r'bool IsJumping;', content)
    content = re.sub(r'/\* Unknown \*/ UObject\* IsCrouching;', r'bool IsCrouching;', content)
    content = re.sub(r'/\* Unknown \*/ UObject\* Direction;', r'double Direction;', content)
    content = re.sub(r'/\* Unknown \*/ UObject\* Speed;', r'double Speed;', content)
    content = re.sub(r'/\* Unknown \*/ UObject\* Velocity;', r'FVector Velocity;', content)
    
    # Fix HitLocation
    content = re.sub(r'/\* Unknown \*/ UObject\* HitLocation;', r'FVector HitLocation;', content)
    
    return content if content != original_content else None

# Process all header files
print(f"\n=== Additional Property Type Fixes for {len(all_h_files)} files ===\n")

fixed_count = 0
unchanged_count = 0

for filepath in sorted(all_h_files):
    result = fix_property_types(filepath)
    if result:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(result)
        print(f"✓ Fixed: {os.path.basename(filepath)}")
        fixed_count += 1
    else:
        unchanged_count += 1
    
    if (fixed_count + unchanged_count) % 50 == 0:
        print(f"  ... {fixed_count + unchanged_count}/{len(all_h_files)} files processed")

print(f"\n✅ Complete! Fixed {fixed_count} files, {unchanged_count} already correct.")
