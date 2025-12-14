import unreal
import os

def count_assets():
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    
    # Get ALL assets in /Game
    filter = unreal.ARFilter(
        package_paths=["/Game"],
        recursive_paths=True
    )
    
    assets = asset_registry.get_assets(filter)
    
    counts = {}
    for asset in assets:
        c_name = asset.asset_class_path.asset_name # UE5.1+ usage, or asset_class for older
        # Fallback for older python API if needed, but asset_class_path is standard in modern UE5
        if not c_name: c_name = asset.asset_class
        
        c_name = str(c_name)
        if c_name not in counts:
            counts[c_name] = 0
        counts[c_name] += 1
        
    # Sort and print
    unreal.log("=== Asset Counts by Class ===")
    for type_name, count in sorted(counts.items(), key=lambda item: item[1], reverse=True):
        unreal.log(f"{type_name}: {count}")
    
    unreal.log(f"Total Assets: {len(assets)}")

if __name__ == "__main__":
    count_assets()
