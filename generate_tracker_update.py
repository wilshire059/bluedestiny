import os
import re

EXPORT_DIR = r"c:/scripts/BlueDestiny/Saved/NodeToCode/ExportedBlueprints"
TRACKER_FILE = r"C:\Users\james\.gemini\antigravity\brain\68a7c97c-c717-464d-81dc-fb7d5d469f9c\manual_conversion_tracker.md"

def get_files():
    files = [f for f in os.listdir(EXPORT_DIR) if f.endswith(".json")]
    return sorted(files)

def parse_tracker():
    completed = set()
    if os.path.exists(TRACKER_FILE):
        with open(TRACKER_FILE, "r") as f:
            for line in f:
                match = re.search(r"- \[x\] `(.*?)`", line)
                if match:
                    completed.add(match.group(1))
    return completed

def categorize_file(filename):
    name = os.path.splitext(filename)[0]
    
    if name.startswith("E_"): return "Enums"
    if name.startswith("F") or name.startswith("Struct_"): return "Structs" # Heuristic
    if name.startswith("BPI_"): return "Interfaces"
    if name.startswith("AC_"): return "Actor Components"
    if name.startswith("ABP_"): return "Animation Blueprints"
    if name.startswith("W_"): return "Widgets"
    if name.startswith("GM_"): return "Game Modes"
    if name.startswith("GS_"): return "Core Classes" # Grouping GS/PS/PC together
    if name.startswith("PS_"): return "Core Classes"
    if name.startswith("PC_"): return "Core Classes"
    if name == "B_Soulslike_Character": return "Core Classes"
    if name.startswith("BFL_"): return "Function Libraries"
    if name.startswith("DT_"): return "Data Tables"
    if name.startswith("DA_") or name.startswith("PDA_"): return "Data Assets"
    if name.startswith("BP_") or name.startswith("B_"): return "Blueprints"
    
    return "Uncategorized"

def generate_markdown(files, completed):
    categories = {
        "Enums": [],
        "Structs": [],
        "Interfaces": [],
        "Actor Components": [],
        "Core Classes": [],
        "Animation Blueprints": [],
        "Game Modes": [],
        "Widgets": [],
        "Function Libraries": [],
        "Data Tables": [],
        "Data Assets": [],
        "Blueprints": [],
        "Uncategorized": []
    }
    
    for f in files:
        name = os.path.splitext(f)[0]
        cat = categorize_file(f)
        categories[cat].append(name)
        
    # Order of categories in markdown
    order = [
        "Enums", "Structs", "Interfaces", "Actor Components", "Core Classes", 
        "Animation Blueprints", "Game Modes", "Widgets", "Blueprints", 
        "Function Libraries", "Data Assets", "Data Tables", "Uncategorized"
    ]
    
    output = []
    output.append("# Manual Blueprint to C++ Conversion Tracker\n")
    output.append("## Process Checklist")
    output.append("For each file, the following steps must be taken:")
    output.append("1.  **Analyze JSON**: Read the source JSON file to understand properties, functions, and logic.")
    output.append("2.  **Check Dependencies**: Identify any structs, enums, or classes this file depends on.")
    output.append("3.  **UE 5.7 Compatibility**: Ensure code uses modern UE 5.7 standards (e.g., `TObjectPtr`, `IncludeOrderVersion`).")
    output.append("4.  **Logic Matching**: Manually implement the logic from the EventGraph/FunctionGraphs.")
    output.append("5.  **Verify**: Visual check of the generated code.")
    output.append("6.  **Self-Validation**: Validate created files against JSON and check dependencies (e.g. missing variables, incorrect types, missing includes).\n")
    output.append("## File Status\n")
    
    for cat in order:
        if not categories[cat]: continue
        
        output.append(f"### {cat}")
        for name in categories[cat]:
            checked = "x" if name in completed else " "
            # Special case for already marked converted items to keep comments if possible? 
            # For now just simple list.
            output.append(f"- [{checked}] `{name}`")
        output.append("")
        
    return "\n".join(output)

def main():
    files = get_files()
    completed = parse_tracker()
    md = generate_markdown(files, completed)
    
    with open("tracker_update.md", "w") as f:
        f.write(md)
    print("Tracker update generated in tracker_update.md")

if __name__ == "__main__":
    main()
