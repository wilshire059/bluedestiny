"""
Enhanced Property Type Extractor

This script reads JSON exports directly and properly extracts variable types
INCLUDING collection flags (bIsArray, bIsMap, bIsSet) to build a complete
type database for accurate C++ generation.
"""

import json
import os
from pathlib import Path
from collections import defaultdict

EXPORT_DIR = Path("C:/scripts/BlueDestiny/Saved/NodeToCode/ExportedBlueprints")
OUTPUT_FILE = "enhanced_analysis.json"

def extract_variables_from_graph(data):
    """
    Extract variables with full type information from graph analysis.
    Looks at graphs to find variable get/set nodes and their types.
    """
    variables = {}
    
    # Check graphs for variable usage
    for graph in data.get('graphs', []):
        for node in graph.get('nodes', []):
            node_type = node.get('nodeType', '')
            
            if node_type in ['VariableGet', 'VariableSet']:
                var_name = node.get('name', '')
                member_parent = node.get('memberParent', '')
                
                # Get type from member_parent (e.g., "bool", "struct/Vector", "object/Actor")
                if var_name and member_parent and var_name not in variables:
                    # For now, just record the basic type
                    # We'll get collection info from functions section
                    variables[var_name] = member_parent
    
    return variables

def extract_from_functions(data):
    """
    Extract property types from the functions section.
    The functions section contains full type info including collection flags.
    """
    properties = {}
    
    for func in data.get('functions', []):
        # Check outputs - these become properties or function parameters
        for output in func.get('outputs', []):
            prop_name = output.get('name', '')
            
            # Skip internal/temporary variables
            if prop_name.startswith(('CallFunc_', 'Temp_', 'K2Node_', 'LOCAL_', 'Cache_')):
                continue
            
            if not prop_name:
                continue
                
            prop_type = output.get('type', '')
            typename = output.get('typeName', '')
            is_array = output.get('bIsArray', False)
            is_map = output.get('bIsMap', False)
            is_set = output.get('bIsSet', False)
            key_type = output.get('keyType', '')
            key_typename = output.get('keyTypeName', '')
            
            # Build complete type info
            type_info = {
                'type': prop_type,
                'typeName': typename,
                'isArray': is_array,
                'isMap': is_map,
                'isSet': is_set
            }
            
            if is_map:
                type_info['keyType'] = key_type
                type_info['keyTypeName'] = key_typename
            
            properties[prop_name] = type_info
                
    return properties

def extract_from_class_defaults(data):
    """
    Get properties from classDefaults section.
    This tells us which properties actually exist in the class.
    """
    class_defaults = data.get('classDefaults', {})
    return list(class_defaults.keys())

def process_blueprint(filepath):
    """
    Process a single blueprint JSON export.
    """
    if not filepath.exists():
        return None
    
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except:
        return None
    
    metadata = data.get('metadata', {})
    bp_name = metadata.get('blueprintClass', filepath.stem)
    bp_type = metadata.get('blueprintType', 'Unknown')
    
    # Get actual properties from classDefaults
    default_props = extract_from_class_defaults(data)
    
    # Get type info from functions section
    func_properties = extract_from_functions(data)
    
    # Get variables from graphs
    graph_variables = extract_variables_from_graph(data)
    
    # Merge: prioritize classDefaults for what exists, func_properties for types
    final_properties = {}
    
    for prop_name in default_props:
        if prop_name in func_properties:
            final_properties[prop_name] = func_properties[prop_name]
        elif prop_name in graph_variables:
            # Create basic type info from graph data
            final_properties[prop_name] = {
                'type': graph_variables[prop_name].split('/')[-1] if '/' in graph_variables[prop_name] else graph_variables[prop_name],
                'typeName': graph_variables[prop_name],
                'isArray': False,
                'isMap': False,
                'isSet': False
            }
        else:
            # Unknown - will need manual review
            final_properties[prop_name] = {
                'type': 'Unknown',
                'typeName': '',
                'isArray': False,
                'isMap': False,
                'isSet': False
            }
    
    return {
        'name': bp_name,
        'type': bp_type,
        'properties': final_properties
    }

def main():
    print("=== Enhanced Property Type Extraction ===\n")
    
    results = {}
    processed = 0
    
    # Get all JSON files
    json_files = list(EXPORT_DIR.glob("*.json"))
    
    for json_file in json_files:
        result = process_blueprint(json_file)
        
        if result:
            results[result['name']] = result
            processed += 1
            
        if processed % 50 == 0:
            print(f"Processed {processed}/{len(json_files)} files...")
    
    # Save results
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        json.dump(results, f, indent=2)
    
    print(f"\n✓ Processed {processed} blueprints")
    print(f"✓ Saved to {OUTPUT_FILE}")
    
    # Print some statistics
    print("\n=== Statistics ===")
    
    array_count = 0
    map_count = 0
    set_count = 0
    
    for bp_name, bp_data in results.items():
        for prop_name, prop_info in bp_data.get('properties', {}).items():
            if prop_info.get('isArray'): array_count += 1
            if prop_info.get('isMap'): map_count += 1
            if prop_info.get('isSet'): set_count += 1
    
    print(f"Found {array_count} TArray properties")
    print(f"Found {map_count} TMap properties")
    print(f"Found {set_count} TSet properties")
    
    return 0

if __name__ == "__main__":
    exit(main())
