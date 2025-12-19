# Step-by-Step Reparenting Guide

This guide provides **exact Blueprint name → exact C++ class** mappings with step-by-step instructions for each item.

## Naming Convention Clarification

| Blueprint Name | C++ Class Name | C++ File |
|---------------|----------------|----------|
| `B_Action` | `UB_Action` | `B_Action.h` |
| `B_BaseCharacter` | `AB_BaseCharacter` | `B_BaseCharacter.h` |
| `W_HUD` | `UW_HUD` | `W_HUD.h` |

- **UObject-derived**: Blueprint `B_*` → C++ class `UB_*`
- **AActor-derived**: Blueprint `B_*` → C++ class `AB_*`
- **UUserWidget-derived**: Blueprint `W_*` → C++ class `UW_*`

---

## Phase 1: Game Framework (DO FIRST)

### Step 1.1: Game Instance
```
Blueprint: GI_SoulslikeFramework
C++ Class: UGI_SoulslikeFramework

1. Open GI_SoulslikeFramework in Content Browser
2. File > Reparent Blueprint
3. Search for: GI_SoulslikeFramework (or UGI_SoulslikeFramework)
4. Click Reparent
5. Compile (Ctrl+F7)
6. Save

Then set in Project Settings:
1. Edit > Project Settings
2. Project > Maps & Modes
3. Set "Game Instance Class" to: GI_SoulslikeFramework
```

### Step 1.2: Save Game
```
Blueprint: SG_SoulslikeFramework
C++ Class: USG_SoulslikeFramework

1. Open SG_SoulslikeFramework
2. File > Reparent Blueprint
3. Search for: SG_SoulslikeFramework
4. Click Reparent
5. Compile and Save
```

---

## Phase 2: Base Classes (Reparent these FIRST, before derived classes)

### Step 2.1: B_Action (Base for all actions)
```
Blueprint: B_Action
C++ Class: UB_Action

1. Open B_Action Blueprint
2. File > Reparent Blueprint
3. Search for: B_Action (class is UB_Action)
4. Click Reparent
5. Compile and Save

DO THIS BEFORE any B_Action_* classes!
```

### Step 2.2: B_Stat (Base for all stats)
```
Blueprint: B_Stat
C++ Class: UB_Stat

1. Open B_Stat Blueprint
2. File > Reparent Blueprint
3. Search for: B_Stat
4. Click Reparent
5. Compile and Save

DO THIS BEFORE B_HP, B_Stamina, etc.!
```

### Step 2.3: B_BaseCharacter (Base for all characters)
```
Blueprint: B_BaseCharacter
C++ Class: AB_BaseCharacter

1. Open B_BaseCharacter Blueprint
2. File > Reparent Blueprint
3. Search for: B_BaseCharacter (class is AB_BaseCharacter)
4. Click Reparent
5. Compile and Save

DO THIS BEFORE B_Soulslike_Character, B_Soulslike_Enemy!
```

### Step 2.4: B_Interactable (Base for interactables)
```
Blueprint: B_Interactable
C++ Class: AB_Interactable

1. Open B_Interactable Blueprint
2. File > Reparent Blueprint
3. Search for: B_Interactable
4. Click Reparent
5. Compile and Save

DO THIS BEFORE B_Door, B_Container, B_Ladder, etc.!
```

### Step 2.5: B_Item (Base for items)
```
Blueprint: B_Item
C++ Class: AB_Item

1. Open B_Item Blueprint
2. File > Reparent Blueprint
3. Search for: B_Item
4. Click Reparent
5. Compile and Save

DO THIS BEFORE B_Item_Weapon, B_PickupItem!
```

### Step 2.6: B_AbilityEffectBase (Base for buffs/effects)
```
Blueprint: B_AbilityEffectBase
C++ Class: UB_AbilityEffectBase

1. Open B_AbilityEffectBase Blueprint
2. File > Reparent Blueprint
3. Search for: B_AbilityEffectBase
4. Click Reparent
5. Compile and Save

DO THIS BEFORE B_Buff, B_StatusEffect!
```

