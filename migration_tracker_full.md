# Soulslike Framework - Complete Migration Tracker

**Total Blueprints**: 438 | **Migrated**: ~141 | **Progress**: ~32%

**IMPORTANT**: This tracker must NEVER be truncated. Always update in place by checking off items.

---

## Legend
- `[x]` Migrated to C++
- `[ ]` Not yet migrated
- `[~]` Partial / Needs review
- `[S]` Skip (Editor-only or not needed)

---

## 1. ENUMS (E_) - 37 Total | 37 Migrated

- [x] E_ActionWeaponSlot
- [x] E_AI_BossEncounterType
- [x] E_AI_Senses
- [x] E_AI_StateHandle
- [x] E_AI_States
- [x] E_AI_StrafeLocations
- [x] E_AttackPower
- [x] E_CalculationType
- [x] E_DebugWindowScaleType
- [x] E_Direction
- [x] E_DotProductThreshold
- [x] E_EnclosureLevel
- [x] E_ExecutionType
- [x] E_FadeTypes
- [x] E_HitReactType
- [x] E_InputAction
- [x] E_InventoryAmountedActionType
- [x] E_InventorySlotType
- [x] E_ItemCategory
- [x] E_ItemSubCategory
- [x] E_KeyType
- [x] E_LadderClimbState
- [x] E_LightningMode
- [x] E_MontageSection
- [x] E_MovementType
- [x] E_NpcState
- [x] E_OverlayState
- [x] E_Progress
- [x] E_SaveBehavior
- [x] E_SettingCategory
- [x] E_SettingEntry
- [x] E_StatCategory
- [x] E_StatScaling
- [x] E_TraceType
- [x] E_ValueType
- [x] E_VendorType
- [x] E_WeaponAbilityHandle
- [x] E_WorldMeshStyle

---

## 2. STRUCTS (F) - 4 in JSON + ~23 in C++ | Most Migrated

### From JSON Exports:
- [x] FAiAttackEntry
- [x] FAnimationData
- [x] FEquipmentStat
- [x] FExecutionAnimInfo

### Additional C++ Structs Created:
- [x] FAiBossPhase
- [x] FAiPatrolPathInfo
- [x] FAiRuleStat
- [x] FCardinalData
- [x] FCraftingInfo
- [x] FCreditsEntry
- [x] FCreditsExtra
- [x] FDayNightInfo
- [x] FDialogProgress
- [x] FDialogRequirement
- [x] FDoorLockInfo
- [x] FEquipmentInfo
- [x] FEquipmentSocketInfo
- [x] FEquipmentWeaponStatInfo
- [x] FInventoryCategory
- [x] FInventoryItem
- [x] FItemCategory
- [x] FLootItem
- [x] FModularMeshData
- [x] FRegen
- [x] FSaveGameInfo
- [x] FSLFItemInfo
- [x] FStatInfo
- [x] FStatusEffectApplication
- [x] FWeaponAttackPower
- [x] FWeightedLoot
- [x] FWorldMeshInfo

---

## 3. INTERFACES (BPI_ / ALI_) - 20 Total | 20 Migrated

### Animation Layer Interfaces:
- [x] ALI_LocomotionStates
- [x] ALI_OverlayStates

### Blueprint Interfaces:
- [x] BPI_AIC
- [x] BPI_BossDoor
- [x] BPI_Controller
- [x] BPI_Damageable (C++ only - no JSON)
- [x] BPI_DestructibleHelper
- [x] BPI_Enemy
- [x] BPI_EnemyHealthbar
- [x] BPI_Executable
- [x] BPI_ExecutionIndicator
- [x] BPI_GameInstance
- [x] BPI_GenericCharacter (as BPI_Generic_Character)
- [x] BPI_Interactable
- [x] BPI_Item
- [x] BPI_MainMenu
- [x] BPI_NPC
- [x] BPI_Player
- [x] BPI_Projectile
- [x] BPI_RestingPoint
- [x] BPI_StatEntry

---

## 4. DATA ASSETS (PDA_) - 24 Total | 24 Migrated

- [x] PDA_Action
- [x] PDA_AI_Ability
- [x] PDA_AnimData
- [x] PDA_BaseCharacterInfo
- [x] PDA_Buff
- [x] PDA_Calculations
- [x] PDA_CombatReactionAnimData
- [x] PDA_CombatReactionAnimData_Player
- [x] PDA_Credits
- [x] PDA_CustomSettings
- [x] PDA_DayNight
- [x] PDA_DefaultMeshData
- [x] PDA_Dialog
- [x] PDA_ExecutionAnimData
- [x] PDA_Item
- [x] PDA_LadderAnimData
- [x] PDA_LoadingScreens
- [x] PDA_MainMenuData
- [x] PDA_MovementSpeedData
- [x] PDA_PoiseBreakAnimData
- [x] PDA_StatusEffect
- [x] PDA_Vendor
- [x] PDA_WeaponAbility
- [x] PDA_WeaponAnimset

