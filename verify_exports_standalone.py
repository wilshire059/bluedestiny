import os

def verify_standalone():
    # 1. Source Truth: The files successfully exported by the Python script (The "Structure" exports)
    # These represent the 395 assets we definitively know exist and are Blueprints.
    structure_dir = r"C:\scripts\BlueDestiny\Saved\BlueprintComponentExports"
    
    # 2. Target: The NodeToCode exports (The "Logic" exports)
    logic_dir = r"C:\scripts\BlueDestiny\Plugins\NodeToCode\ExportedBlueprints"
    
    if not os.path.exists(structure_dir):
        print(f"Error: Structure directory not found: {structure_dir}")
        return
        
    if not os.path.exists(logic_dir):
        print(f"Error: Logic directory not found: {logic_dir}")
        return

    # Gather sets of names (stripped of extension and suffixes)
    structure_assets = set()
    for f in os.listdir(structure_dir):
        if f.endswith("_COMPLETE.json"):
            # Format: Name_COMPLETE.json
            name = f.replace("_COMPLETE.json", "")
            structure_assets.add(name)
            
    logic_assets = set()
    for f in os.listdir(logic_dir):
        if f.endswith(".json"):
            # NodeToCode sometimes just uses Name.json
            name = os.path.splitext(f)[0]
            logic_assets.add(name)
            
    print(f"Found {len(structure_assets)} Structure Exports (Project Blueprints)")
    print(f"Found {len(logic_assets)} NodeToCode Exports (Logic JSONs)")

    # Compare
    missing_logic = []
    for asset in structure_assets:
        if asset not in logic_assets:
            # Check for B_Item_COMPLETE vs B_Item logic match
            # Sometimes N2C names are slightly different? Assuming exact match for now.
            missing_logic.append(asset)
            
    if missing_logic:
        print(f"!!! MISSING NODE-TO-CODE EXPORTS: {len(missing_logic)} !!!")
        print("The following Blueprints have Structure data but NO Logic data:")
        for m in sorted(missing_logic):
            print(f" - {m}")
    else:
        print("SUCCESS: All Project Blueprints have corresponding NodeToCode logic exports.")

if __name__ == "__main__":
    verify_standalone()