---

## Phase 3: Action Classes (26 items)

Reparent each in order. After B_Action is reparented, do these:

| # | Blueprint | C++ Class | File |
|---|-----------|-----------|------|
| 1 | B_Action_Backstab | UB_Action_Backstab | B_Action_Backstab.h |
| 2 | B_Action_ComboHeavy | UB_Action_ComboHeavy | B_Action_ComboHeavy.h |
| 3 | B_Action_ComboLight_L | UB_Action_ComboLight_L | B_Action_ComboLight_L.h |
| 4 | B_Action_ComboLight_R | UB_Action_ComboLight_R | B_Action_ComboLight_R.h |
| 5 | B_Action_Crouch | UB_Action_Crouch | B_Action_Crouch.h |
| 6 | B_Action_Dodge | UB_Action_Dodge | B_Action_Dodge.h |
| 7 | B_Action_DrinkFlask_HP | UB_Action_DrinkFlask_HP | B_Action_DrinkFlask_HP.h |
| 8 | B_Action_DualWieldAttack | UB_Action_DualWieldAttack | B_Action_DualWieldAttack.h |
| 9 | B_Action_Execute | UB_Action_Execute | B_Action_Execute.h |
| 10 | B_Action_GuardCancel | UB_Action_GuardCancel | B_Action_GuardCancel.h |
| 11 | B_Action_GuardEnd | UB_Action_GuardEnd | B_Action_GuardEnd.h |
| 12 | B_Action_GuardStart | UB_Action_GuardStart | B_Action_GuardStart.h |
| 13 | B_Action_Jump | UB_Action_Jump | B_Action_Jump.h |
| 14 | B_Action_JumpAttack | UB_Action_JumpAttack | B_Action_JumpAttack.h |
| 15 | B_Action_PickupItemMontage | UB_Action_PickupItemMontage | B_Action_PickupItemMontage.h |
| 16 | B_Action_ScrollWheel_LeftHand | UB_Action_ScrollWheel_LeftHand | B_Action_ScrollWheel_LeftHand.h |
| 17 | B_Action_ScrollWheel_RightHand | UB_Action_ScrollWheel_RightHand | B_Action_ScrollWheel_RightHand.h |
| 18 | B_Action_ScrollWheel_Tools | UB_Action_ScrollWheel_Tools | B_Action_ScrollWheel_Tools.h |
| 19 | B_Action_SprintAttack | UB_Action_SprintAttack | B_Action_SprintAttack.h |
| 20 | B_Action_StartSprinting | UB_Action_StartSprinting | B_Action_StartSprinting.h |
| 21 | B_Action_StopSprinting | UB_Action_StopSprinting | B_Action_StopSprinting.h |
| 22 | B_Action_ThrowProjectile | UB_Action_ThrowProjectile | B_Action_ThrowProjectile.h |
| 23 | B_Action_TwoHandedStance_L | UB_Action_TwoHandedStance_L | B_Action_TwoHandedStance_L.h |
| 24 | B_Action_TwoHandedStance_R | UB_Action_TwoHandedStance_R | B_Action_TwoHandedStance_R.h |
| 25 | B_Action_UseEquippedTool | UB_Action_UseEquippedTool | B_Action_UseEquippedTool.h |
| 26 | B_Action_WeaponAbility | UB_Action_WeaponAbility | B_Action_WeaponAbility.h |

**For each action:**
```
1. Open the Blueprint (e.g., B_Action_Dodge)
2. File > Reparent Blueprint
3. Search for the matching name (e.g., B_Action_Dodge)
4. Click Reparent
5. Compile (Ctrl+F7)
6. Save
```

---

## Phase 4: Stat Classes (30+ items)

After B_Stat is reparented, do these in any order:

### Core Stats
| Blueprint | C++ Class |
|-----------|-----------|
| B_HP | UB_HP |
| B_FP | UB_FP |
| B_Stamina | UB_Stamina |
| B_Poise | UB_Poise |
| B_Stance | UB_Stance |
| B_Weight | UB_Weight |
| B_Discovery | UB_Discovery |
| B_IncantationPower | UB_IncantationPower |

