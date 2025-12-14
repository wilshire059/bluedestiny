"""
Clean Generator - FIXED Collection Type Extraction
Based on working test_collection_extraction.py
"""
import json, os, re
from pathlib import Path

EXPORT_DIR = Path("C:/scripts/BlueDestiny/Saved/NodeToCode/ExportedBlueprints")
OUTPUT_BASE = Path("C:/scripts/BlueDestiny/Source/SLF_5_7/Generated")

def extract_properties(data):
    """Extract properties with correct collection types."""
    props = {}
    cd = data.get('classDefaults', {})
    
    for g in data.get('graphs', []):
        for n in g.get('nodes', []):
            if n.get('nodeType') not in ['VariableGet', 'VariableSet']:
                continue
            
            vn = n.get('memberName', '')
            if not vn or vn not in cd:
                continue
                
            for p in n.get('outputPins', []):
                pn = p.get('name', '')
                if pn == vn or (not pn and n.get('nodeType') == 'VariableGet'):
                    # Get type info
                    t = p.get('type', '')
                    st = p.get('subType', '')
                    ia = p.get('bIsArray', False)
                    im = p.get('bIsMap', False)
                    is_ = p.get('bIsSet', False)
                    
                    # Build base type - PROPER TYPE CONVERSION
                    bt = ''
                    if t == "Struct":
                        bt = f"F{st}" if st and not st.startswith("F") else st
                    elif t == "Object":
                        if st:
                            if st.startswith("B_"):
                                bt = f"A{st}*"
                            elif st.startswith("PDA_"):
                                bt = f"U{st}*"
                            else:
                                bt = f"U{st}*" if not st.startswith("U") else f"{st}*"
                        else:
                            bt = "UObject*"
                    else:
                        bt = t if t else "UObject*"
                    
                    # Apply collection wrappers - THE FIX!
                    if im:
                        kt = p.get('keyType', '')
                        ktn = p.get('keyTypeName', '')
                        kc = "int32"
                        if kt == "Struct" and ktn:
                            kc = f"F{ktn}" if not ktn.startswith("F") else ktn
                        elif kt == "Name":
                            kc = "FName"
                        ft = f"TMap<{kc}, {bt}>"
                    elif is_:
                        ft = f"TSet<{bt}>"
                    elif ia:
                        ft = f"TArray<{bt}>"
                    else:
                        ft = bt
                    
                    props[vn] = ft
                    break
    
    # Fallback for properties not in graphs
    for pn in cd:
        if pn not in props:
            props[pn] = "UObject*"
    
    return props

def gen_header(name, data):
    """Generate C++ header."""
    par = "UAnimInstance" if name.startswith("ABP_") else "UActorComponent" if name.startswith("AC_") else "AActor"
    pre = "A" if par.startswith("A") else "U"
    cn = f"{pre}{name}"
    
    h = f'#pragma once\n#include "CoreMinimal.h"\n#include "{name}.generated.h"\nUCLASS()\nclass {cn} : public {par} {{\n\tGENERATED_BODY()\npublic:\n\t{cn}();\n'
    
    for pn, pt in sorted(extract_properties(data).items()):
        sn = pn.replace(" ", "").replace("?", "").replace("-", "_")
        pt = re.sub(r"_C(?=\W|$)", "", pt)  # Clean _C suffix
        h += f'\tUPROPERTY() {pt} {sn};\n'
    
    return h + "};\n"

def gen_source(name):
    """Generate C++ source."""
    par = "UAnimInstance" if name.startswith("ABP_") else "UActorComponent" if name.startswith("AC_") else "AActor"
    pre = "A" if par.startswith("A") else "U"
    cn = f"{pre}{name}"
    return f'#include "{name}.h"\n{cn}::{cn}() {{ }}\n'

def main():
    """Generate all C++ files."""
    print("=== Clean Generator - WITH COLLECTION TYPE FIX ===\n")
    
    (OUTPUT_BASE / "Classes").mkdir(parents=True, exist_ok=True)
    (OUTPUT_BASE / "Private").mkdir(parents=True, exist_ok=True)
    
    with open("C:/scripts/BlueDestiny/analysis_output.json", 'r') as f:
        am = json.load(f)
    
    gen = 0
    for n, a in am.items():
        if a['type'] in ["Enum", "Struct"]:
            continue
        
        jp = EXPORT_DIR / f"{n}.json"
        if not jp.exists():
            continue
        
        with open(jp, 'r') as f:
            d = json.load(f)
        
        with open(OUTPUT_BASE / "Classes" / f"{n}.h", 'w') as f:
            f.write(gen_header(n, d))
        with open(OUTPUT_BASE / "Private" / f"{n}.cpp", 'w') as f:
            f.write(gen_source(n))
        
        gen += 1
        if gen % 50 == 0:
            print(f"Generated {gen} files...")
    
    print(f"\n✓ Generated {gen} C++ files with CORRECT collection types!")

if __name__ == "__main__":
    main()
