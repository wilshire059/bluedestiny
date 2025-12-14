import os
import re

SOURCE_DIR = r"Source/SLF_5_7/ManualConversion"

# Build mappings from file basename to actual relative path
def build_file_map():
    """Build a map of filename to relative path from ManualConversion."""
    file_map = {}
    for root, dirs, files in os.walk(SOURCE_DIR):
        for filename in files:
            if filename.endswith('.h'):
                rel_path = os.path.relpath(os.path.join(root, filename), SOURCE_DIR)
                rel_path = rel_path.replace('\\', '/')
                file_map[filename] = rel_path
    return file_map

def get_correct_include(include_path, current_folder, file_map):
    """Given an include path, determine the correct path."""
    # Extract just the filename
    basename = os.path.basename(include_path.strip('"'))
    
    if basename in file_map:
        target_path = file_map[basename]
        target_folder = os.path.dirname(target_path)
        
        # Calculate relative path from current folder
        if current_folder == target_folder:
            # Same folder, just use filename
            return f'"{basename}"'
        else:
            # Different folder, need relative path
            # From current_folder to ManualConversion root, then to target
            up_count = current_folder.count('/') + 1 if current_folder else 0
            up_path = '../' * up_count
            return f'"{up_path}{target_path}"'
    
    return None  # Not found, leave as is

def fix_includes():
    """Fix include paths in all C++ files."""
    file_map = build_file_map()
    print(f"Found {len(file_map)} header files")
    
    count = 0
    
    for root, dirs, files in os.walk(SOURCE_DIR):
        for filename in files:
            if not (filename.endswith('.h') or filename.endswith('.cpp')):
                continue
                
            filepath = os.path.join(root, filename)
            current_folder = os.path.relpath(root, SOURCE_DIR).replace('\\', '/')
            if current_folder == '.':
                current_folder = ''
                
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
                
            original = content
            
            # Find all includes that might be wrong
            include_pattern = r'#include\s+"([^"]+)"'
            
            def replace_include(match):
                include_path = match.group(1)
                basename = os.path.basename(include_path)
                
                # Skip system includes and already correct includes
                if '/' not in include_path and '\\' not in include_path:
                    # Simple filename - check if it exists in file_map
                    if basename in file_map:
                        target_path = file_map[basename]
                        target_folder = os.path.dirname(target_path)
                        
                        if current_folder == target_folder:
                            return f'#include "{basename}"'
                        else:
                            # Need relative path
                            up_count = current_folder.count('/') + 1 if current_folder else 0
                            rel_path = '../' * up_count + target_path
                            return f'#include "{rel_path}"'
                    return match.group(0)  # Not found, leave as is
                
                # Path include - check if basename exists and path is wrong
                if basename in file_map and not include_path.endswith('.generated.h'):
                    # Check if current path resolves correctly
                    target_path = file_map[basename]
                    target_folder = os.path.dirname(target_path)
                    
                    if current_folder == target_folder:
                        return f'#include "{basename}"'
                    else:
                        up_count = current_folder.count('/') + 1 if current_folder else 0
                        rel_path = '../' * up_count + target_path
                        return f'#include "{rel_path}"'
                
                return match.group(0)  # Leave as is
                
            content = re.sub(include_pattern, replace_include, content)
                    
            if content != original:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                print(f"Fixed: {filename}")
                count += 1
                
    print(f"\nDone. Fixed {count} files.")

if __name__ == "__main__":
    fix_includes()