### Attribute Stats
| Blueprint | C++ Class |
|-----------|-----------|
| B_Vigor | UB_Vigor |
| B_Mind | UB_Mind |
| B_Endurance | UB_Endurance |
| B_Strength | UB_Strength |
| B_Dexterity | UB_Dexterity |
| B_Intelligence | UB_Intelligence |
| B_Faith | UB_Faith |
| B_Arcane | UB_Arcane |

### Attack Power Stats (B_AP_*)
| Blueprint | C++ Class |
|-----------|-----------|
| B_AP_Physical | UB_AP_Physical |
| B_AP_Fire | UB_AP_Fire |
| B_AP_Frost | UB_AP_Frost |
| B_AP_Lightning | UB_AP_Lightning |
| B_AP_Holy | UB_AP_Holy |
| B_AP_Magic | UB_AP_Magic |

### Damage Negation Stats (B_DN_*)
| Blueprint | C++ Class |
|-----------|-----------|
| B_DN_Physical | UB_DN_Physical |
| B_DN_Fire | UB_DN_Fire |
| B_DN_Frost | UB_DN_Frost |
| B_DN_Lightning | UB_DN_Lightning |
| B_DN_Holy | UB_DN_Holy |
| B_DN_Magic | UB_DN_Magic |

### Resistance Stats (B_Resistance_*)
| Blueprint | C++ Class |
|-----------|-----------|
| B_Resistance_Focus | UB_Resistance_Focus |
| B_Resistance_Immunity | UB_Resistance_Immunity |
| B_Resistance_Robustness | UB_Resistance_Robustness |
| B_Resistance_Vitality | UB_Resistance_Vitality |

---

## Phase 5: Character Classes

**Order matters! Do base classes first.**

### Step 5.1: B_BaseCharacter (if not done)
```
Blueprint: B_BaseCharacter
C++ Class: AB_BaseCharacter
```

### Step 5.2: B_Soulslike_Character (Player)
```
Blueprint: B_Soulslike_Character
C++ Class: AB_Soulslike_Character

1. Open B_Soulslike_Character
2. File > Reparent Blueprint
3. Search for: B_Soulslike_Character
4. Click Reparent
5. Compile and Save
```

### Step 5.3: B_Soulslike_Enemy (Base Enemy)
```
Blueprint: B_Soulslike_Enemy
C++ Class: AB_Soulslike_Enemy

1. Open B_Soulslike_Enemy
2. File > Reparent Blueprint
3. Search for: B_Soulslike_Enemy
4. Click Reparent
5. Compile and Save
```

### Step 5.4: Enemy Variants (after B_Soulslike_Enemy)
| Blueprint | C++ Class |
|-----------|-----------|
| B_Soulslike_Enemy_Guard | AB_Soulslike_Enemy_Guard |
| B_Soulslike_Enemy_Showcase | AB_Soulslike_Enemy_Showcase |

### Step 5.5: B_Soulslike_Boss
```
Blueprint: B_Soulslike_Boss
C++ Class: AB_Soulslike_Boss
```

### Step 5.6: Boss Variants
| Blueprint | C++ Class |
|-----------|-----------|
| B_Soulslike_Boss_Malgareth | AB_Soulslike_Boss_Malgareth |

### Step 5.7: B_Soulslike_NPC
```
Blueprint: B_Soulslike_NPC
C++ Class: AB_Soulslike_NPC
```

### Step 5.8: NPC Variants
| Blueprint | C++ Class |
|-----------|-----------|
| B_Soulslike_NPC_ShowcaseGuide | AB_Soulslike_NPC_ShowcaseGuide |
| B_Soulslike_NPC_ShowcaseVendor | AB_Soulslike_NPC_ShowcaseVendor |

---

## Phase 6: Interactable Classes

