#!/usr/bin/env python3
"""Batch fix Game Framework files - fix missing U/A/F prefixes and invalid properties"""
import os
import re

files_to_fix = {
    "GM_SoulslikeFramework.h": "GameMode",
    "GM_Menu_SoulslikeFramework.h": "GameMode",
    "PC_SoulslikeFramework.h": "PlayerController",
    "PC_Menu_SoulslikeFramework.h": "PlayerController",
}

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"

def fix_game_framework_file(filepath, file_type):
    """Fix type prefixes and remove invalid properties in a Game Framework file"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Remove invalid properties (RootComponent/DefaultSceneRoot not valid for GameMode/PlayerController/GameState)
    content = re.sub(r'\tUPROPERTY\(EditAnywhere, BlueprintReadWrite, Category="Migration"\)\r?\n\tUSceneComponent\* DefaultSceneRoot;\r?\n\r?\n', '', content)
    content = re.sub(r'\tUPROPERTY\(EditAnywhere, BlueprintReadWrite, Category="Migration"\)\r?\n\tSceneComponent\* RootComponent;\r?\n\r?\n', '', content)
    
    # Fix all type prefixes in function signatures and properties
    # Controller -> AController
    content = re.sub(r'\b(Controller\*)', r'A\1', content)
    # Pawn -> APawn  
    content = re.sub(r'\b(Pawn\*)', r'A\1', content)
    # Actor -> AActor
    content = re.sub(r'\b(Actor\*)', r'A\1', content)
    # PlayerController -> APlayerController
    content = re.sub(r'\b(PlayerController\*)', r'A\1', content)
    # PlayerState -> APlayerState  
    content = re.sub(r'\b(PlayerState\*)', r'A\1', content)
   # HUD -> AHUD
    content = re.sub(r'\b(HUD\*)', r'A\1', content)
    
    # Fix input-related types
    content = re.sub(r'\b(InputAction\*)', r'U\1', content)
    content = re.sub(r'\b(InputMappingContext\*)', r'U\1', content)
    content = re.sub(r'(InputActionValue)', r'F\1', content)
    
    # Fix material/sound/effect types
    content = re.sub(r'\b(MaterialInterface\*)', r'U\1', content)
    content = re.sub(r'\b(UserWidget\*)', r'U\1', content)
    content = re.sub(r'\b(ForceFeedbackEffect\*)', r'UF\1', content)
    content = re.sub(r'\b(HapticFeedbackEffect_Base\*)', r'U\1', content)
    content = re.sub(r'\b(CameraShakeSourceComponent\*)', r'U\1', content)
    content = re.sub(r'\b(TouchInterface\*)', r'U\1', content)
    
    # Fix struct types
    content = re.sub(r'\b(Vector\b)', r'F\1', content)
    content = re.sub(r'([^F])(Vector2D)', r'\1F\2', content)
    content = re.sub(r'\b(Rotator\b)', r'F\1', content)
    content = re.sub(r'\b(Color\b)', r'F\1', content)
    content = re.sub(r'\b(Key\b)', r'F\1', content)
    content = re.sub(r'\b(HitResult)', r'F\1', content)
    content = re.sub(r'\b(LatentActionInfo)', r'F\1', content)
    content = re.sub(r'\b(StreamingSourceShape)', r'F\1', content)
    content = re.sub(r'\b(PlatformUserId)', r'F\1', content)
    
    # Fix TSubclassOf template arguments
    content = re.sub(r'TSubclassOf<Object>', 'TSubclassOf<UObject>', content)
    content = re.sub(r'TSubclassOf<Actor>', 'TSubclassOf<AActor>', content)
    content = re.sub(r'TSubclassOf<PlayerInput>', 'TSubclassOf<UPlayerInput>', content)
    content = re.sub(r'TSubclassOf<HUD>', 'TSubclassOf<AHUD>', content)
    content = re.sub(r'TSubclassOf<CameraShakeBase>', 'TSubclassOf<UCameraShakeBase>', content)
    
    # Fix spectator pawn
    content = re.sub(r'\b(SpectatorPawn\*)', r'A\1', content)
    
    # Fix gameplay tag and instance struct types
    content = re.sub(r'\b(?<!F)(GameplayTag\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(InstancedStruct\b)', r'F\1', content)
    
    # Fix SceneComponent
    content = re.sub(r'\b(SceneComponent\*)', r'U\1', content)
    
    # Fix DamageType
    content = re.sub(r'\b(DamageType\*)', r'const U\1', content)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print(f"✓ Fixed: {os.path.basename(filepath)}")

# Process all Game Framework files
print(f"\n=== Processing {len(files_to_fix)} Game Framework files ===")
for filename, file_type in files_to_fix.items():
    filepath = os.path.join(base_path, filename)
    if os.path.exists(filepath):
        fix_game_framework_file(filepath, file_type)
    else:
        print(f"⚠ Not found: {filename}")

print(f"\n✅ Batch processing complete! Fixed {len(files_to_fix)} files total.")
