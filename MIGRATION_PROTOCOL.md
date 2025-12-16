# STRICT MIGRATION PROTOCOL - READ BEFORE EVERY MIGRATION

## CRITICAL REMINDER (READ THIS FIRST EVERY TIME)
**STOP! Before migrating ANY file, you MUST:**
1. Read this ENTIRE protocol
2. Read the full NodeToCode JSON (use offset/limit if needed)
3. Read ALL BlueprintComponentExport files for defaults
4. Document EVERY graph, function, event, property in the JSON
5. Migrate EVERYTHING - no shortcuts, no summaries, no skipping

## The Problem We're Fixing
Previous migrations only captured a FRACTION of the Blueprint logic. For example, AC_ActionManager had 11 graphs but only 3 functions were migrated. This is UNACCEPTABLE.

## Strict Migration Steps (FOLLOW EXACTLY)

### Step 1: Pre-Migration Analysis
```
For each Blueprint to migrate:
1. READ the full NodeToCode JSON at: Plugins/NodeToCode/ExportedBlueprints/{Name}.json
2. DOCUMENT every single:
   - Graph (EventGraph, Function, Macro, Composite)
   - Custom Event
   - Function
   - Variable/Property
   - Delegate
   - Interface implementation
3. READ the BlueprintComponentExports at: Saved/BlueprintComponentExports/*{Name}*.json
4. DOCUMENT all default values
```

### Step 2: Compare Against Existing C++
```
If C++ file already exists:
1. READ the existing .h and .cpp files
2. CREATE a checklist comparing JSON contents vs C++ contents
3. IDENTIFY everything that is MISSING
4. The goal is 100% parity - not "good enough"
```

### Step 3: Migration Implementation
```
1. CREATE/UPDATE the .h file with ALL:
   - Properties (with correct UPROPERTY specifiers)
   - Function declarations (with correct UFUNCTION specifiers)
   - Delegate declarations
   - Enum declarations (if inline)

2. CREATE/UPDATE the .cpp file with ALL:
   - Constructor with ALL default values from BlueprintComponentExports
   - EVERY function implementation from the JSON
   - EVERY event handler
   - ALL logic branches - do not simplify or summarize
```

### Step 4: Verification
```
1. COMPILE using: CompileBatch18.bat
2. FIX any errors
3. RE-READ the JSON to verify nothing was missed
4. UPDATE the tracker
```

### Step 5: Commit
```
1. git add -A
2. git commit with descriptive message listing ALL functions migrated
3. git push
```

## JSON Structure Reference
```json
{
  "graphs": [
    {
      "name": "GraphName",
      "graphType": "EventGraph|Function|Macro|Composite",
      "nodes": [
        {
          "nodeType": "CustomEvent|CallFunction|FunctionEntry|...",
          "name": "NodeName",
          "inputPins": [...],
          "outputPins": [...]
        }
      ]
    }
  ],
  "variables": [...],
  "delegates": [...]
}
```

## Common Node Types to Handle
- **CustomEvent**: Becomes a UFUNCTION with appropriate specifiers (Server, Client, NetMulticast)
- **FunctionEntry**: Start of a BlueprintCallable function
- **CallFunction**: Calling another function - translate to C++ equivalent
- **Branch**: if/else statement
- **Sequence**: Multiple execution paths
- **ForEachLoop**: Range-based for loop
- **MacroInstance**: Inline the macro logic
- **Composite**: Collapsed graph - expand and migrate all contents

## DO NOT:
- Skip "simple" functions
- Summarize complex logic
- Leave TODOs for "later"
- Assume existing C++ is complete
- Rush through large files
- Ignore Composite graphs (they contain real logic!)

## QUALITY CHECKLIST (Verify for EVERY migration)
- [ ] Read complete JSON (all sections, use pagination if needed)
- [ ] Documented all graphs in JSON
- [ ] Read BlueprintComponentExports for defaults
- [ ] All variables migrated with correct types
- [ ] All functions migrated with full logic
- [ ] All events migrated (Begin Play, Tick, custom events)
- [ ] All delegates declared and broadcast correctly
- [ ] All RPC functions have correct specifiers (Server, Client, NetMulticast, Reliable/Unreliable)
- [ ] Default values set in constructor
- [ ] Compiles without errors
- [ ] Committed to git

## File Locations
- **NodeToCode JSONs**: `C:\scripts\BlueDestiny\Plugins\NodeToCode\ExportedBlueprints\`
- **BlueprintComponentExports**: `C:\scripts\BlueDestiny\Saved\BlueprintComponentExports\`
- **C++ Output**: `C:\scripts\BlueDestiny\Source\SLF_5_7\Converted\`
- **This Protocol**: `C:\scripts\BlueDestiny\MIGRATION_PROTOCOL.md`
- **Progress Tracker**: `C:\scripts\BlueDestiny\MIGRATION_PROGRESS.md`

## Emergency Recovery
If context compacts and you lose track:
1. Read MIGRATION_PROTOCOL.md (this file)
2. Read MIGRATION_PROGRESS.md to see where you left off
3. Continue from the last incomplete item
4. DO NOT start over - continue from checkpoint