---

## 5. COMPONENTS (AC_) - 21 Total | 21 Migrated

- [x] AC_ActionManager
- [x] AC_AI_BehaviorManager
- [x] AC_AI_Boss
- [x] AC_AI_CombatManager
- [x] AC_AI_InteractionManager
- [x] AC_BuffManager
- [x] AC_CollisionManager
- [x] AC_CombatManager
- [x] AC_DebugCentral
- [x] AC_EquipmentManager
- [x] AC_InputBuffer
- [x] AC_InteractionManager
- [x] AC_InventoryManager
- [x] AC_LadderManager
- [x] AC_LootDropManager
- [x] AC_ProgressManager
- [x] AC_RadarElement
- [x] AC_RadarManager
- [x] AC_SaveLoadManager
- [x] AC_StatManager
- [x] AC_StatusEffectManager

---

## 6. ACTORS/CLASSES (B_) - 109 Total | ~21 Migrated

### Core Actors:
- [x] B_AbilityEffectBase
- [x] B_Action
- [x] B_Action_Backstab
- [x] B_Action_ComboHeavy
- [x] B_Action_ComboLight_L
- [x] B_Action_ComboLight_R
- [x] B_Action_Crouch
- [x] B_Action_Dodge
- [x] B_Action_DrinkFlask_HP
- [x] B_Action_DualWieldAttack
- [x] B_Action_Execute
- [x] B_Action_GuardCancel
- [x] B_Action_GuardEnd
- [x] B_Action_GuardStart
- [x] B_Action_Jump
- [x] B_Action_JumpAttack
- [x] B_Action_PickupItemMontage
- [x] B_Action_ScrollWheel_LeftHand
- [x] B_Action_ScrollWheel_RightHand
- [x] B_Action_ScrollWheel_Tools
- [x] B_Action_SprintAttack
- [x] B_Action_StartSprinting
- [x] B_Action_StopSprinting
- [x] B_Action_ThrowProjectile
- [x] B_Action_TwoHandedStance_L
- [x] B_Action_TwoHandedStance_R
- [x] B_Action_UseEquippedTool
- [x] B_Action_WeaponAbility

### Stats (Attack Power):
- [x] B_AP_Fire
- [x] B_AP_Frost
- [x] B_AP_Holy
- [x] B_AP_Lightning
- [x] B_AP_Magic
- [x] B_AP_Physical

### Stats (Attributes):
- [x] B_Arcane
- [x] B_Dexterity
- [x] B_Discovery
- [x] B_Endurance
- [x] B_Faith
- [x] B_FP
- [x] B_HP
- [x] B_IncantationPower
- [x] B_Intelligence
- [x] B_Mind
- [x] B_Poise
- [x] B_Stamina
- [x] B_Stance
- [x] B_Stat
- [x] B_Strength
- [x] B_Vigor
- [x] B_Weight

### Stats (Defense/Negation):
- [x] B_DN_Fire
- [x] B_DN_Frost
- [x] B_DN_Holy
- [x] B_DN_Lightning
- [x] B_DN_Magic
- [x] B_DN_Physical

### Stats (Resistance):
- [x] B_Resistance_Focus
- [x] B_Resistance_Immunity
- [x] B_Resistance_Robustness
- [x] B_Resistance_Vitality

### Characters:
- [x] B_BaseCharacter
- [x] B_Soulslike_Character
- [x] B_Soulslike_Enemy
- [x] B_Soulslike_Boss
- [x] B_Soulslike_Boss_Malgareth
- [x] B_Soulslike_Enemy_Guard
- [x] B_Soulslike_Enemy_Showcase
- [x] B_Soulslike_NPC
- [x] B_Soulslike_NPC_ShowcaseGuide
- [x] B_Soulslike_NPC_ShowcaseVendor

### Interactables:
- [x] B_Interactable
- [x] B_BossDoor
- [x] B_Container
- [x] B_DeathTrigger
- [x] B_Destructible
- [x] B_Door
- [x] B_Door_Demo
- [x] B_Ladder
- [x] B_LocationActor
- [x] B_PatrolPath
- [x] B_RestingPoint
- [x] B_Torch

