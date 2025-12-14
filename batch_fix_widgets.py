#!/usr/bin/env python3
"""Batch fix W_ (Widget) files - type prefix fixes"""
import os
import re
import glob

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"
w_files = glob.glob(os.path.join(base_path, "W_*.h"))

def fix_widget_file(filepath):
    """Fix type prefixes in Widget files"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Fix UObject types (widgets, components, etc.)
    content = re.sub(r'\b(?<!U)(Object\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(UserWidget\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(Widget\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(WidgetAnimation\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(WidgetComponent\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SoundBase\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(MaterialInterface\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(Texture2D\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(UserWidgetExtension\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(DragDropOperation\*)', r'U\1', content)
    
    # Fix UMG widget types
    content = re.sub(r'\b(?<!U)(WidgetSwitcher\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(VerticalBox\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(HorizontalBox\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(CanvasPanel\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(GridPanel\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(Overlay\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(SizeBox\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(Image\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(TextBlock\*)', r'U\1', content)
    content = re.sub(r'\b(?<!U)(Button\*)', r'U\1', content)
    
    # Fix custom widget types (W_*)
    content = re.sub(r'\b(W_[A-Za-z_]*)\*', r'U\1*', content)
    
    # Fix PDA types
    content = re.sub(r'\b(?<!U)(PDA_[A-Za-z_]*)\*', r'U\1*', content)
    
    # Fix AB_ types (Blueprint actors)
    content = re.sub(r'\b(AB_[A-Za-z_]*)\*', r'A\1*', content)
    
    # Fix Actor/Pawn/Controller types
    content = re.sub(r'\b(?<!A)(Actor\*)(?!>)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(Pawn\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(PlayerController\*)', r'A\1', content)
    content = re.sub(r'\b(?<!A)(PlayerCameraManager\*)', r'A\1', content)
    
    # Fix B_Stat types
    content = re.sub(r'\b(B_Stat\*)', r'A\1', content)
    
    # Fix struct types
    content = re.sub(r'\b(?<!F)(GameplayTag\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Vector\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Vector2D\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(LinearColor\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Geometry\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Margin\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(Anchors\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(SlateColor\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(PointerEvent\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(KeyEvent\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(CharacterEvent\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(FocusEvent\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(MotionEvent\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(AnalogInputEvent\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(PaintContext\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(EventReply\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(WidgetAnimationDynamicEvent\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(OnInputAction\b)', r'F\1', content)
    content = re.sub(r'\b(?<!F)(WidgetAnimationHandle\b)', r'F\1', content)
    
    # Fix TSubclassOf template arguments
    content = re.sub(r'TSubclassOf<(?!U|A)B_Stat>', 'TSubclassOf<AB_Stat>', content)
    content = re.sub(r'TSubclassOf<(?!U)UserWidgetExtension>', 'TSubclassOf<UUserWidgetExtension>', content)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return os.path.basename(filepath)

# Process all Widget files
print(f"\n=== Processing {len(w_files)} Widget (W_*) files ===")
print("Fixing type prefixes in all widget files\n")

fixed_count = 0
for filepath in sorted(w_files):
    filename = fix_widget_file(filepath)
    print(f"✓ Fixed: {filename}")
    fixed_count += 1
    
    if fixed_count % 25 == 0:
        print(f"  ... {fixed_count}/{len(w_files)} files processed")

print(f"\n✅ All {len(w_files)} Widget files fixed!")
