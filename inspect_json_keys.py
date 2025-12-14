import json

def inspect():
    with open(r"c:\scripts\BlueDestiny\Plugins\NodeToCode\ExportedBlueprints\AC_StatManager.json", "r", encoding="utf-8") as f:
        data = json.load(f)
    print("Keys:", data.keys())
    
    if "variables" in data:
        print(f"Found 'variables': {len(data['variables'])} items")
    if "Properties" in data:
        print(f"Found 'Properties': {len(data['Properties'])} items")
    if "Functions" in data:
        print(f"Found 'Functions': {len(data['Functions'])} items")
    if "functions" in data:
        print(f"Found 'functions': {len(data['functions'])} items")

if __name__ == "__main__":
    inspect()