### Items:
- [x] B_Item
- [x] B_Item_AI_Weapon
- [x] B_Item_AI_Weapon_BossMace
- [x] B_Item_AI_Weapon_Greatsword
- [x] B_Item_AI_Weapon_Sword
- [x] B_Item_Lantern
- [x] B_Weapon (B_Item_Weapon)
- [x] B_Item_Weapon_BossMace
- [x] B_Item_Weapon_Greatsword
- [x] B_Item_Weapon_Katana
- [x] B_Item_Weapon_PoisonSword
- [x] B_Item_Shield (B_Item_Weapon_Shield)
- [x] B_Item_Weapon_SwordExample01
- [x] B_Item_Weapon_SwordExample02
- [x] B_PickupItem

### Buffs/Effects:
- [x] B_Buff
- [x] B_Buff_AttackPower
- [x] B_StatusEffect
- [x] B_StatusEffect_Bleed
- [x] B_StatusEffect_Burn
- [x] B_StatusEffect_Corruption
- [x] B_StatusEffect_Frostbite
- [x] B_StatusEffect_Madness
- [x] B_StatusEffect_Plague
- [x] B_StatusEffect_Poison
- [x] B_StatusEffectArea
- [x] B_StatusEffectBuildup
- [x] B_StatusEffectOneShot

### Projectiles:
- [x] B_BaseProjectile
- [x] B_Projectile_Boss_Fireball
- [x] B_Projectile_ThrowingKnife

### Misc Actors:
- [x] B_Chaos_ForceField
- [x] B_DeathCurrency
- [x] B_Demo_TimeSlider
- [x] B_DemoDisplay
- [x] B_DemoRoom
- [x] B_SequenceActor
- [x] B_ShowcaseEnemy_ExitCombat
- [x] B_ShowcaseEnemy_StatDisplay
- [x] B_SkyManager

---

## 7. WIDGETS (W_) - 101 Total | ~17 Migrated

### Core UI:
- [x] W_HUD
- [x] W_Status
- [x] W_Navigable
- [x] W_UserWidget_Base (C++ only)
- [ ] W_BigScreenMessage
- [ ] W_LoadingScreen
- [ ] W_SkipCinematic

### Equipment:
- [x] W_Equipment
- [x] W_EquipmentSlot
- [ ] W_Equipment_Item_AttackPower
- [ ] W_Equipment_Item_DamageNegation
- [ ] W_Equipment_Item_ItemEffect
- [ ] W_Equipment_Item_OnUseEffect
- [ ] W_Equipment_Item_RequiredStats
- [ ] W_Equipment_Item_Resistance
- [ ] W_Equipment_Item_StatScaling
- [ ] W_Equipment_Item_StatsGranted

### Inventory:
- [x] W_Inventory
- [x] W_InventorySlot
- [x] W_Inventory_CategoryEntry
- [x] W_InventoryAction
- [x] W_InventoryActionAmount
- [ ] W_Inventory_ActionButton

### Stats:
- [x] W_StatBlock
- [x] W_StatEntry
- [ ] W_StatBlock_LevelUp
- [ ] W_StatEntry_LevelUp
- [ ] W_StatEntry_StatName
- [ ] W_StatEntry_Status
- [ ] W_Status_LevelCurrencyBlock
- [ ] W_Status_StatBlock

### Menus:
- [x] W_GameMenu
- [x] W_GameMenu_Button
- [ ] W_MainMenu
- [ ] W_MainMenu_Button
- [ ] W_RestMenu
- [ ] W_RestMenu_Button
- [ ] W_RestMenu_TimeEntry

### Item Info:
- [x] W_ItemInfoEntry
- [ ] W_ItemInfoEntry_RequiredStats
- [ ] W_ItemInfoEntry_StatScaling
- [ ] W_ItemWheel_NextSlot
- [ ] W_ItemWheelSlot

### Dialogs/NPC:
- [ ] W_Dialog
- [ ] W_NPC_Window
- [ ] W_NPC_Window_Vendor

### Combat UI:
- [ ] W_AbilityDisplay
- [ ] W_Boss_Healthbar
- [ ] W_Buff
- [ ] W_EnemyHealthbar
- [ ] W_StatusEffectBar
- [ ] W_StatusEffectNotification
- [ ] W_TargetExecutionIndicator
- [ ] W_TargetLock

### Save/Load:
- [ ] W_LoadGame
- [ ] W_LoadGame_Entry

### Level Up:
- [ ] W_LevelCurrencyBlock_LevelUp
- [ ] W_LevelEntry
- [ ] W_LevelUp
- [ ] W_LevelUpCost

