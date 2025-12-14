"""
Quick script to find where AvailableActions property is defined in the JSON
with its collection type flags.
"""
import json

# Load the JSON
with open('Saved/NodeToCode/ExportedBlueprints/AC_ActionManager.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

# Search graph nodes
print("=== Searching Graph Nodes for AvailableActions ===\n")
for graph in data.get('graphs', []):
    for node in graph.get('nodes', []):
        member_name = node.get('memberName', '')
        if member_name == 'AvailableActions':
            print(f"Found in graph '{graph.get('name')}':")
            print(f"  Node Type: {node.get('nodeType')}")
            print(f"  Member Parent: {node.get('memberParent')}")
            
            # Check output pins
            for pin in node.get('outputPins', []):
                pin_name = pin.get('name', '')
                if 'Available' in pin_name or pin_name == member_name:
                    print(f"\n  Output Pin '{pin_name}':")
                    print(f"    Type: {pin.get('type')}")
                    print(f"    SubType: {pin.get('subType')}")
                    print(f"    bIsArray: {pin.get('bIsArray')}")
                    print(f"    bIsMap: {pin.get('bIsMap')}")
                    print(f"    bIsSet: {pin.get('bIsSet')}")
            print()

# Also check classDefaults to see the actual value
print("\n=== Class Defaults Value ===")
class_defaults = data.get('classDefaults', {})
if 'AvailableActions' in class_defaults:
    print(f"AvailableActions = {class_defaults['AvailableActions']}")