### Step 6.1: B_Interactable (if not done)
```
Blueprint: B_Interactable
C++ Class: AB_Interactable
```

### Step 6.2: Derived Interactables
| Blueprint | C++ Class |
|-----------|-----------|
| B_Door | AB_Door |
| B_Door_Demo | AB_Door_Demo |
| B_BossDoor | AB_BossDoor |
| B_Container | AB_Container |
| B_Ladder | AB_Ladder |
| B_RestingPoint | AB_RestingPoint |
| B_Destructible | AB_Destructible |
| B_DeathTrigger | AB_DeathTrigger |
| B_Torch | AB_Torch |
| B_LocationActor | AB_LocationActor |
| B_PatrolPath | AB_PatrolPath |

---

## Phase 7: Item Classes

### Step 7.1: B_Item (if not done)
```
Blueprint: B_Item
C++ Class: AB_Item
```

### Step 7.2: B_Item_Weapon (Base Weapon)
```
Blueprint: B_Item_Weapon
C++ Class: AB_Weapon

1. Open B_Item_Weapon
2. File > Reparent Blueprint
3. Search for: B_Weapon (class is AB_Weapon)
4. Click Reparent
5. Compile and Save
```

### Step 7.3: Player Weapons
| Blueprint | C++ Class |
|-----------|-----------|
| B_Item_Weapon_SwordExample01 | (inherits from AB_Weapon) |
| B_Item_Weapon_SwordExample02 | (inherits from AB_Weapon) |
| B_Item_Weapon_Katana | (inherits from AB_Weapon) |
| B_Item_Weapon_Greatsword | (inherits from AB_Weapon) |
| B_Item_Weapon_PoisonSword | (inherits from AB_Weapon) |
| B_Item_Weapon_BossMace | (inherits from AB_Weapon) |
| B_Item_Weapon_Shield | AB_Item_Shield |

### Step 7.4: AI Weapons
| Blueprint | C++ Class |
|-----------|-----------|
| B_Item_AI_Weapon | AB_Item_AI_Weapon |
| B_Item_AI_Weapon_Sword | (inherits from AB_Item_AI_Weapon) |
| B_Item_AI_Weapon_Greatsword | (inherits from AB_Item_AI_Weapon) |
| B_Item_AI_Weapon_BossMace | (inherits from AB_Item_AI_Weapon) |

### Step 7.5: Other Items
| Blueprint | C++ Class |
|-----------|-----------|
| B_Item_Lantern | AB_Item_Lantern |
| B_PickupItem | AB_PickupItem |

---

## Phase 8: Buff & Status Effect Classes

### Step 8.1: B_AbilityEffectBase (if not done)
```
Blueprint: B_AbilityEffectBase
C++ Class: UB_AbilityEffectBase
```

### Step 8.2: B_Buff
```
Blueprint: B_Buff
C++ Class: UB_Buff
```

### Step 8.3: Buff Variants
| Blueprint | C++ Class |
|-----------|-----------|
| B_Buff_AttackPower | UB_Buff_AttackPower |

### Step 8.4: B_StatusEffect
```
Blueprint: B_StatusEffect
C++ Class: UB_StatusEffect
```

### Step 8.5: Status Effect Variants
| Blueprint | C++ Class |
|-----------|-----------|
| B_StatusEffect_Bleed | UB_StatusEffect_Bleed |
| B_StatusEffect_Burn | UB_StatusEffect_Burn |
| B_StatusEffect_Frostbite | UB_StatusEffect_Frostbite |
| B_StatusEffect_Poison | UB_StatusEffect_Poison |
| B_StatusEffect_Corruption | UB_StatusEffect_Corruption |
| B_StatusEffect_Madness | UB_StatusEffect_Madness |
| B_StatusEffect_Plague | UB_StatusEffect_Plague |

### Step 8.6: Other Effect Classes
| Blueprint | C++ Class |
|-----------|-----------|
| B_StatusEffectArea | UB_StatusEffectArea |
| B_StatusEffectBuildup | UB_StatusEffectBuildup |
| B_StatusEffectOneShot | UB_StatusEffectOneShot |

