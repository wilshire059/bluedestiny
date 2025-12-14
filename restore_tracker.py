import os

export_dir = "c:/scripts/BlueDestiny/Saved/NodeToCode/ExportedBlueprints/"
tracker_file = "C:/Users/james/.gemini/antigravity/brain/68a7c97c-c717-464d-81dc-fb7d5d469f9c/manual_conversion_tracker.md"

files = sorted([f for f in os.listdir(export_dir) if f.endswith(".json")])

completed_prefixes = ["E_", "F", "BPI_", "AC_", "ABP_", "GM_", "W_", "PC_", "AIC_", "CR_", "GI_", "GS_", "PS_"]
completed_specifics = [
    "AC_CollisionManager.json",
    "B_Item_Lantern.json",
    "B_Item_Weapon_Shield.json",
    "B_Ladder.json",
    "B_LocationActor.json",
    "B_Mind.json",
    "B_PatrolPath.json",
    "B_PickupItem.json",
    "B_Poise.json",
    "B_Resistance_Focus.json",
    "B_Resistance_Immunity.json",
    "B_Resistance_Robustness.json",
    "B_Resistance_Vitality.json",
    "B_RestingPoint.json",
    "B_SequenceActor.json",
    "B_ShowcaseEnemy_ExitCombat.json",
    "B_ShowcaseEnemy_StatDisplay.json",
    "B_SkyManager.json",
    "B_Soulslike_Boss.json",
    "B_Soulslike_Boss_Malgareth.json",
    "B_Soulslike_Enemy.json",
    "B_Soulslike_NPC.json",
    "B_Soulslike_NPC_ShowcaseGuide.json",
    "PDA_Dialog.json",
    "AC_ProgressManager.json",
    "AC_AI_InteractionManager.json",
    "AC_AI_CombatManager.json",
    "AC_AI_Boss.json"
]

# Add wildcard completions
wildcard_completions = [
    "B_Item_Weapon",
    "B_Item_AI_Weapon"
]

categories = {
    "Enums": "E_",
    "Structs": "F",
    "Interfaces": "BPI_",
    "Actor Components": "AC_",
    "Characters & Animation": ("ABP_", "CR_", "ALI_"),
    "Widgets": "W_",
    "Game Modes & Controllers": ("GM_", "PC_", "AIC_", "GI_", "GS_", "PS_"),
    "Data Assets": "PDA_",
    "Blueprints": "B_",
    "Anim Notifies & States": ("AN_", "ANS_"),
    "Behavior Tree": ("BT", "BB"),
    "Editor Utilities": "EU",
    "Others": ""
}

content = "# Manual Conversion Tracker\n\n"

def get_category(filename):
    for cat, prefix in categories.items():
        if isinstance(prefix, tuple):
            if filename.startswith(prefix):
                return cat
        elif prefix and filename.startswith(prefix):
            return cat
    return "Others"

grouped_files = {cat: [] for cat in categories}

for f in files:
    cat = get_category(f)
    grouped_files[cat].append(f)

for cat, file_list in grouped_files.items():
    if not file_list:
        continue
    content += f"## {cat}\n"
    for f in file_list:
        is_done = False
        if any(f.startswith(p) for p in completed_prefixes):
            is_done = True
        elif f in completed_specifics:
            is_done = True
        elif any(f.startswith(w) for w in wildcard_completions):
            is_done = True
        
        # Special case for F structs which might match F prefix but be something else? 
        # No, F*.json is pretty safe for structs in UE.
        
        check = "x" if is_done else " "
        name = f.replace(".json", "")
        content += f"- [{check}] {name}\n"
    content += "\n"

with open(tracker_file, "w") as f:
    f.write(content)

print("Tracker restored.")
