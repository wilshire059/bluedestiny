"""Debug script to see what's happening with AC_ActionManager extraction."""
import json

with open('Saved/NodeToCode/ExportedBlueprints/AC_ActionManager.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

cd = data.get('classDefaults', {})
print(f"Class defaults has {len(cd)} properties")
print(f"Properties: {list(cd.keys())}\n")

found_props = {}
for g in data.get('graphs', []):
    print(f"Checking graph: {g.get('name')}")
    for n in g.get('nodes', []):
        vn = n.get('memberName', '')
        if vn and vn in cd and n.get('nodeType') in ['VariableGet', 'VariableSet']:
            for p in n.get('outputPins', []):
                pn = p.get('name', '')
                if pn == vn or (not pn and n.get('nodeType') == 'VariableGet'):
                    found_props[vn] = {
                        'type': p.get('type'),
                        'subType': p.get('subType'),
                        'isArray': p.get('bIsArray'),
                        'isMap': p.get('bIsMap'),
                        'isSet': p.get('bIsSet')
                    }
                    print(f"  Found {vn}: {found_props[vn]}")
                    break

print(f"\nTotal found in graphs: {len(found_props)}")
print(f"Missing from graphs: {set(cd.keys()) - set(found_props.keys())}")