### Settings:
- [ ] W_Settings
- [ ] W_Settings_CategoryEntry
- [ ] W_Settings_CenteredText
- [ ] W_Settings_ControlEntry
- [ ] W_Settings_ControlsDisplay
- [ ] W_Settings_Entry
- [ ] W_Settings_InputKeySelector
- [ ] W_Settings_KeyMapping
- [ ] W_Settings_KeyMapping_Category
- [ ] W_Settings_KeyMapping_Entry
- [ ] W_Settings_PlayerCard
- [ ] W_Settings_QuitConfirmation

### Crafting:
- [ ] W_Crafting
- [ ] W_CraftingAction
- [ ] W_CraftingEntry
- [ ] W_CraftingEntrySimple

### Credits:
- [ ] W_CreditEntry
- [ ] W_CreditEntry_Extra
- [ ] W_CreditEntry_Sub
- [ ] W_CreditEntry_Sub_NameEntry
- [ ] W_Credits

### Character Selection:
- [ ] W_CharacterSelection
- [ ] W_CharacterSelection_StatEntry
- [ ] W_CharacterSelectionCard

### Misc Widgets:
- [ ] W_CategoryEntry
- [ ] W_CurrencyContainer
- [ ] W_CurrencyEntry
- [ ] W_Error
- [ ] W_FirstLootNotification
- [ ] W_GenericButton
- [ ] W_GenericError
- [ ] W_Interaction
- [ ] W_InteractionError
- [ ] W_LootNotification
- [ ] W_Navigable_InputReader
- [ ] W_Radar
- [ ] W_Radar_Cardinal
- [ ] W_Radar_TrackedElement
- [ ] W_Resources
- [ ] W_TimePass
- [ ] W_VendorAction
- [ ] W_VendorSlot

### Debug Widgets:
- [ ] W_Debug_ComponentSlot
- [ ] W_Debug_ComponentTooltip
- [ ] W_Debug_HUD
- [ ] W_DebugWindow

### Browser Widgets:
- [ ] W_Browser_Action
- [ ] W_Browser_Action_Tooltip
- [ ] W_Browser_Animset
- [ ] W_Browser_Animset_OwnerEntry
- [ ] W_Browser_AnimsetTooltip
- [ ] W_Browser_Categories
- [ ] W_Browser_CategoryEntry
- [ ] W_Browser_Item
- [ ] W_Browser_StatusEffect
- [ ] W_Browser_StatusEffect_Tooltip
- [ ] W_Browser_Tooltip
- [ ] W_Browser_WeaponAbility
- [ ] W_Browser_WeaponAbility_Tooltip
- [ ] W_BrowserFilterEntry

### Utility Widgets:
- [ ] W_Utility_Asset
- [ ] W_Utility_AssetTooltip
- [ ] W_Utility_Component

---

## 8. ANIMATION BLUEPRINTS (ABP_) - 6 Total | 0 Migrated

- [ ] ABP_Manny_PostProcess
- [ ] ABP_Quinn_PostProcess
- [ ] ABP_SoulslikeBossNew
- [ ] ABP_SoulslikeCharacter_Additive
- [ ] ABP_SoulslikeEnemy
- [ ] ABP_SoulslikeNPC

---

## 9. ANIM NOTIFIES (AN_) - 13 Total | 0 Migrated

- [ ] AN_AdjustStat
- [ ] AN_AI_SpawnProjectile
- [ ] AN_AoeDamage
- [ ] AN_CameraShake
- [ ] AN_FootstepTrace
- [ ] AN_InterruptMontage
- [ ] AN_LaunchField
- [ ] AN_PlayCameraSequence
- [ ] AN_SetAiState
- [ ] AN_SetMovementMode
- [ ] AN_SpawnProjectile
- [ ] AN_TryGuard
- [ ] AN_WorldCameraShake

---

## 10. ANIM NOTIFY STATES (ANS_) - 11 Total | 0 Migrated

- [ ] ANS_AI_FistTrace
- [ ] ANS_AI_RotateTowardsTarget
- [ ] ANS_AI_Trail
- [ ] ANS_AI_WeaponTrace
- [ ] ANS_FistTrace
- [ ] ANS_HyperArmor
- [ ] ANS_InputBuffer
- [ ] ANS_InvincibilityFrame
- [ ] ANS_RegisterAttackSequence
- [ ] ANS_ToggleChaosField
- [ ] ANS_Trail
- [ ] ANS_WeaponTrace

---

## 11. AI - BT SERVICES (BTS_) - 5 Total | 0 Migrated

- [ ] BTS_ChaseBounds
- [ ] BTS_DistanceCheck
- [ ] BTS_IsTargetDead
- [ ] BTS_SetMovementModeBasedOnDistance
- [ ] BTS_TryGetAbility

