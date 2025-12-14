"""
Compare NodeToCode JSON exports with Component Exports to find missing files.
"""

import os
import json

# Paths
NODETOCODE_DIR = r"c:\scripts\BlueDestiny\Plugins\NodeToCode\ExportedBlueprints"
COMPONENT_EXPORT_DIR = r"C:\scripts\BlueDestiny\Saved\BlueprintComponentExports"

def get_nodetocode_names():
    """Get all blueprint names from NodeToCode exports."""
    names = set()
    for f in os.listdir(NODETOCODE_DIR):
        if f.endswith('.json'):
            names.add(f.replace('.json', ''))
    return names

def get_component_export_names():
    """Get all blueprint names from Component exports."""
    names = set()
    summary_path = os.path.join(COMPONENT_EXPORT_DIR, "_export_summary.json")
    
    if os.path.exists(summary_path):
        with open(summary_path, 'r') as f:
            data = json.load(f)
            for filepath in data.get("ExportedFiles", []):
                # Extract just the blueprint name from the path
                basename = os.path.basename(filepath).replace('.json', '')
                # The component export uses full path as name, extract last part
                parts = basename.split('_')
                # Find the actual blueprint name (last meaningful part)
                names.add(basename)
    return names

def extract_bp_name_from_component_export(filename):
    """Extract the blueprint name from a component export filename."""
    # Format: SoulslikeFramework_Blueprints__WorldActors_LevelDesign_B_Destructible
    # We need to extract: B_Destructible
    parts = filename.split('_')
    # Find known prefixes
    prefixes = ['B_', 'W_', 'AC_', 'BPI_', 'ABP_', 'PDA_', 'AN_', 'ANS_', 'BTS_', 'BTT_', 
                'BFL_', 'BML_', 'GI_', 'GM_', 'GS_', 'PC_', 'PS_', 'SG_', 'CS_', 'CR_',
                'E_', 'EUW_', 'EUO_', 'ALI_', 'AIC_', 'F']
    
    for i, part in enumerate(parts):
        for prefix in prefixes:
            if part.startswith(prefix.split('_')[0]) or part == prefix.rstrip('_'):
                # Found a likely blueprint name start
                return '_'.join(parts[i:])
    
    # Fallback: return last parts
    return parts[-1] if parts else filename

def main():
    print("="*60)
    print("Blueprint Graph Logic Coverage Check")
    print("="*60)
    
    # Get NodeToCode exports
    nodetocode_names = get_nodetocode_names()
    print(f"\nNodeToCode exports: {len(nodetocode_names)}")
    
    # Get component exports and extract names
    component_exports = set()
    summary_path = os.path.join(COMPONENT_EXPORT_DIR, "_export_summary.json")
    
    with open(summary_path, 'r') as f:
        data = json.load(f)
        for filepath in data.get("ExportedFiles", []):
            basename = os.path.basename(filepath).replace('.json', '')
            bp_name = extract_bp_name_from_component_export(basename)
            component_exports.add(bp_name)
    
    print(f"Component exports (unique BP names): {len(component_exports)}")
    
    # Compare
    in_components_not_nodetocode = []
    in_nodetocode_not_components = []
    
    # For each component export, check if there's a matching NodeToCode export
    for comp_name in component_exports:
        found = False
        for ntc_name in nodetocode_names:
            if ntc_name in comp_name or comp_name in ntc_name or ntc_name == comp_name:
                found = True
                break
        if not found:
            in_components_not_nodetocode.append(comp_name)
    
    # For each NodeToCode export, check if there's a matching component export
    for ntc_name in nodetocode_names:
        found = False
        for comp_name in component_exports:
            if ntc_name in comp_name or comp_name in ntc_name or ntc_name == comp_name:
                found = True
                break
        if not found:
            in_nodetocode_not_components.append(ntc_name)
    
    print(f"\n")
    print("="*60)
    print("RESULTS")
    print("="*60)
    
    if in_components_not_nodetocode:
        print(f"\n[!] In Component Exports but NOT in NodeToCode ({len(in_components_not_nodetocode)}):")
        for name in sorted(in_components_not_nodetocode)[:20]:
            print(f"  - {name}")
        if len(in_components_not_nodetocode) > 20:
            print(f"  ... and {len(in_components_not_nodetocode) - 20} more")
    
    if in_nodetocode_not_components:
        print(f"\n[!] In NodeToCode but NOT in Component Exports ({len(in_nodetocode_not_components)}):")
        for name in sorted(in_nodetocode_not_components)[:20]:
            print(f"  - {name}")
        if len(in_nodetocode_not_components) > 20:
            print(f"  ... and {len(in_nodetocode_not_components) - 20} more")
    
    if not in_components_not_nodetocode and not in_nodetocode_not_components:
        print("\n[OK] All blueprints have both graph logic AND component exports!")
    
    # Summary
    print(f"\n")
    print("="*60)
    print("SUMMARY")
    print("="*60)
    print(f"NodeToCode (graph logic): {len(nodetocode_names)} files")
    print(f"Component Exports:        {len(component_exports)} unique blueprints")
    print(f"Missing from NodeToCode:  {len(in_components_not_nodetocode)}")
    print(f"Missing from Components:  {len(in_nodetocode_not_components)}")

if __name__ == "__main__":
    main()
