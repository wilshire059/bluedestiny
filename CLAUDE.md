# Soulslike Framework Migration Status (Handoff)

## Project Overview
**Goal**: Migrate all Blueprints to C++ for Unreal Engine 5.7.
**Current Phase**: System Widgets & Core Classes (Completed).
**Immediate Next Step**: Reparenting of System Widgets and final verification.

## Migration Tracker
**Total Scope**: 438 Blueprints (Source: `Plugins/NodeToCode/ExportedBlueprints`)
**Migrated**: ~144 Files | **Skip**: 16 (Editor-only) | **Remaining**: ~278
**Progress**: ~32% (excluding skipped)

### Comprehensive Tracker Files
- **Full Tracker**: `migration_tracker_full.md` - Every item with checkbox (NEVER truncate, only check off)
- **Backup List**: `migration_tracker_backup.md` - Raw list of all 438 blueprints

| Category | Total | Migrated | Status |
|----------|-------|----------|--------|
| Enums | 37 | 26 | 70% |
| Structs | 27+ | 27 | 100% |
| Interfaces | 20 | 15 | 75% |
| DataAssets | 24 | 21 | 88% |
| Components | 17 | 15 | 88% |
| Classes/Actors | 109 | 21 | 19% |
| Widgets | 101 | 17 | 17% |
| Animation | 30 | 0 | 0% |
| AI (BT) | 19 | 0 | 0% |
| Game Framework | 9 | 2 | 22% |
| Editor Utils | 16 | 0 | SKIP |
| Other | 9 | 0 | 0% |
| **Total** | **438** | **~144** | **~32%** |

## File Locations (Dual-Source Protocol)
**CRITICAL**: You must use BOTH data sources to ensure high-quality migration.

1.  **Structure & Logic Source (NodeToCode)**
    *   **Path**: `c:\scripts\BlueDestiny\Plugins\NodeToCode\ExportedBlueprints`
    *   **Count**: 438 Files.
    *   **Use for**: Graphs, Nodes, Function Signatures, Logic flow. This is the primary source for C++ implementation.

2.  **Property & Defaults Source (Bulk Export)**
    *   **Path**: `c:\scripts\BlueDestiny\Saved\BlueprintComponentExports`
    *   **Count**: 801 Files.
    *   **Use for**: Verifying precise default values (CDO) that the user had set in Blueprint.
    *   **Action**: You MUST cross-reference this to see if the C++ constructor needs to set specific default values (e.g., `MaxHealth = 500`).

## Required Output: Manual Update Guide
The user specifically requested that you creating a `manual_update_guide.md`.
*   **Purpose**: List properties that cannot be automatically reparented or set in C++ constructors easily (e.g., Scene Component relative locations, specific Actor tags, complex struct defaults).
*   **Source**: Compare the `BlueprintComponentExports` values against your C++ defaults. If they differ, add them to the guide so the user knows to check them in the Editor after reparenting.

- **Output (C++)**: `c:\scripts\BlueDestiny\Source\SLF_5_7\Converted`

## Automated Migration Workflow (MANDATORY)

**CRITICAL RULES:**
1. **NEVER truncate `migration_tracker_full.md`** - Only update checkboxes `[ ]` → `[x]`
2. **Always use BOTH data sources** when converting
3. **Commit after each successful migration**

### Per-Item Migration Steps:

```
1. READ SOURCE FILES
   - NodeToCode JSON: Plugins/NodeToCode/ExportedBlueprints/{Name}.json
   - Bulk Export: Saved/BlueprintComponentExports/*{Name}*.json (for defaults)

2. CONVERT TO C++
   - Create .h and .cpp in Source/SLF_5_7/Converted/{Category}/
   - Target: Unreal Engine 5.7
   - Cross-reference defaults from Bulk Export

3. COMPILE
   - Run: CompileBatch18.bat (single-threaded, avoids OOM)
   - Fix any errors before proceeding

4. COMMIT TO GITHUB
   - git add -A
   - git commit -m "Migrate {ClassName} to C++"
   - git push

5. UPDATE TRACKER
   - Edit migration_tracker_full.md
   - Change [ ] to [x] for completed item
   - Update summary counts in CLAUDE.md if needed
```

### Git Configuration
- **Repository**: https://github.com/wilshire059/bluedestiny.git
- **Account**: wilshire059
- **Remote URL**: https://wilshire059@github.com/wilshire059/bluedestiny.git
- **Content folder**: EXCLUDED (2.6GB - stays local only)

## Recent Accomplishments (System Batch)
We just completed the migration of the Save/Load system and Main Menus.
**Created Classes**:
-   `BPI_GameInstance`: Interface for game instance operations.
-   `SG_SoulslikeFramework`: SaveGame object.
-   `GI_SoulslikeFramework`: GameInstance implementation (partial SaveSlot logic).
-   `AC_SaveLoadManager`: ActorComponent handling save/load requests.
-   `UW_GameMenu`: Main menu widget logic.
-   `UW_GameMenu_Button`: Menu button logic.
-   `UW_InventoryAction` & `UW_InventoryActionAmount`: Action hints.

## Technical Debt & Known Issues (CRITICAL)

### 1. W_Status / NativeOnVisibilityChanged
**Issue**: `UW_Status` (and `UW_GameMenu`) originally overrode `NativeOnVisibilityChanged`. This caused compilation errors in the current UE 5.7 context (potentially due to base class `UW_UserWidget_Base` or strictness changes).
**Workaround**: The override was commented out in `W_Status.cpp` and `W_Status.h`.
**Action Required**: Investigate proper visibility event handling if visual bugs occur (e.g., Fade animation not playing).

### 2. Compiler Cache / Shadowing (C4458)
**Issue**: We encountered a persistent `C4458 (declaration hides class member)` error in `W_Status.cpp` regarding the variable `StatManager`.
**Resolution**: We renamed the local variable to `LocalStatManager`.
**Anomaly**: The compiler continued to report the error *after* the fix was applied on disk. We had to:
1.  Delete `W_Status.cpp`.
2.  Run a failing build.
3.  Recreate `W_Status.cpp` with the fix.
4.  Recompile.
**Takeaway**: If you see "impossible" errors, assume the Intermediate cache is corrupted/stale and force a file flush.

### 3. Build Environment (OOM)
**Issue**: The project is prone to Out of Memory errors during parallel compilation.
**Mitigation**: Use `CompileBatch18.bat` (or similar) which sets `-MaxParallelActions=1`. **Do not run standard parallel builds** unless you are sure of memory availability.

### 4. Stubbed Logic
-   `GI_SoulslikeFramework::SaveSlotList` / `LoadSlotList`: Currently placeholder implementations. Need proper `SaveGame` logic for the slot list itself.

## Next Steps for the Next Agent
1.  **Reparenting**:
    -   Reparent `W_GameMenu`, `W_InventoryAction`, `AC_SaveLoadManager` Blueprints to their new C++ classes.
    -   Set Project GameInstance to `GI_SoulslikeFramework`.
2.  **Verification**:
    -   Test Save/Load flow in editor.
    -   Verify Menu navigation.
3.  **Refinement**:
    -   Address the commented-out `NativeOnVisibilityChanged` if needed.
    -   Implement the actual saving of the Slot List in `GI_SoulslikeFramework`.

## Associated Artifacts
-   `migration_tracker_full.md`: **COMPREHENSIVE TRACKER** - All 438 items with checkboxes. NEVER truncate.
-   `migration_tracker_backup.md`: Raw backup list of all blueprints.
-   `task.md`: Granular checklist.
-   `walkthrough.md`: Detailed verification steps.