---

## 12. AI - BT TASKS (BTT_) - 13 Total | 0 Migrated

- [ ] BTT_ClearKey
- [ ] BTT_GetCurrentLocation
- [ ] BTT_GetRandomPoint
- [ ] BTT_GetRandomPointNearStartPosition
- [ ] BTT_GetStrafePointAroundTarget
- [ ] BTT_PatrolPath
- [ ] BTT_SetKey
- [ ] BTT_SetMovementMode
- [ ] BTT_SimpleMoveTo
- [ ] BTT_SwitchState
- [ ] BTT_SwitchToPreviousState
- [ ] BTT_ToggleFocus
- [ ] BTT_TryExecuteAbility

---

## 13. AI CONTROLLER (AIC_) - 1 Total | 0 Migrated

- [x] AIC_SoulslikeFramework

---

## 14. GAME FRAMEWORK - 9 Total | 9 Migrated

- [x] GI_SoulslikeFramework
- [x] GM_Menu_SoulslikeFramework
- [x] GM_SoulslikeFramework
- [x] GS_SoulslikeFramework
- [x] PC_Menu_SoulslikeFramework
- [x] PC_SoulslikeFramework
- [x] PS_SoulslikeFramework
- [x] SG_SoulslikeFramework
- [x] SG_SaveSlots

---

## 15. CONTROL RIGS (CR_) - 3 Total | SKIP (Best in Blueprint)

Control Rigs are complex procedural animation systems that are better maintained in Blueprint.

- [S] CR_Mannequin_BasicFootIK
- [S] CR_Mannequin_Procedural
- [S] CR_SoulslikeFramework

---

## 16. CAMERA SHAKES (CS_) - 6 Total | 6 Migrated

- [x] CS_Boss_Roar
- [x] CS_Guard
- [x] CS_JumpHit
- [x] CS_Seq_Handheld
- [x] CS_StrongHit
- [x] CS_SubtleHit

---

## 17. EDITOR UTILITIES (EUO_ / EUW_) - 16 Total | SKIP

These are editor-only tools and do not need C++ migration.

- [S] EUO_Hook
- [S] EUW_ActionBrowser
- [S] EUW_ActionCreator
- [S] EUW_AI_AbilityCreator
- [S] EUW_BatchExport
- [S] EUW_EnemyViewer
- [S] EUW_ItemBrowser
- [S] EUW_ItemCreator
- [S] EUW_Setup
- [S] EUW_StatusEffectBrowser
- [S] EUW_StatusEffectCreator
- [S] EUW_WeaponAbilityBrowser
- [S] EUW_WeaponAbilityCreator
- [S] EUW_WeaponAnimsetBrowser
- [S] EUW_WeaponAnimsetCreator

---

## 18. BLUEPRINT LIBRARIES (BFL_ / BML_) - 3 Total | 1 Migrated | 2 SKIP

- [x] BFL_Helper
- [S] BML_HelperMacros (Macro Libraries don't translate to C++)
- [S] BML_StructConversion (Macro Libraries don't translate to C++)

---

## Summary

| Category | Total | Migrated | Skip | Remaining |
|----------|-------|----------|------|-----------|
| Enums | 37 | 26 | 0 | 11 |
| Structs | 27+ | 27 | 0 | 0 |
| Interfaces | 20 | 15 | 0 | 5 |
| Data Assets | 24 | 21 | 0 | 3 |
| Components | 17 | 15 | 0 | 2 |
| Classes/Actors | 109 | 21 | 0 | 88 |
| Widgets | 101 | 17 | 0 | 84 |
| Anim BPs | 6 | 0 | 0 | 6 |
| Anim Notifies | 13 | 0 | 0 | 13 |
| Anim Notify States | 11 | 0 | 0 | 11 |
| BT Services | 5 | 0 | 0 | 5 |
| BT Tasks | 13 | 0 | 0 | 13 |
| AI Controller | 1 | 0 | 0 | 1 |
| Game Framework | 9 | 2 | 0 | 7 |
| Control Rigs | 3 | 0 | 0 | 3 |
| Camera Shakes | 6 | 0 | 0 | 6 |
| Editor Utilities | 16 | 0 | 16 | 0 |
| BP Libraries | 3 | 0 | 0 | 3 |
| **TOTAL** | **438** | **~144** | **16** | **~278** |

---

## Data Sources

- **Logic Source**: `Plugins/NodeToCode/ExportedBlueprints/` (438 files)
- **Defaults Source**: `Saved/BlueprintComponentExports/` (801 files)
- **C++ Output**: `Source/SLF_5_7/Converted/`
