# Soulslike Framework - Quality Assurance Tracker

## Overview
This document tracks the quality and completeness of the Blueprint-to-C++ migration.
**Last Updated**: December 19, 2025
**Status**: Active Review

---

## Critical Issues Found During Spot Check

### PRIORITY 1: CRITICAL (Must Fix Before Production)

#### 1. BPI_Player Interface - 78% Functions Missing
**File**: `Source/SLF_5_7/Converted/Interfaces/BPI_Player.h`
**Status**: ❌ CRITICAL
**Issue**: Only 4 of 18 JSON functions implemented

**Missing Functions (14 total)**:
- [ ] ResetCameraView
- [ ] StopActiveCameraSequence
- [ ] PlayCameraSequence
- [ ] PlayBackstabMontage
- [ ] PlayExecuteMontage
- [ ] DiscoverRestingPoint
- [ ] OnDialogStarted
- [ ] OnNpcTraced
- [ ] GetSoulslikeCharacter
- [ ] ToggleCrouchReplicated
- [ ] ResetGreaves / ResetGloves / ResetArmor / ResetHeadpiece
- [ ] ChangeGreaves / ChangeGloves / ChangeArmor / ChangeHeadpiece
- [ ] OnTargetLocked

**Action**: Add all missing interface functions to match JSON exactly.

---

#### 2. BPI_Generic_Character Interface - Many Functions Missing
**File**: `Source/SLF_5_7/Converted/Interfaces/BPI_Generic_Character.h`
**Status**: ❌ CRITICAL
**Issue**: JSON has ~50+ functions, C++ has only ~18

**Missing Function Categories**:
- [ ] PlaySoftMontageReplicated variants
- [ ] All "Soft" prefix variants
- [ ] All "Replicated" suffix variants
- [ ] Niagara looping variant (DurationValue parameter)

**Action**: Compare full JSON export and add all missing functions.

---

### PRIORITY 2: HIGH (Should Fix Soon)

#### 3. BPI_ExecutionIndicator - Wrong Signature
**File**: `Source/SLF_5_7/Converted/Interfaces/BPI_ExecutionIndicator.h`
**Status**: ✅ FIXED (Dec 19, 2025)
**Issue**: Function signature completely different from JSON

| JSON | C++ (before) | C++ (after) |
|------|--------------|-------------|
| ToggleExecutionIcon(bool Visible) | ShowIndicator(AActor*), HideIndicator() | ToggleExecutionIcon(bool bVisible) |

**Resolution**: Replaced with correct signature. Updated W_TargetExecutionIndicator to implement new method.

---

#### 4. BTS_IsTargetDead - Missing Property
**File**: `Source/SLF_5_7/Converted/AI/BTS_IsTargetDead.h`
**Status**: ✅ FIXED (Dec 19, 2025)
**Issue**: Missing `StateToSwitchTo` UPROPERTY

**JSON has**:
```
TargetKey: Blackboard selector
StateToSwitchTo: E_AI_States enum (default: NewEnumerator3 = Investigating)
```

**Resolution**: Added `StateToSwitchTo` property with default `E_AI_States::Investigating`. Implementation now uses the property instead of hardcoded value.

---

#### 5. BTT_GetStrafePointAroundTarget - Property Mismatch
**File**: `Source/SLF_5_7/Converted/AI/BTT_GetStrafePointAroundTarget.h`
**Status**: ⚠️ MEDIUM-HIGH
**Issue**: Different approach - JSON uses RadiusKey blackboard ref, C++ uses direct floats

**Verify**: Was the original Blueprint designed to read radius from blackboard or use fixed values?

---

### PRIORITY 3: MEDIUM

#### 6. BPI_MainMenu - Missing Parameters
**File**: `Source/SLF_5_7/Converted/Interfaces/BPI_MainMenu.h`
**Status**: ⚠️ MEDIUM
**Issue**: PlayButtonInitAnimation missing 4 parameters

**JSON**: `PlayButtonInitAnimation(StartTime, Loops, Mode, PlayRate)`
**C++**: `PlayButtonInitAnimation()` - no parameters

---

#### 7. BPI_GameInstance - Missing Function
**File**: `Source/SLF_5_7/Converted/Interfaces/BPI_GameInstance.h`
**Status**: ⚠️ MEDIUM
**Issue**: Missing `GetSoulslikeGameInstance` function (9/10 implemented)

