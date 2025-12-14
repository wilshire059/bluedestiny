import os
import json
import re

JSON_DIR = r"Plugins/NodeToCode/ExportedBlueprints"

def get_json_path(filename):
    # filename e.g. B_Door.h -> B_Door.json
    base = os.path.splitext(filename)[0]
    # Search recursively in JSON dir
    for root, dirs, files in os.walk(JSON_DIR):
        for f in files:
            if f.lower() == f"{base.lower()}.json":
                return os.path.join(root, f)
    return None

def count_properties_functions_in_json(json_path):
    try:
        with open(json_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except Exception as e:
        return 0, 0

    props = len(data.get("variables", []))
    funcs = len(data.get("functions", []))
    # events might be in graphs
    events = 0
    for graph in data.get("graphs", []):
         # naive count of event nodes
         pass 
    return props, funcs

def count_in_cpp(file_path):
    if not os.path.exists(file_path):
        return 0, 0
    
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    # Heuristic: Count UPROPERTY and UFUNCTION lines
    props = len(re.findall(r'UPROPERTY\(', content))
    funcs = len(re.findall(r'UFUNCTION\(', content))
    return props, funcs

def validate():
    with open("current_duplicates.txt", 'r', encoding='utf-8') as f:
        lines = f.readlines()
    
    results = []
    
    current_file = None
    manual_path = None
    generated_path = None
    
    for line in lines:
        line = line.strip()
        if not line: continue
        
        if not line.startswith("Manual:") and not line.startswith("Generated:"):
            # New file block
            if current_file and manual_path and generated_path:
                results.append((current_file, manual_path, generated_path))
            current_file = line
            manual_path = None
            generated_path = None
        elif line.startswith("Manual:"):
            manual_path = line.split(":", 1)[1].strip()
        elif line.startswith("Generated:"):
            generated_path = line.split(":", 1)[1].strip()

    if current_file and manual_path and generated_path:
        results.append((current_file, manual_path, generated_path))

    print(f"Validating {len(results)} pairs...")

    with open("validation_report.txt", "w", encoding="utf-8") as out:
        for filename, man_p, gen_p in results:
             json_p = get_json_path(filename)
             if not json_p:
                 out.write(f"SKIP {filename}: No JSON found\n")
                 continue
             
             j_props, j_funcs = count_properties_functions_in_json(json_p)
             
             m_props, m_funcs = count_in_cpp(man_p)
             g_props, g_funcs = count_in_cpp(gen_p)
             
             # Calculate delta
             m_delta = abs(j_props - m_props) + abs(j_funcs - m_funcs)
             g_delta = abs(j_props - g_props) + abs(j_funcs - g_funcs)
             
             winner = "Manual"
             if g_delta < m_delta:
                 winner = "Generated"
            
             # Bias towards Manual if close (tie goes to Manual)
             if m_delta <= g_delta:
                 winner = "Manual"

             out.write(f"FILE {filename}\n")
             out.write(f"  JSON: P={j_props} F={j_funcs}\n")
             out.write(f"  Manual: P={m_props} F={m_funcs} (Delta {m_delta})\n")
             out.write(f"  Generated: P={g_props} F={g_funcs} (Delta {g_delta})\n")
             out.write(f"  WINNER: {winner}\n")
             out.write(f"  Path to keep: {man_p if winner == 'Manual' else gen_p}\n")
             out.write(f"  Path to archive: {gen_p if winner == 'Manual' else man_p}\n")
             out.write("\n")

if __name__ == "__main__":
    validate()
