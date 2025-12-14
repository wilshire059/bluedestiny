import unreal
import os

def validate_coverage():
    # 1. Get List of Project Blueprints (The "Target List")
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    filter = unreal.ARFilter(
        class_names=[
            "Blueprint", 
            "BlueprintGeneratedClass", 
            "WidgetBlueprint", 
            "AnimBlueprint",
            "EditorUtilityBlueprint",
            "EditorUtilityWidgetBlueprint",
            "ControlRigBlueprint"
        ],
        package_paths=["/Game"],
        recursive_paths=True
    )
    assets = asset_registry.get_assets(filter)
    
    project_bps = set()
    for asset in assets:
        project_bps.add(str(asset.asset_name))
        
    unreal.log(f"Project Blueprints Found: {len(project_bps)}")

    # 2. Get List of NodeToCode Exports (The "Existing List")
    export_dir = r"C:\scripts\BlueDestiny\Plugins\NodeToCode\ExportedBlueprints"
    
    if not os.path.exists(export_dir):
        unreal.log_error(f"Export directory not found: {export_dir}")
        return

    exported_json_files = set()
    for filename in os.listdir(export_dir):
        if filename.endswith(".json"):
            # Remove extension to get asset name
            asset_name = os.path.splitext(filename)[0]
            exported_json_files.add(asset_name)
            
    unreal.log(f"NodeToCode Exports Found: {len(exported_json_files)}")

    # 3. Compare
    missing = []
    for bp in project_bps:
        if bp not in exported_json_files:
            missing.append(bp)
            
    # 4. Report
    if missing:
        unreal.log_warning(f"MISSING {len(missing)} NodeToCode Exports!")
        unreal.log("The following Blueprints exist in project but have NO NodeToCode JSON:")
        for m in sorted(missing):
            unreal.log(f" - {m}")
    else:
        unreal.log("SUCCESS! All 395+ Blueprints have corresponding NodeToCode exports.")

if __name__ == "__main__":
    validate_coverage()
