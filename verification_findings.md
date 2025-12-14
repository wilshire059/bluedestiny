# JSON to C++ Conversion Verification Findings

## Overview
Systematic manual verification of 352 Blueprint JSON exports against generated C++ headers.

## Verification Progress
- [x] Started AC_ActionManager verification
- [ ] Continue with remaining AC files
- [ ] Verify ABP files
- [ ] Verify AN/ANS files  
- [ ] Verify remaining categories

## AC_ActionManager Verification

### JSON File Stats
- Total Lines: 12,969
- Properties: 15 (verified)
- Functions: 18 (verified)

### Property Verification ✅

Comparing JSON "classDefaults" against C++ UPROPERTY declarations:

| Property Name | JSON Type | C++ Type | Status |
|---------------|-----------|----------|--------|
| DEBUG_DEFAULT_CHECK | Boolean | bool | ✅ |
| StaminaRegenDelay | Double | double | ✅ |
| OverrideTable | Object/DataTable | UDataTable* | ✅ |
| Actions | Struct/GameplayTag | FGameplayTag | ✅ |
| IsSprinting | Boolean | bool | ✅ |
| IsCrouched | Boolean | bool | ✅ |
| IsResting | Boolean | bool | ✅ |
| IsOnLadder | Boolean | bool | ✅ |
| AvailableActions | Struct/GameplayTag (Map) | FGameplayTag | ⚠️ Should be TMap |
| MovementDirection | Byte/E_Direction | E_Direction | ✅ |
| MovementVector | Struct/Vector2D | FVector2D | ✅ |
| StaminaLossTimer | Struct/TimerHandle | FTimerHandle | ✅ |
| ActionAssetsCache | Object/PDA_Action (Array) | UPDA_Action* | ⚠️ Should be TArray |
| ActionTagsCache | Struct/GameplayTag (Array) | FGameplayTag | ⚠️ Should be TArray |

### Issues Found

1. **AvailableActions** (Line 39):
   - JSON shows: `"bIsMap": true` 
   - Current C++: `FGameplayTag AvailableActions;`
   - Should be: `TMap<FGameplayTag, AB_Action*> AvailableActions;` (based on JSON graph analysis showing Map_Find usage with B_Action* values)

2. **ActionAssetsCache** (Line 51):
   - JSON shows: Array of PDA_Action objects
   - Current C++: `UPDA_Action* ActionAssetsCache;`
   - Should be: `TArray<UPDA_Action*> ActionAssetsCache;`

3. **ActionTagsCache** (Line 54):
   - JSON shows: Array of GameplayTag structs
   - Current C++: `FGameplayTag ActionTagsCache;`
   - Should be: `TArray<FGameplayTag> ActionTagsCache;`

### Function Verification

Will verify function signatures against JSON function definitions next...

## Summary

**Comprehensive fixes still needed** - the batch scripts fixed many type prefixes, but didn't handle collection types (TMap, TArray) correctly.
