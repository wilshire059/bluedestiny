import os

BASE_DIR = r"C:\scripts\BlueDestiny\Source\SLF_5_7\Generated"
JSON_DIR = r"C:\scripts\BlueDestiny\Saved\NodeToCode\ExportedBlueprints"
TRACKER_FILE = r"C:\Users\james\.gemini\antigravity\brain\606d0315-cf3e-498f-a413-5bc4c71de7ef\review_tracker.md"

def main():
    content = "# Generated Code Review Tracker\n\n"
    content += "| File Name | Type | JSON Source | Status | Notes |\n"
    content += "| :--- | :--- | :--- | :--- | :--- |\n"
    
    dirs = {
        "Classes": "Class",
        "Enums": "Enum",
        "Structs": "Struct"
    }
    
    for d, default_type in dirs.items():
        full_path = os.path.join(BASE_DIR, d)
        if not os.path.exists(full_path): continue
        
        files = sorted(os.listdir(full_path))
        for f in files:
            if not f.endswith(".h"): continue
            
            name = f.replace(".h", "")
            
            # JSON mapping might be direct or slightly different
            # Enums might be E_...
            # Structs might be F...
            
            json_name = name
            # Heuristic: Enums and Structs might be defined inside other blueprints or as standalone.
            # Standalone usually match name.
            
            json_path = os.path.join(JSON_DIR, json_name + ".json")
            has_json = os.path.exists(json_path)
            
            json_status = "Found" if has_json else "Derived/Internal"
            
            type_ = default_type
            if name.startswith("BPI_"): type_ = "Interface"
            
            content += f"| {f} | {type_} | {json_status} | Pending | |\n"

    with open(TRACKER_FILE, 'w') as f:
        f.write(content)
    print("Tracker updated.")

if __name__ == "__main__":
    main()
