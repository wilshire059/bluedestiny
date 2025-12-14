import os

source_file = "c:/scripts/BlueDestiny/tracker_update.md"
target_file = "C:/Users/james/.gemini/antigravity/brain/68a7c97c-c717-464d-81dc-fb7d5d469f9c/manual_conversion_tracker.md"

# List of completed prefixes/files based on task.md and recent work
completed_prefixes = [
    "E_", "F", "BPI_", "AC_", "W_", 
    "GM_", "PC_", "GS_", "PS_",
    "ABP_Manny_PostProcess", "ABP_Quinn_PostProcess"
]

completed_specifics = [
    "B_Soulslike_Character",
    "AC_CollisionManager",
    "B_Item_Weapon",
    "B_Item_AI_Weapon",
    "B_Item_Lantern",
    "B_Item_Weapon_Shield",
    "B_Ladder",
    "B_LocationActor",
    "B_Mind",
    "B_PatrolPath",
    "B_PickupItem",
    "B_Poise",
    "B_Resistance_Focus",
    "B_Resistance_Immunity",
    "B_Resistance_Robustness",
    "B_Resistance_Vitality",
    "B_RestingPoint",
    "B_SequenceActor",
    "B_ShowcaseEnemy_ExitCombat",
    "B_ShowcaseEnemy_StatDisplay",
    "B_SkyManager",
    "B_Soulslike_Boss",
    "B_Soulslike_Boss_Malgareth",
    "B_Soulslike_Enemy",
    "B_Soulslike_NPC",
    "B_Soulslike_NPC_ShowcaseGuide",
    "PDA_Dialog",
    "AC_ProgressManager",
    "AC_AI_InteractionManager",
    "AC_AI_CombatManager",
    "AC_AI_Boss"
]

# Add wildcards for subclasses
completed_wildcards = [
    "B_Item_Weapon_",
    "B_Item_AI_Weapon_"
]

with open(source_file, "r") as f:
    lines = f.readlines()

new_lines = []
for line in lines:
    stripped = line.strip()
    if stripped.startswith("- [ ]") or stripped.startswith("- [x]"):
        # Extract filename (remove backticks if present)
        content = stripped[5:].strip()
        filename = content.replace("`", "")
        
        is_done = False
        if stripped.startswith("- [x]"):
            is_done = True
        
        # Check against our completed list
        if not is_done:
            if any(filename.startswith(p) for p in completed_prefixes):
                is_done = True
            elif filename in completed_specifics:
                is_done = True
            elif any(filename.startswith(w) for w in completed_wildcards):
                is_done = True
        
        if is_done:
            new_lines.append(line.replace("- [ ]", "- [x]"))
        else:
            new_lines.append(line)
    else:
        new_lines.append(line)

with open(target_file, "w") as f:
    f.writelines(new_lines)

print("Tracker updated successfully.")
