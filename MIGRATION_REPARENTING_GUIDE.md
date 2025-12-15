# Soulslike Framework - Complete Migration & Reparenting Guide

This guide covers every C++ class created during migration, what Blueprint it replaces, how to activate it, and comprehensive testing procedures.

---

## Table of Contents

1. [Pre-Migration Checklist](#1-pre-migration-checklist)
2. [Understanding Reparenting](#2-understanding-reparenting)
3. [Enums](#3-enums---37-items)
4. [Structs](#4-structs---27-items)
5. [Interfaces](#5-interfaces---20-items)
6. [Data Assets](#6-data-assets---24-items)
7. [Components](#7-components---21-items)
8. [Classes/Actors](#8-classesactors---109-items)
9. [Widgets](#9-widgets---101-items)
10. [Animation Assets](#10-animation-assets---31-items)
11. [AI Assets](#11-ai-assets---19-items)
12. [Game Framework](#12-game-framework---9-items)
13. [Other Assets](#13-other-assets)
14. [Post-Migration Verification](#14-post-migration-verification)
15. [Troubleshooting](#15-troubleshooting)

---

## 1. Pre-Migration Checklist

### Before You Begin

1. **Backup Your Project**
   ```
   - Create a complete backup of the Content folder
   - Commit all pending changes to Git
   - Note the current commit hash for rollback
   ```

2. **Compile the C++ Code**
   ```batch
   CompileBatch18.bat
   ```
   Ensure "Build Successful" appears with no errors.

3. **Open Unreal Editor**
   - Wait for shader compilation to complete
   - Ensure no Blueprint compile errors appear

4. **Create Test Save**
   - Play the game and create a save file
   - Note character stats, inventory, and location
   - This is your "before" baseline

### Recommended Migration Order

1. **Phase 1**: Enums, Structs (automatic - no action needed)
2. **Phase 2**: Interfaces (automatic for most)
3. **Phase 3**: Data Assets
4. **Phase 4**: Game Framework (GameInstance, GameMode, etc.)
5. **Phase 5**: Components
6. **Phase 6**: Core Actors (Interactables, Items)
7. **Phase 7**: Characters (Enemy, NPC, Player)
8. **Phase 8**: Widgets (UI)
9. **Phase 9**: Animation & AI

---

## 2. Understanding Reparenting

### What is Reparenting?

Reparenting changes a Blueprint's parent class from one Blueprint to a C++ class. For example:
- **Before**: `BP_Weapon` inherits from `BP_Item` (Blueprint)
- **After**: `BP_Weapon` inherits from `AB_Weapon` (C++)

### How to Reparent a Blueprint

1. Open the Blueprint in the editor
2. Go to **File > Reparent Blueprint**
3. Search for and select the new C++ parent class
4. Click **Reparent**
5. **IMPORTANT**: Review the "Reparent Blueprint" dialog for any warnings
6. Compile the Blueprint (Ctrl+F7)
7. Save the Blueprint

### What Gets Preserved vs. Lost

| Preserved | May Need Manual Update |
|-----------|----------------------|
| Child class logic | Overridden functions with signature changes |
| Event bindings | Component references if renamed |
| Custom variables | Default values (verify in Details panel) |
| Widget bindings | Struct references if type changed |

---

## 3. Enums - 37 Items

### What They Are
Enums define fixed sets of named values (e.g., `E_AI_States::Idle`, `E_Direction::Forward`).

### C++ Location
`Source/SLF_5_7/Converted/Enums/`

### Migration Status: AUTOMATIC

Enums are automatically available in Blueprints once compiled. No reparenting needed.

### Complete Enum List

| C++ File | Purpose |
|----------|---------|
| `E_ActionWeaponSlot.h` | Which hand slot an action uses (Left/Right/Both) |
| `E_AI_BossEncounterType.h` | Boss encounter phases |
| `E_AI_Senses.h` | AI perception types (Sight/Sound/Damage) |
| `E_AI_StateHandle.h` | AI state machine handles |
| `E_AI_States.h` | Core AI states (Idle/Patrol/Chase/Combat/Dead) |
| `E_AI_StrafeLocations.h` | Strafe positions around target |
| `E_AttackPower.h` | Damage types (Physical/Fire/Frost/Lightning/Holy/Magic) |
| `E_CalculationType.h` | Math operations for stat calculations |
| `E_DebugWindowScaleType.h` | Debug UI scaling modes |
| `E_Direction.h` | Cardinal/relative directions |
| `E_DotProductThreshold.h` | Angle comparison thresholds |
| `E_EnclosureLevel.h` | Indoor/Outdoor detection levels |
| `E_ExecutionType.h` | Execution attack types (Backstab/Riposte) |
| `E_FadeTypes.h` | Screen fade transition types |
| `E_HitReactType.h` | Hit reaction animation types |
| `E_InputAction.h` | Player input action mappings |
| `E_InventoryAmountedActionType.h` | Inventory bulk action types |
| `E_InventorySlotType.h` | Equipment slot types (Weapon/Armor/Accessory) |
| `E_ItemCategory.h` | Top-level item categories |
| `E_ItemSubCategory.h` | Detailed item subcategories |
| `E_KeyType.h` | Door/Lock key types |
| `E_LadderClimbState.h` | Ladder interaction states |
| `E_LightningMode.h` | Environment lightning modes |
| `E_MontageSection.h` | Animation montage section identifiers |
| `E_MovementType.h` | Character movement modes |
| `E_NpcState.h` | NPC behavior states |
| `E_OverlayState.h` | Animation overlay states |
| `E_Progress.h` | Game progress flags |
| `E_SaveBehavior.h` | Save system behaviors |
| `E_SettingCategory.h` | Settings menu categories |
| `E_SettingEntry.h` | Individual setting entries |
| `E_StatCategory.h` | Stat groupings |
| `E_StatScaling.h` | Stat scaling grades (S/A/B/C/D/E) |
| `E_TraceType.h` | Collision trace channel types |
| `E_ValueType.h` | Stat value types (Flat/Percent) |
| `E_VendorType.h` | Vendor shop types |
| `E_WeaponAbilityHandle.h` | Weapon ability identifiers |
| `E_WorldMeshStyle.h` | Procedural mesh generation styles |

### Testing Enums
```
1. Open any Blueprint that uses an enum
2. In the Details panel, verify dropdown options appear
3. Compile the Blueprint - no errors should occur
```

---

## 4. Structs - 27+ Items

### What They Are
Structs are data containers grouping related properties (e.g., `FInventoryItem` holds item ID, quantity, slot).

### C++ Location
`Source/SLF_5_7/Converted/Structs/`

### Migration Status: AUTOMATIC

Structs are automatically available once compiled. Existing Blueprint structs may need to be replaced with C++ versions.

### Complete Struct List

| C++ File | Purpose | Used By |
|----------|---------|---------|
| `FAiAttackEntry.h` | AI attack ability definition | AC_AI_CombatManager |
| `FAiBossPhase.h` | Boss phase configuration | B_Soulslike_Boss |
| `FAiPatrolPathInfo.h` | Patrol waypoint data | B_PatrolPath |
| `FAiRuleStat.h` | AI decision rules | PDA_AI_Ability |
| `FAnimationData.h` | Animation reference container | Multiple |
| `FCardinalData.h` | Cardinal direction data | W_Radar_Cardinal |
| `FCraftingInfo.h` | Crafting recipe data | W_Crafting |
| `FCreditsEntry.h` | Credits roll entry | PDA_Credits |
| `FCreditsExtra.h` | Credits extra content | PDA_Credits |
| `FDayNightInfo.h` | Day/Night cycle data | B_SkyManager |
| `FDialogProgress.h` | Dialog state tracking | PDA_Dialog |
| `FDialogRequirement.h` | Dialog prerequisites | PDA_Dialog |
| `FDoorLockInfo.h` | Door lock configuration | B_Door |
| `FEquipmentInfo.h` | Equipment slot data | AC_EquipmentManager |
| `FEquipmentSocketInfo.h` | Mesh socket attachment | PDA_Item |
| `FEquipmentStat.h` | Equipment stat modifier | PDA_Item |
| `FEquipmentWeaponStatInfo.h` | Weapon-specific stats | B_Weapon |
| `FExecutionAnimInfo.h` | Execution animation data | PDA_ExecutionAnimData |
| `FInventoryCategory.h` | Inventory tab definition | W_Inventory |
| `FInventoryItem.h` | Item instance in inventory | AC_InventoryManager |
| `FItemCategory.h` | Item category definition | PDA_Item |
| `FLootItem.h` | Loot drop definition | AC_LootDropManager |
| `FModularMeshData.h` | Modular character mesh | PDA_DefaultMeshData |
| `FRegen.h` | Regeneration rate data | AC_StatManager |
| `FSaveGameInfo.h` | Save slot metadata | SG_SoulslikeFramework |
| `FSLFItemInfo.h` | Item display information | BPI_Item |
| `FStatInfo.h` | Stat definition | B_Stat |
| `FStatusEffectApplication.h` | Status effect instance | AC_StatusEffectManager |
| `FWeaponAttackPower.h` | Weapon damage breakdown | B_Weapon |
| `FWeightedLoot.h` | Weighted random loot | AC_LootDropManager |
| `FWorldMeshInfo.h` | World mesh configuration | B_SkyManager |

### Testing Structs
```
1. Open a Blueprint that uses structs (e.g., AC_InventoryManager)
2. Create a variable of the struct type
3. Verify all properties appear in Details panel
4. Test "Make" and "Break" struct nodes work correctly
```

---

## 5. Interfaces - 20 Items

### What They Are
Interfaces define function contracts that multiple classes can implement.

### C++ Location
`Source/SLF_5_7/Converted/Interfaces/`

### Migration Status: MOSTLY AUTOMATIC

C++ interfaces are automatically available. Blueprints implementing interfaces continue to work.

### Complete Interface List

| C++ File | Purpose | Implementers |
|----------|---------|--------------|
| `ALI_LocomotionStates.h` | Animation locomotion states | Animation Blueprints |
| `ALI_OverlayStates.h` | Animation overlay states | Animation Blueprints |
| `BPI_AIC.h` | AI Controller interface | AIC_SoulslikeFramework |
| `BPI_BossDoor.h` | Boss door interactions | B_BossDoor |
| `BPI_Controller.h` | Player controller interface | PC_SoulslikeFramework |
| `BPI_Damageable.h` | Damage reception | All characters, destructibles |
| `BPI_DestructibleHelper.h` | Destruction system | B_Destructible |
| `BPI_Enemy.h` | Enemy-specific functions | B_Soulslike_Enemy |
| `BPI_EnemyHealthbar.h` | Enemy UI communication | W_EnemyHealthbar |
| `BPI_Executable.h` | Execution target interface | B_Soulslike_Enemy |
| `BPI_ExecutionIndicator.h` | Execution UI indicator | W_TargetExecutionIndicator |
| `BPI_GameInstance.h` | Game instance functions | GI_SoulslikeFramework |
| `BPI_Generic_Character.h` | Common character functions | All characters |
| `BPI_Interactable.h` | Interaction system | All interactables |
| `BPI_Item.h` | Item interface | B_Item, B_Weapon |
| `BPI_MainMenu.h` | Main menu functions | W_MainMenu |
| `BPI_NPC.h` | NPC interaction | B_Soulslike_NPC |
| `BPI_Player.h` | Player-specific functions | B_Soulslike_Character |
| `BPI_Projectile.h` | Projectile interface | B_BaseProjectile |
| `BPI_RestingPoint.h` | Rest point (bonfire) | B_RestingPoint |
| `BPI_StatEntry.h` | Stat UI entry | W_StatEntry |

### Testing Interfaces
```
1. Open a Blueprint implementing the interface
2. Verify interface functions appear in "Interfaces" section
3. Call interface function via "Does Implement Interface" check
4. Test message calls work correctly
```

---

## 6. Data Assets - 24 Items

### What They Are
Data Assets are reusable configuration objects (items, abilities, animations).

### C++ Location
`Source/SLF_5_7/Converted/DataAssets/`

### Reparenting Required: YES

Each Blueprint Data Asset should be reparented to its C++ equivalent.

### Complete Data Asset List

| C++ Class | Blueprint to Reparent | Purpose |
|-----------|----------------------|---------|
| `UPDA_Action` | `PDA_Action` | Player action definitions |
| `UPDA_AI_Ability` | `PDA_AI_Ability` | AI ability configurations |
| `UPDA_AnimData` | `PDA_AnimData` | Animation references |
| `UPDA_BaseCharacterInfo` | `PDA_BaseCharacterInfo` | Character configuration |
| `UPDA_Buff` | `PDA_Buff` | Buff effect definitions |
| `UPDA_Calculations` | `PDA_Calculations` | Stat calculation formulas |
| `UPDA_CombatReactionAnimData` | `PDA_CombatReactionAnimData` | Hit reaction animations |
| `UPDA_CombatReactionAnimData_Player` | `PDA_CombatReactionAnimData_Player` | Player hit reactions |
| `UPDA_Credits` | `PDA_Credits` | Credits roll data |
| `UPDA_CustomSettings` | `PDA_CustomSettings` | Game settings definitions |
| `UPDA_DayNight` | `PDA_DayNight` | Day/night cycle config |
| `UPDA_DefaultMeshData` | `PDA_DefaultMeshData` | Default character meshes |
| `UPDA_Dialog` | `PDA_Dialog` | NPC dialog trees |
| `UPDA_ExecutionAnimData` | `PDA_ExecutionAnimData` | Execution animations |
| `UPDA_Item` | `PDA_Item` | Item definitions |
| `UPDA_LadderAnimData` | `PDA_LadderAnimData` | Ladder climb animations |
| `UPDA_LoadingScreens` | `PDA_LoadingScreens` | Loading screen images |
| `UPDA_MainMenuData` | `PDA_MainMenuData` | Main menu configuration |
| `UPDA_MovementSpeedData` | `PDA_MovementSpeedData` | Movement speed settings |
| `UPDA_PoiseBreakAnimData` | `PDA_PoiseBreakAnimData` | Stagger animations |
| `UPDA_StatusEffect` | `PDA_StatusEffect` | Status effect definitions |
| `UPDA_Vendor` | `PDA_Vendor` | Vendor shop inventory |
| `UPDA_WeaponAbility` | `PDA_WeaponAbility` | Weapon skill definitions |
| `UPDA_WeaponAnimset` | `PDA_WeaponAnimset` | Weapon animation sets |

### Reparenting Steps (Data Assets)

```
For each Data Asset type (e.g., PDA_Item):

1. Find all instances in Content Browser:
   - Right-click the Blueprint parent (e.g., PDA_Item)
   - Select "Reference Viewer"
   - Note all child Data Assets

2. Reparent the parent Blueprint:
   - Open PDA_Item Blueprint
   - File > Reparent Blueprint
   - Select UPDA_Item
   - Compile and Save

3. Verify child assets:
   - Open each child Data Asset
   - Verify properties are preserved
   - Compile and Save

4. Test in editor:
   - Open an actor using this Data Asset
   - Verify the Data Asset loads correctly
```

### Testing Data Assets

**Before Migration:**
```
1. Note all items in player inventory
2. Note equipped weapon stats
3. Screenshot the settings menu
4. Note any active status effects
```

**After Migration:**
```
1. Play the game
2. Open inventory - verify items display correctly
3. Equip a weapon - verify stats match
4. Open settings - verify options appear
5. Apply a status effect - verify it activates
```

---

## 7. Components - 21 Items

### What They Are
Actor Components provide reusable functionality attached to actors.

### C++ Location
`Source/SLF_5_7/Converted/Components/`

### Reparenting Required: YES (for Blueprint component bases)

### Complete Component List

| C++ Class | Purpose | Attached To |
|-----------|---------|-------------|
| `UAC_ActionManager` | Handles player actions | Player Character |
| `UAC_AI_BehaviorManager` | AI state machine | Enemy Characters |
| `UAC_AI_Boss` | Boss-specific behavior | Boss Characters |
| `UAC_AI_CombatManager` | AI combat decisions | Enemy Characters |
| `UAC_AI_InteractionManager` | AI-NPC interactions | NPCs |
| `UAC_BuffManager` | Buff/debuff tracking | All Characters |
| `UAC_CollisionManager` | Weapon collision traces | All Characters |
| `UAC_CombatManager` | Combat state tracking | All Characters |
| `UAC_DebugCentral` | Debug visualization | Debug actors |
| `UAC_EquipmentManager` | Equipment slots | Player Character |
| `UAC_InputBuffer` | Input buffering | Player Character |
| `UAC_InteractionManager` | Interaction detection | Player Character |
| `UAC_InventoryManager` | Inventory system | Player Character |
| `UAC_LadderManager` | Ladder climbing | Player Character |
| `UAC_LootDropManager` | Loot spawning | Enemy Characters |
| `UAC_ProgressManager` | Game progress flags | Player Controller |
| `UAC_RadarElement` | Radar tracking | Trackable Actors |
| `UAC_RadarManager` | Radar system | Player Character |
| `UAC_SaveLoadManager` | Save/Load operations | Player Controller |
| `UAC_StatManager` | Character stats | All Characters |
| `UAC_StatusEffectManager` | Status effects | All Characters |

### Reparenting Steps (Components)

```
For Character Blueprints that own these components:

1. Open the Character Blueprint (e.g., B_Soulslike_Character)
2. In Components panel, select the component
3. In Details panel, note the current class
4. If it's a Blueprint component:
   a. Open that Blueprint component
   b. File > Reparent Blueprint
   c. Select the C++ equivalent
   d. Compile and Save
5. Return to the Character Blueprint
6. The component should now use C++ parent
7. Compile the Character Blueprint
```

### Testing Components

**AC_StatManager Test:**
```
1. Play as character
2. Note HP/Stamina values
3. Take damage - verify HP decreases
4. Sprint - verify Stamina decreases
5. Wait - verify regeneration works
```

**AC_InventoryManager Test:**
```
1. Pick up an item
2. Open inventory
3. Move item between slots
4. Drop item
5. Verify item appears in world
```

**AC_CombatManager Test:**
```
1. Lock onto enemy
2. Attack enemy
3. Get hit by enemy
4. Verify hit reactions play
5. Block an attack
```

**AC_EquipmentManager Test:**
```
1. Open equipment menu
2. Equip/unequip weapon
3. Verify mesh appears/disappears
4. Verify stats update
```

---

## 8. Classes/Actors - 109 Items

### C++ Location
`Source/SLF_5_7/Converted/Classes/`

### Categories

#### 8.1 Base Classes

| C++ Class | Purpose | Reparent Targets |
|-----------|---------|------------------|
| `AB_Action` | Base player action | All B_Action_* Blueprints |
| `AB_BaseCharacter` | Base character class | B_Soulslike_Character, B_Soulslike_Enemy |
| `AB_Stat` | Base stat class | All stat Blueprints (B_HP, B_Stamina, etc.) |
| `AB_AbilityEffectBase` | Base effect class | B_Buff, B_StatusEffect |
| `AB_Interactable` | Base interactable | B_Door, B_Container, B_Ladder |
| `AB_Item` | Base item | B_Weapon, B_Item_Shield |

#### 8.2 Actions (B_Action_*)

All 28 action classes should be reparented to their C++ equivalents.

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `AB_Action_Backstab` | B_Action_Backstab | Backstab execution |
| `AB_Action_ComboHeavy` | B_Action_ComboHeavy | Heavy attack combo |
| `AB_Action_ComboLight_L` | B_Action_ComboLight_L | Left-hand light attack |
| `AB_Action_ComboLight_R` | B_Action_ComboLight_R | Right-hand light attack |
| `AB_Action_Crouch` | B_Action_Crouch | Crouch toggle |
| `AB_Action_Dodge` | B_Action_Dodge | Dodge roll |
| `AB_Action_DrinkFlask_HP` | B_Action_DrinkFlask_HP | Health flask usage |
| `AB_Action_DualWieldAttack` | B_Action_DualWieldAttack | Dual wield attack |
| `AB_Action_Execute` | B_Action_Execute | Execution attack |
| `AB_Action_GuardCancel` | B_Action_GuardCancel | Cancel guard |
| `AB_Action_GuardEnd` | B_Action_GuardEnd | End guard stance |
| `AB_Action_GuardStart` | B_Action_GuardStart | Start guard stance |
| `AB_Action_Jump` | B_Action_Jump | Jump |
| `AB_Action_JumpAttack` | B_Action_JumpAttack | Jumping attack |
| `AB_Action_PickupItemMontage` | B_Action_PickupItemMontage | Item pickup animation |
| `AB_Action_ScrollWheel_LeftHand` | B_Action_ScrollWheel_LeftHand | Left equipment scroll |
| `AB_Action_ScrollWheel_RightHand` | B_Action_ScrollWheel_RightHand | Right equipment scroll |
| `AB_Action_ScrollWheel_Tools` | B_Action_ScrollWheel_Tools | Tool slot scroll |
| `AB_Action_SprintAttack` | B_Action_SprintAttack | Running attack |
| `AB_Action_StartSprinting` | B_Action_StartSprinting | Begin sprint |
| `AB_Action_StopSprinting` | B_Action_StopSprinting | End sprint |
| `AB_Action_ThrowProjectile` | B_Action_ThrowProjectile | Throw item |
| `AB_Action_TwoHandedStance_L` | B_Action_TwoHandedStance_L | Two-hand left weapon |
| `AB_Action_TwoHandedStance_R` | B_Action_TwoHandedStance_R | Two-hand right weapon |
| `AB_Action_UseEquippedTool` | B_Action_UseEquippedTool | Use equipped tool |
| `AB_Action_WeaponAbility` | B_Action_WeaponAbility | Weapon skill |

#### 8.3 Stats (B_*)

| C++ Class | Purpose |
|-----------|---------|
| `AB_HP` | Health points |
| `AB_Stamina` | Stamina resource |
| `AB_FP` | Focus points (mana) |
| `AB_Poise` | Poise (stagger resistance) |
| `AB_Stance` | Stance damage |
| `AB_Weight` | Equipment weight |
| `AB_Vigor` | Vigor attribute |
| `AB_Mind` | Mind attribute |
| `AB_Endurance` | Endurance attribute |
| `AB_Strength` | Strength attribute |
| `AB_Dexterity` | Dexterity attribute |
| `AB_Intelligence` | Intelligence attribute |
| `AB_Faith` | Faith attribute |
| `AB_Arcane` | Arcane attribute |
| `AB_Discovery` | Item discovery |
| `AB_IncantationPower` | Incantation scaling |

#### 8.4 Attack Power Stats (B_AP_*)

| C++ Class | Purpose |
|-----------|---------|
| `AB_AP_Physical` | Physical damage |
| `AB_AP_Fire` | Fire damage |
| `AB_AP_Frost` | Frost damage |
| `AB_AP_Lightning` | Lightning damage |
| `AB_AP_Holy` | Holy damage |
| `AB_AP_Magic` | Magic damage |

#### 8.5 Damage Negation Stats (B_DN_*)

| C++ Class | Purpose |
|-----------|---------|
| `AB_DN_Physical` | Physical defense |
| `AB_DN_Fire` | Fire resistance |
| `AB_DN_Frost` | Frost resistance |
| `AB_DN_Lightning` | Lightning resistance |
| `AB_DN_Holy` | Holy resistance |
| `AB_DN_Magic` | Magic resistance |

#### 8.6 Resistance Stats (B_Resistance_*)

| C++ Class | Purpose |
|-----------|---------|
| `AB_Resistance_Focus` | Madness resistance |
| `AB_Resistance_Immunity` | Poison/Plague resistance |
| `AB_Resistance_Robustness` | Bleed/Frostbite resistance |
| `AB_Resistance_Vitality` | Death Blight resistance |

#### 8.7 Characters

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `AB_BaseCharacter` | B_BaseCharacter | Base for all characters |
| `AB_Soulslike_Character` | B_Soulslike_Character | Player character |
| `AB_Soulslike_Enemy` | B_Soulslike_Enemy | Base enemy |
| `AB_Soulslike_Enemy_Guard` | B_Soulslike_Enemy_Guard | Guarding enemy variant |
| `AB_Soulslike_Enemy_Showcase` | B_Soulslike_Enemy_Showcase | Demo enemy |
| `AB_Soulslike_Boss` | B_Soulslike_Boss | Boss base |
| `AB_Soulslike_Boss_Malgareth` | B_Soulslike_Boss_Malgareth | Malgareth boss |
| `AB_Soulslike_NPC` | B_Soulslike_NPC | Base NPC |
| `AB_Soulslike_NPC_ShowcaseGuide` | B_Soulslike_NPC_ShowcaseGuide | Demo guide NPC |
| `AB_Soulslike_NPC_ShowcaseVendor` | B_Soulslike_NPC_ShowcaseVendor | Demo vendor NPC |

#### 8.8 Interactables

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `AB_Interactable` | B_Interactable | Base interactable |
| `AB_BossDoor` | B_BossDoor | Boss fog gate |
| `AB_Container` | B_Container | Lootable container |
| `AB_DeathTrigger` | B_DeathTrigger | Instant death zone |
| `AB_Destructible` | B_Destructible | Destructible prop |
| `AB_Door` | B_Door | Openable door |
| `AB_Door_Demo` | B_Door_Demo | Demo door |
| `AB_Ladder` | B_Ladder | Climbable ladder |
| `AB_LocationActor` | B_LocationActor | Location marker |
| `AB_PatrolPath` | B_PatrolPath | AI patrol waypoints |
| `AB_RestingPoint` | B_RestingPoint | Bonfire/checkpoint |
| `AB_Torch` | B_Torch | Lightable torch |

#### 8.9 Items

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `AB_Item` | B_Item | Base item |
| `AB_Weapon` | B_Weapon / B_Item_Weapon | Base weapon |
| `AB_Item_Shield` | B_Item_Shield | Shield |
| `AB_Item_Lantern` | B_Item_Lantern | Light source |
| `AB_Item_AI_Weapon` | B_Item_AI_Weapon | AI weapon base |
| `AB_Item_AI_Weapon_BossMace` | B_Item_AI_Weapon_BossMace | Boss mace |
| `AB_Item_AI_Weapon_Greatsword` | B_Item_AI_Weapon_Greatsword | AI greatsword |
| `AB_Item_AI_Weapon_Sword` | B_Item_AI_Weapon_Sword | AI sword |
| `AB_Item_Weapon_BossMace` | B_Item_Weapon_BossMace | Player boss mace |
| `AB_Item_Weapon_Greatsword` | B_Item_Weapon_Greatsword | Player greatsword |
| `AB_Item_Weapon_Katana` | B_Item_Weapon_Katana | Player katana |
| `AB_Item_Weapon_PoisonSword` | B_Item_Weapon_PoisonSword | Poison sword |
| `AB_Item_Weapon_SwordExample01` | B_Item_Weapon_SwordExample01 | Example sword 1 |
| `AB_Item_Weapon_SwordExample02` | B_Item_Weapon_SwordExample02 | Example sword 2 |
| `AB_PickupItem` | B_PickupItem | World item pickup |

#### 8.10 Buffs & Status Effects

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `AB_Buff` | B_Buff | Base buff |
| `AB_Buff_AttackPower` | B_Buff_AttackPower | Attack power buff |
| `AB_StatusEffect` | B_StatusEffect | Base status effect |
| `AB_StatusEffect_Bleed` | B_StatusEffect_Bleed | Bleed effect |
| `AB_StatusEffect_Burn` | B_StatusEffect_Burn | Burn effect |
| `AB_StatusEffect_Corruption` | B_StatusEffect_Corruption | Corruption effect |
| `AB_StatusEffect_Frostbite` | B_StatusEffect_Frostbite | Frostbite effect |
| `AB_StatusEffect_Madness` | B_StatusEffect_Madness | Madness effect |
| `AB_StatusEffect_Plague` | B_StatusEffect_Plague | Plague effect |
| `AB_StatusEffect_Poison` | B_StatusEffect_Poison | Poison effect |
| `AB_StatusEffectArea` | B_StatusEffectArea | Area effect |
| `AB_StatusEffectBuildup` | B_StatusEffectBuildup | Buildup tracker |
| `AB_StatusEffectOneShot` | B_StatusEffectOneShot | Instant effect |

#### 8.11 Projectiles

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `AB_BaseProjectile` | B_BaseProjectile | Base projectile |
| `AB_Projectile_Boss_Fireball` | B_Projectile_Boss_Fireball | Boss fireball |
| `AB_Projectile_ThrowingKnife` | B_Projectile_ThrowingKnife | Throwing knife |

#### 8.12 Misc Actors

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `AB_Chaos_ForceField` | B_Chaos_ForceField | Force field effect |
| `AB_DeathCurrency` | B_DeathCurrency | Currency drop on death |
| `AB_Demo_TimeSlider` | B_Demo_TimeSlider | Demo time control |
| `AB_DemoDisplay` | B_DemoDisplay | Demo display |
| `AB_DemoRoom` | B_DemoRoom | Demo environment |
| `AB_SequenceActor` | B_SequenceActor | Sequence trigger |
| `AB_ShowcaseEnemy_ExitCombat` | B_ShowcaseEnemy_ExitCombat | Demo combat exit |
| `AB_ShowcaseEnemy_StatDisplay` | B_ShowcaseEnemy_StatDisplay | Demo stat display |
| `AB_SkyManager` | B_SkyManager | Day/night sky |

#### 8.13 Animation Instances

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UB_SoulslikeAnimInstance` | B_SoulslikeAnimInstance | Player anim instance |
| `UB_EnemyAnimInstance` | B_EnemyAnimInstance | Enemy anim instance |

### Reparenting Steps (Actors)

```
IMPORTANT: Reparent in dependency order!

Order:
1. Base classes first (AB_Stat, AB_Action, AB_Interactable)
2. Then derived classes (AB_HP inherits AB_Stat)
3. Then character classes
4. Finally specific implementations

For each Blueprint:
1. Open the Blueprint
2. File > Reparent Blueprint
3. Select the C++ equivalent (e.g., AB_Weapon for B_Weapon)
4. Review warnings in dialog
5. Compile (Ctrl+F7)
6. Save
7. Test the specific functionality
```

### Testing Actors

**Character Test:**
```
1. Play game
2. Move character - verify movement
3. Attack - verify animations play
4. Take damage - verify hit reactions
5. Die - verify death state
6. Respawn - verify respawn works
```

**Item Test:**
```
1. Place weapon in world
2. Pick up weapon
3. Equip weapon
4. Attack - verify weapon mesh visible
5. Unequip - verify mesh disappears
```

**Enemy Test:**
```
1. Place enemy in level
2. Approach - verify detection
3. Combat - verify AI attacks
4. Kill - verify loot drops
5. Verify death animation
```

---

## 9. Widgets - 101 Items

### C++ Location
`Source/SLF_5_7/Converted/Classes/` (W_* files)

### Migration Status: PARTIAL (17 of 101 migrated)

### Migrated Widget List

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UW_UserWidget_Base` | W_UserWidget_Base | Base widget class |
| `UW_Navigable` | W_Navigable | Keyboard-navigable widget |
| `UW_HUD` | W_HUD | Main HUD container |
| `UW_Status` | W_Status | Status bars display |
| `UW_StatBlock` | W_StatBlock | Stat group display |
| `UW_StatEntry` | W_StatEntry | Single stat display |
| `UW_Inventory` | W_Inventory | Inventory screen |
| `UW_InventorySlot` | W_InventorySlot | Inventory item slot |
| `UW_Inventory_CategoryEntry` | W_Inventory_CategoryEntry | Inventory category tab |
| `UW_InventoryAction` | W_InventoryAction | Item action menu |
| `UW_InventoryActionAmount` | W_InventoryActionAmount | Quantity selection |
| `UW_Equipment` | W_Equipment | Equipment screen |
| `UW_EquipmentSlot` | W_EquipmentSlot | Equipment slot |
| `UW_ItemInfoEntry` | W_ItemInfoEntry | Item details display |
| `UW_GameMenu` | W_GameMenu | Pause/Game menu |
| `UW_GameMenu_Button` | W_GameMenu_Button | Menu button |

### Widget Reparenting Notes

**CRITICAL**: Widget reparenting requires extra care:

1. **Bind Widget**: Widgets with BindWidget properties must have matching widget names
2. **Animations**: Widget animations may need to be recreated
3. **Event Dispatchers**: Custom dispatchers need reconnection

### Reparenting Steps (Widgets)

```
For each Widget Blueprint:

1. Open the Widget Blueprint
2. Note all BindWidget references:
   - Look in C++ header for UPROPERTY(meta=(BindWidget))
   - Ensure your Blueprint has widgets with exact same names

3. File > Reparent Blueprint
4. Select the C++ widget class

5. If compilation fails:
   - Check widget names match BindWidget properties
   - Check animation names if any
   - Check event dispatcher bindings

6. Compile and Save

7. Test the widget:
   - Does it display correctly?
   - Does interaction work?
   - Do animations play?
```

### Testing Widgets

**HUD Test:**
```
1. Play game
2. Verify health bar visible
3. Take damage - bar decreases
4. Verify stamina bar visible
5. Sprint - bar decreases
```

**Inventory Test:**
```
1. Open inventory (Tab or I)
2. Navigate with keyboard/mouse
3. Select item - verify details display
4. Use item - verify effect
5. Close inventory
```

**Menu Test:**
```
1. Open pause menu (Escape)
2. Navigate options
3. Select Resume - game resumes
4. Select Quit - returns to main menu
```

---

## 10. Animation Assets - 31 Items

### C++ Location
`Source/SLF_5_7/Converted/Animation/`

### Categories

#### 10.1 Animation Blueprints (ABP_) - 6 Items

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UABP_Manny_PostProcess` | ABP_Manny_PostProcess | Male character post process |
| `UABP_Quinn_PostProcess` | ABP_Quinn_PostProcess | Female character post process |
| `UABP_SoulslikeBossNew` | ABP_SoulslikeBossNew | Boss animation graph |
| `UABP_SoulslikeCharacter_Additive` | ABP_SoulslikeCharacter_Additive | Player additive layer |
| `UABP_SoulslikeEnemy` | ABP_SoulslikeEnemy | Enemy animation graph |
| `UABP_SoulslikeNPC` | ABP_SoulslikeNPC | NPC animation graph |

#### 10.2 Anim Notifies (AN_) - 13 Items

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UAN_AdjustStat` | AN_AdjustStat | Modify stat during animation |
| `UAN_AI_SpawnProjectile` | AN_AI_SpawnProjectile | AI spawns projectile |
| `UAN_AoeDamage` | AN_AoeDamage | Area of effect damage |
| `UAN_CameraShake` | AN_CameraShake | Play camera shake |
| `UAN_FootstepTrace` | AN_FootstepTrace | Footstep sound/effect |
| `UAN_InterruptMontage` | AN_InterruptMontage | Cancel current montage |
| `UAN_LaunchField` | AN_LaunchField | Launch force field |
| `UAN_PlayCameraSequence` | AN_PlayCameraSequence | Play camera sequence |
| `UAN_SetAiState` | AN_SetAiState | Change AI state |
| `UAN_SetMovementMode` | AN_SetMovementMode | Change movement mode |
| `UAN_SpawnProjectile` | AN_SpawnProjectile | Player spawns projectile |
| `UAN_TryGuard` | AN_TryGuard | Attempt guard action |
| `UAN_WorldCameraShake` | AN_WorldCameraShake | World-space camera shake |

#### 10.3 Anim Notify States (ANS_) - 12 Items

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UANS_AI_FistTrace` | ANS_AI_FistTrace | AI fist weapon trace |
| `UANS_AI_RotateTowardsTarget` | ANS_AI_RotateTowardsTarget | AI rotation during attack |
| `UANS_AI_Trail` | ANS_AI_Trail | AI weapon trail effect |
| `UANS_AI_WeaponTrace` | ANS_AI_WeaponTrace | AI weapon hit detection |
| `UANS_FistTrace` | ANS_FistTrace | Player fist trace |
| `UANS_HyperArmor` | ANS_HyperArmor | Poise damage reduction |
| `UANS_InputBuffer` | ANS_InputBuffer | Buffer next input |
| `UANS_InvincibilityFrame` | ANS_InvincibilityFrame | I-frames during dodge |
| `UANS_RegisterAttackSequence` | ANS_RegisterAttackSequence | Register combo |
| `UANS_ToggleChaosField` | ANS_ToggleChaosField | Toggle chaos field |
| `UANS_Trail` | ANS_Trail | Weapon trail effect |
| `UANS_WeaponTrace` | ANS_WeaponTrace | Weapon hit detection |

### Reparenting Steps (Animation Assets)

```
Animation Blueprints:
1. These typically don't need reparenting
2. The C++ base classes provide native performance
3. Your existing Animation Blueprints should continue to work

Anim Notifies:
1. Open the Animation Montage using the notify
2. Select the notify in the timeline
3. In Details, change the class to C++ version
4. Save the montage

Anim Notify States:
1. Same process as Anim Notifies
2. Note: Duration settings are preserved
```

### Testing Animation Assets

**Anim Notify Test:**
```
1. Open an attack montage
2. Find the weapon trace notify state
3. Play the montage in editor
4. Verify trace visualization (if debug enabled)
5. Test in game - attacks should deal damage
```

**Anim Blueprint Test:**
```
1. Select character with the Animation BP
2. Play game
3. Walk/Run - verify locomotion blends
4. Attack - verify montages play
5. Get hit - verify hit reactions
```

---

## 11. AI Assets - 19 Items

### C++ Location
`Source/SLF_5_7/Converted/AI/`

### Categories

#### 11.1 AI Controller (AIC_) - 1 Item

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `AAIC_SoulslikeFramework` | AIC_SoulslikeFramework | Main AI controller |

#### 11.2 Behavior Tree Services (BTS_) - 5 Items

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UBTS_ChaseBounds` | BTS_ChaseBounds | Check chase distance |
| `UBTS_DistanceCheck` | BTS_DistanceCheck | Target distance |
| `UBTS_IsTargetDead` | BTS_IsTargetDead | Target death check |
| `UBTS_SetMovementModeBasedOnDistance` | BTS_SetMovementModeBasedOnDistance | Adjust movement speed |
| `UBTS_TryGetAbility` | BTS_TryGetAbility | Select next ability |

#### 11.3 Behavior Tree Tasks (BTT_) - 13 Items

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UBTT_ClearKey` | BTT_ClearKey | Clear blackboard key |
| `UBTT_GetCurrentLocation` | BTT_GetCurrentLocation | Store current location |
| `UBTT_GetRandomPoint` | BTT_GetRandomPoint | Random navigation point |
| `UBTT_GetRandomPointNearStartPosition` | BTT_GetRandomPointNearStartPosition | Random point near spawn |
| `UBTT_GetStrafePointAroundTarget` | BTT_GetStrafePointAroundTarget | Strafe position |
| `UBTT_PatrolPath` | BTT_PatrolPath | Follow patrol path |
| `UBTT_SetKey` | BTT_SetKey | Set blackboard key |
| `UBTT_SetMovementMode` | BTT_SetMovementMode | Change movement mode |
| `UBTT_SimpleMoveTo` | BTT_SimpleMoveTo | Basic movement |
| `UBTT_SwitchState` | BTT_SwitchState | Change AI state |
| `UBTT_SwitchToPreviousState` | BTT_SwitchToPreviousState | Return to previous state |
| `UBTT_ToggleFocus` | BTT_ToggleFocus | Toggle target focus |
| `UBTT_TryExecuteAbility` | BTT_TryExecuteAbility | Execute selected ability |

### Reparenting Steps (AI Assets)

```
AI Controller:
1. Open the AI Controller Blueprint
2. File > Reparent Blueprint
3. Select AAIC_SoulslikeFramework
4. Compile and Save

Behavior Tree Tasks/Services:
1. Open the Behavior Tree asset
2. Select each task/service node
3. In Details, note the class
4. If Blueprint, open that Blueprint
5. Reparent to C++ equivalent
6. Save all assets
```

### Testing AI

**AI Controller Test:**
```
1. Place enemy in level
2. Set AI Controller class to reparented BP
3. Play game
4. Approach enemy - should detect player
5. Verify behavior tree runs
```

**Behavior Tree Test:**
```
1. Enable AI debugging (Apostrophe key)
2. Select enemy
3. Watch behavior tree execution
4. Verify state transitions:
   - Idle -> Patrol
   - Patrol -> Chase (on detection)
   - Chase -> Combat (in range)
   - Combat -> Idle (target lost)
```

---

## 12. Game Framework - 9 Items

### C++ Location
`Source/SLF_5_7/Converted/Classes/`

### This is the MOST CRITICAL section - do this first!

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UGI_SoulslikeFramework` | GI_SoulslikeFramework | Game Instance |
| `AGM_SoulslikeFramework` | GM_SoulslikeFramework | Game Mode (gameplay) |
| `AGM_Menu_SoulslikeFramework` | GM_Menu_SoulslikeFramework | Game Mode (menus) |
| `AGS_SoulslikeFramework` | GS_SoulslikeFramework | Game State |
| `APC_SoulslikeFramework` | PC_SoulslikeFramework | Player Controller |
| `APC_Menu_SoulslikeFramework` | PC_Menu_SoulslikeFramework | Menu Player Controller |
| `APS_SoulslikeFramework` | PS_SoulslikeFramework | Player State |
| `USG_SoulslikeFramework` | SG_SoulslikeFramework | Save Game |
| `USG_SaveSlots` | SG_SaveSlots | Save Slot List |

### Reparenting Steps (Game Framework)

```
STEP 1: Reparent Game Instance
1. Open GI_SoulslikeFramework Blueprint
2. File > Reparent to UGI_SoulslikeFramework
3. Compile and Save

STEP 2: Set Project Game Instance
1. Edit > Project Settings
2. Project > Maps & Modes
3. Game Instance Class: GI_SoulslikeFramework (your BP)

STEP 3: Reparent Game Modes
1. Reparent GM_SoulslikeFramework to AGM_SoulslikeFramework
2. Reparent GM_Menu_SoulslikeFramework to AGM_Menu_SoulslikeFramework

STEP 4: Set Default Game Mode
1. Project Settings > Maps & Modes
2. Default GameMode: GM_SoulslikeFramework

STEP 5: Reparent Player Controller
1. Reparent PC_SoulslikeFramework to APC_SoulslikeFramework
2. Reparent PC_Menu_SoulslikeFramework to APC_Menu_SoulslikeFramework

STEP 6: Update Game Mode Settings
1. Open GM_SoulslikeFramework Blueprint
2. Set Default Pawn Class: B_Soulslike_Character
3. Set Player Controller Class: PC_SoulslikeFramework
4. Set Player State Class: PS_SoulslikeFramework
5. Set Game State Class: GS_SoulslikeFramework

STEP 7: Reparent Remaining
1. Reparent GS_SoulslikeFramework to AGS_SoulslikeFramework
2. Reparent PS_SoulslikeFramework to APS_SoulslikeFramework
3. Reparent SG_SoulslikeFramework to USG_SoulslikeFramework
```

### Testing Game Framework

**Game Instance Test:**
```
1. Play in Editor
2. Open Output Log
3. Verify no Game Instance errors
4. Test level transitions
5. Verify data persists between levels
```

**Game Mode Test:**
```
1. Play game
2. Verify correct pawn spawns
3. Verify HUD appears
4. Verify player controller receives input
```

**Save/Load Test:**
```
1. Progress in game (collect items, level up)
2. Find a save point
3. Save game
4. Close editor
5. Reopen and load save
6. Verify all progress restored:
   - Character location
   - Inventory
   - Stats
   - Progress flags
```

---

## 13. Other Assets

### 13.1 Camera Shakes (CS_) - 6 Items

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UCS_Boss_Roar` | CS_Boss_Roar | Boss roar shake |
| `UCS_Guard` | CS_Guard | Block impact shake |
| `UCS_JumpHit` | CS_JumpHit | Jump attack shake |
| `UCS_Seq_Handheld` | CS_Seq_Handheld | Cinematic handheld |
| `UCS_StrongHit` | CS_StrongHit | Heavy attack shake |
| `UCS_SubtleHit` | CS_SubtleHit | Light attack shake |

### 13.2 Blueprint Function Library (BFL_) - 1 Item

| C++ Class | Blueprint | Purpose |
|-----------|-----------|---------|
| `UBFL_Helper` | BFL_Helper | Static helper functions |

### Reparenting Camera Shakes

```
1. These are typically created as data assets, not Blueprints
2. If you have Blueprint camera shakes:
   - Open the Blueprint
   - File > Reparent to the C++ equivalent
3. Update references in AN_CameraShake notifies
```

### Using BFL_Helper

```
The Blueprint Function Library provides static functions.
After compilation, functions are available in any Blueprint:

1. Right-click in Blueprint graph
2. Search for function name
3. Functions appear under "BFL Helper" category

Example functions:
- GetDirectionFromAngle
- CalculateStatScaling
- FormatCurrency
```

---

## 14. Post-Migration Verification

### Complete System Test Checklist

#### Core Systems
```
[ ] Game starts without crashes
[ ] Main menu loads
[ ] New game creates character
[ ] Save/Load functions work
[ ] Settings persist between sessions
```

#### Character Systems
```
[ ] Player movement works
[ ] Camera follows player
[ ] Stats display correctly
[ ] Health regenerates
[ ] Stamina regenerates
[ ] Level up functions
```

#### Combat Systems
```
[ ] Light attack works
[ ] Heavy attack works
[ ] Dodge has i-frames
[ ] Guard blocks damage
[ ] Lock-on functions
[ ] Execution works
[ ] Status effects apply
[ ] Buffs apply
```

#### Inventory Systems
```
[ ] Items can be picked up
[ ] Inventory displays items
[ ] Items can be used
[ ] Items can be dropped
[ ] Equipment can be changed
[ ] Stats update with equipment
```

#### Enemy Systems
```
[ ] Enemies spawn
[ ] AI detects player
[ ] AI attacks player
[ ] AI takes damage
[ ] AI dies properly
[ ] Loot drops on death
```

#### Boss Systems
```
[ ] Boss door opens
[ ] Boss activates on enter
[ ] Boss attacks work
[ ] Boss phases transition
[ ] Boss death triggers rewards
```

#### UI Systems
```
[ ] HUD displays
[ ] Health bar updates
[ ] Stamina bar updates
[ ] Inventory opens/closes
[ ] Equipment screen works
[ ] Pause menu works
```

### Performance Test

```
1. Open a complex level (many enemies, effects)
2. Enable stat fps in console: stat fps
3. Note average FPS
4. Compare to pre-migration baseline
5. C++ migration should improve or maintain performance
```

---

## 15. Troubleshooting

### Common Issues

#### "CDO Constructor Error"

**Symptom**: Error about invalid default values in constructor

**Fix**:
```cpp
// In the C++ constructor, ensure defaults match Blueprint:
MyProperty = nullptr;  // For object pointers
MyValue = 0.0f;        // For numeric defaults
```

#### "Accessed None" After Reparent

**Symptom**: Blueprint errors about accessing None

**Cause**: Component or property names changed

**Fix**:
1. Open the Blueprint
2. Find red error nodes
3. Reconnect to correct property/component
4. If component missing, add it manually

#### "Interface Function Not Found"

**Symptom**: Interface calls fail after reparent

**Fix**:
1. Verify interface is still implemented
2. Check function signature matches C++
3. Re-implement interface in Blueprint if needed

#### "Widget Binding Failed"

**Symptom**: Widget doesn't display correctly

**Fix**:
1. Check BindWidget property names in C++ header
2. Ensure Blueprint widget names match exactly
3. Widget types must match (Button, TextBlock, etc.)

#### "Animation Notify Not Firing"

**Symptom**: Anim notifies don't trigger effects

**Fix**:
1. Open the montage/animation
2. Verify notify class is set to C++ version
3. Check notify is within valid time range
4. Verify receiving actor implements required interface

#### "AI Not Responding"

**Symptom**: Enemies stand still or don't attack

**Fix**:
1. Verify AI Controller is set on enemy
2. Check Behavior Tree is assigned
3. Verify Blackboard has required keys
4. Test perception component is detecting player

#### "Save Data Not Loading"

**Symptom**: Save files don't restore properly

**Fix**:
1. Verify SaveGame class reparented correctly
2. Check UPROPERTY(SaveGame) on saved properties
3. Clear old save files and test fresh save
4. Check serialization functions in SaveLoadManager

### Getting Help

If you encounter issues not covered here:

1. Check the UE5 Output Log for detailed errors
2. Enable verbose logging in DefaultEngine.ini:
   ```ini
   [Core.Log]
   LogBlueprintUserMessages=Verbose
   ```
3. Use Blueprint debugging breakpoints
4. Check the GitHub issues: https://github.com/wilshire059/bluedestiny/issues

---

## Quick Reference Card

### Reparenting Command Sequence

```
1. BACKUP PROJECT
2. Compile C++ (CompileBatch18.bat)
3. Open Unreal Editor
4. Reparent in order:
   a. Game Framework (GI, GM, PC, etc.)
   b. Data Assets
   c. Components (via their parent Blueprints)
   d. Base Actor Classes
   e. Derived Actor Classes
   f. Widgets
   g. Animation Assets
   h. AI Assets
5. Test each system after reparenting
6. Commit working changes frequently
```

### Critical Files Reference

| File Type | C++ Location |
|-----------|-------------|
| Enums | `Source/SLF_5_7/Converted/Enums/` |
| Structs | `Source/SLF_5_7/Converted/Structs/` |
| Interfaces | `Source/SLF_5_7/Converted/Interfaces/` |
| DataAssets | `Source/SLF_5_7/Converted/DataAssets/` |
| Components | `Source/SLF_5_7/Converted/Components/` |
| Classes | `Source/SLF_5_7/Converted/Classes/` |
| Animation | `Source/SLF_5_7/Converted/Animation/` |
| AI | `Source/SLF_5_7/Converted/AI/` |
| CameraShakes | `Source/SLF_5_7/Converted/CameraShakes/` |
| Libraries | `Source/SLF_5_7/Converted/Libraries/` |

---

*Document Version: 1.0*
*Generated: December 2024*
*For: Soulslike Framework UE5.7 Migration*