---

#### 8. BPI_Interactable - Intentionally Incomplete
**File**: `Source/SLF_5_7/Converted/Interfaces/BPI_Interactable.h`
**Status**: ⚠️ LOW (Documented)
**Issue**: `OnSpawnedFromSave` commented out due to FInstancedStruct not enabled

**Action**: Enable FInstancedStruct in .uproject and uncomment, OR remove from interface.

---

## Enum Quality Summary

### Fixed Enums (Session Dec 19)
| Enum | Issue | Status |
|------|-------|--------|
| E_AI_States | Complete rewrite needed | ✅ FIXED |
| E_ActionWeaponSlot | RightHand→Right, etc. | ✅ FIXED |
| E_FadeTypes | Added FadeInNOut | ✅ FIXED |
| E_InventoryAmountedActionType | Complete rewrite | ✅ FIXED |
| E_SaveBehavior | Complete rewrite | ✅ FIXED |
| E_TraceType | Shape→Hand based | ✅ FIXED |
| E_Direction | Forward→Fwd naming | ✅ FIXED |
| E_AI_Senses | Removed extra values | ✅ FIXED |
| E_Progress | Removed extra values | ✅ FIXED |
| E_ValueType | Kept extended (C++ needs 7 vals) | ✅ KEPT |
| E_CalculationType | Already in PDA_Calculations.h | ✅ EXISTS |

### Code Fixes Applied
- AC_CombatManager.cpp - Updated enum references
- AC_EquipmentManager.cpp - Updated enum references
- AC_InteractionManager.cpp - Updated enum references
- AC_InventoryManager.cpp - Updated enum references
- AC_ActionManager.cpp - Updated enum references
- PC_SoulslikeFramework.cpp - Updated enum references
- BTS_IsTargetDead.cpp - Updated enum references
- FDialogRequirement.h - E_Progress::None → NotStarted
- AC_ProgressManager.cpp - E_Progress::None → NotStarted

---

## Widget Migration Status

| Status | Count | Percentage |
|--------|-------|------------|
| Converted | 2 | 1.6% |
| Remaining | 120 | 98.4% |
| **Total** | **122** | - |

### Converted Widgets (High Quality)
- [x] W_Inventory_ActionButton - GOOD
- [x] W_Inventory_CategoryEntry - GOOD

### Known Widget Issues
- **W_Status**: OnVisibilityChanged override was problematic (commented out)
- Pattern established is solid, can be used as template

---

## Verification Protocol

### Before Marking Any Item Complete
1. **READ the JSON** in `Plugins/NodeToCode/ExportedBlueprints/`
2. **COMPARE** function count, signatures, properties
3. **CHECK defaults** against `Saved/BlueprintComponentExports/`
4. **COMPILE** to verify no errors
5. **DOCUMENT** any intentional deviations

### Quality Gates
- [ ] All UENUM values match Blueprint exactly (order matters!)
- [ ] All interface functions match JSON signatures
- [ ] All BT Task/Service properties exposed
- [ ] All BindWidget properties use TObjectPtr<>
- [ ] Compiles with -WarningsAsErrors

---

## Migration Tracker Links
- **Full Tracker**: `migration_tracker_full.md`
- **Backup List**: `migration_tracker_backup.md`
- **Main Instructions**: `CLAUDE.md`

---

## Session Log

### December 19, 2025
- Completed spot check of all types
- Found 11 enum mismatches - ALL FIXED
- Found 7 interface issues - DOCUMENTED
- Found 3 BT issues - DOCUMENTED
- Compiled successfully after fixes
- Created this quality tracker

---

## Next Actions Checklist

### Immediate (This Session)
- [ ] Fix BTS_IsTargetDead - add StateToSwitchTo property
- [ ] Fix BPI_ExecutionIndicator - correct signature
- [ ] Review BPI_Player and add missing functions

### Short Term
- [ ] Complete BPI_Generic_Character
- [ ] Complete BPI_MainMenu parameter fix
- [ ] Add BPI_GameInstance missing function

### Medium Term
- [ ] Migrate priority widgets using established pattern
- [ ] Enable FInstancedStruct for BPI_Interactable
- [ ] Address W_Status visibility event handling