---

## Phase 9: Widget Classes

### Step 9.1: W_UserWidget_Base (Base Widget)
```
Blueprint: W_UserWidget_Base
C++ Class: UW_UserWidget_Base

1. Open W_UserWidget_Base
2. File > Reparent Blueprint
3. Search for: W_UserWidget_Base
4. Click Reparent
5. Compile and Save

DO THIS BEFORE other widgets!
```

### Step 9.2: W_Navigable
```
Blueprint: W_Navigable
C++ Class: UW_Navigable
```

### Step 9.3: Other Widgets
| Blueprint | C++ Class |
|-----------|-----------|
| W_HUD | UW_HUD |
| W_Status | UW_Status |
| W_StatBlock | UW_StatBlock |
| W_StatEntry | UW_StatEntry |
| W_Inventory | UW_Inventory |
| W_InventorySlot | UW_InventorySlot |
| W_Inventory_CategoryEntry | UW_Inventory_CategoryEntry |
| W_InventoryAction | UW_InventoryAction |
| W_InventoryActionAmount | UW_InventoryActionAmount |
| W_Equipment | UW_Equipment |
| W_EquipmentSlot | UW_EquipmentSlot |
| W_ItemInfoEntry | UW_ItemInfoEntry |
| W_GameMenu | UW_GameMenu |
| W_GameMenu_Button | UW_GameMenu_Button |

---

## Phase 10: Miscellaneous Classes

### Projectiles
| Blueprint | C++ Class |
|-----------|-----------|
| B_BaseProjectile | AB_BaseProjectile |
| B_Projectile_ThrowingKnife | AB_Projectile_ThrowingKnife |
| B_Projectile_Boss_Fireball | AB_Projectile_Boss_Fireball |

### Other Actors
| Blueprint | C++ Class |
|-----------|-----------|
| B_SkyManager | AB_SkyManager |
| B_Chaos_ForceField | AB_Chaos_ForceField |
| B_DeathCurrency | AB_DeathCurrency |
| B_SequenceActor | AB_SequenceActor |
| B_DemoDisplay | AB_DemoDisplay |
| B_DemoRoom | AB_DemoRoom |
| B_Demo_TimeSlider | AB_Demo_TimeSlider |
| B_ShowcaseEnemy_ExitCombat | AB_ShowcaseEnemy_ExitCombat |
| B_ShowcaseEnemy_StatDisplay | AB_ShowcaseEnemy_StatDisplay |

### Animation Instances
| Blueprint | C++ Class |
|-----------|-----------|
| B_SoulslikeAnimInstance | UB_SoulslikeAnimInstance |
| B_EnemyAnimInstance | UB_EnemyAnimInstance |

---

## Quick Reference: How to Search in Reparent Dialog

When you click "File > Reparent Blueprint", the search box appears. Here's what to search for:

| Blueprint Name | Search For |
|---------------|------------|
| B_Action | `B_Action` or `UB_Action` |
| B_BaseCharacter | `B_BaseCharacter` or `AB_BaseCharacter` |
| W_HUD | `W_HUD` or `UW_HUD` |
| GI_SoulslikeFramework | `GI_SoulslikeFramework` or `UGI_SoulslikeFramework` |

The search should find the C++ class. If it doesn't appear:
1. Make sure C++ compiled successfully
2. Try searching with or without the U/A prefix
3. Check the exact spelling

---

## Troubleshooting

### "Class not found in reparent dialog"
- Compile C++ first: `CompileBatch18.bat`
- Restart Unreal Editor
- Search without prefix (e.g., `B_Action` instead of `UB_Action`)

### "Compile error after reparent"
- Check for renamed properties in C++ vs Blueprint
- Look for red nodes - reconnect them
- Check component names match

### "Widget doesn't display correctly"
- C++ widgets use `BindWidget` - widget names must match exactly
- Check the C++ header for required widget names

---

*Generated: December 2024*
