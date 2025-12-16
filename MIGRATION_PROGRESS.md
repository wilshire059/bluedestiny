# COMPREHENSIVE MIGRATION PROGRESS TRACKER

**CRITICAL: READ MIGRATION_PROTOCOL.md BEFORE EVERY MIGRATION**

## Status Legend
- [ ] Not started
- [P] Partial migration (NEEDS RE-MIGRATION)
- [x] Complete (fully verified)
- [SKIP] Editor-only, not needed

## Current Progress
- **Total JSONs**: 438
- **Complete**: 0
- **Partial (Need Re-migration)**: ~144 (all previous migrations are suspect)
- **Not Started**: ~278
- **Skip**: ~16 (Editor utilities)

## ACTIVE MIGRATION TARGET
**Currently Migrating**: AC_SaveLoadManager
**Last Checkpoint**: Completed AC_StatManager, analyzing remaining components

---

## CATEGORY: Actor Components (AC_*) - 21 files
Priority: HIGH - These are core gameplay components

| # | File | Status | Graphs | Functions | Completion | Notes |
|---|------|--------|--------|-----------|------------|-------|
| 1 | AC_ActionManager.json | [x] | 11 | 16 | HIGH | Complete re-migration |
| 2 | AC_StatManager.json | [x] | 18 | 16 | HIGH | Complete re-migration |
| 3 | AC_BuffManager.json | [x] | 1 | 7 | HIGH | Minimal graphs, well-implemented |
| 4 | AC_StatusEffectManager.json | [x] | 1 | 7 | HIGH | Minimal graphs, well-implemented |
| 5 | AC_InputBuffer.json | [x] | 2 | 4 | HIGH | Complete |
| 6 | AC_LadderManager.json | [x] | 3 | 4 | HIGH | Complete |
| 7 | AC_LootDropManager.json | [x] | 3 | 3 | HIGH | Complete |
| 8 | AC_DebugCentral.json | [P] | 3 | 2 | MED | 67% |
| 9 | AC_CollisionManager.json | [P] | 4 | 2 | MED | 50% |
| 10 | AC_RadarElement.json | [P] | 5 | 2 | LOW | 40% |
| 11 | AC_AI_BehaviorManager.json | [P] | 7 | 2 | LOW | 29% |
| 12 | AC_ProgressManager.json | [P] | 8 | 2 | LOW | 25% |
| 13 | AC_RadarManager.json | [P] | 10 | 4 | LOW | 40% |
| 14 | AC_AI_InteractionManager.json | [P] | 10 | 1 | LOW | 10% - CRITICAL |
| 15 | AC_SaveLoadManager.json | [P] | 13 | 4 | LOW | 31% - IN PROGRESS |
| 16 | AC_AI_Boss.json | [P] | 25 | 2 | LOW | 8% - CRITICAL |
| 17 | AC_EquipmentManager.json | [P] | 50 | 8 | LOW | 16% - CRITICAL |
| 18 | AC_InventoryManager.json | [P] | 51 | 6 | LOW | 12% - CRITICAL |
| 19 | AC_AI_CombatManager.json | [P] | 55 | 5 | LOW | 9% - CRITICAL |
| 20 | AC_CombatManager.json | [P] | 61 | 5 | LOW | 8% - CRITICAL |
| 21 | AC_InteractionManager.json | [P] | 64 | 3 | LOW | 5% - CRITICAL |

---

## CATEGORY: Animation Blueprints (ABP_*) - 6 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | ABP_Manny_PostProcess.json | [ ] | |
| 2 | ABP_Quinn_PostProcess.json | [ ] | |
| 3 | ABP_SoulslikeBossNew.json | [ ] | |
| 4 | ABP_SoulslikeCharacter_Additive.json | [ ] | |
| 5 | ABP_SoulslikeEnemy.json | [ ] | |
| 6 | ABP_SoulslikeNPC.json | [ ] | |

---

## CATEGORY: AI Controller (AIC_*) - 1 file
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | AIC_SoulslikeFramework.json | [ ] | |

---

## CATEGORY: Animation Layer Interfaces (ALI_*) - 2 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | ALI_LocomotionStates.json | [ ] | |
| 2 | ALI_OverlayStates.json | [ ] | |

---

## CATEGORY: Anim Notifies (AN_*) - 12 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | AN_AdjustStat.json | [ ] | |
| 2 | AN_AI_SpawnProjectile.json | [ ] | |
| 3 | AN_AoeDamage.json | [ ] | |
| 4 | AN_CameraShake.json | [ ] | |
| 5 | AN_FootstepTrace.json | [ ] | |
| 6 | AN_InterruptMontage.json | [ ] | |
| 7 | AN_LaunchField.json | [ ] | |
| 8 | AN_PlayCameraSequence.json | [ ] | |
| 9 | AN_SetAiState.json | [ ] | |
| 10 | AN_SetMovementMode.json | [ ] | |
| 11 | AN_SpawnProjectile.json | [ ] | |
| 12 | AN_TryGuard.json | [ ] | |
| 13 | AN_WorldCameraShake.json | [ ] | |

---

## CATEGORY: Anim Notify States (ANS_*) - 13 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | ANS_AI_FistTrace.json | [ ] | |
| 2 | ANS_AI_RotateTowardsTarget.json | [ ] | |
| 3 | ANS_AI_Trail.json | [ ] | |
| 4 | ANS_AI_WeaponTrace.json | [ ] | |
| 5 | ANS_FistTrace.json | [ ] | |
| 6 | ANS_HyperArmor.json | [ ] | |
| 7 | ANS_InputBuffer.json | [P] | Verify completeness |
| 8 | ANS_InvincibilityFrame.json | [ ] | |
| 9 | ANS_RegisterAttackSequence.json | [ ] | |
| 10 | ANS_ToggleChaosField.json | [ ] | |
| 11 | ANS_Trail.json | [ ] | |
| 12 | ANS_WeaponTrace.json | [ ] | |

---

## CATEGORY: Blueprint Classes/Actors (B_*) - 109 files
### B_Action_* (Player Actions) - 23 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | B_Action.json | [ ] | |
| 2 | B_Action_Backstab.json | [ ] | |
| 3 | B_Action_ComboHeavy.json | [ ] | |
| 4 | B_Action_ComboLight_L.json | [ ] | |
| 5 | B_Action_ComboLight_R.json | [ ] | |
| 6 | B_Action_Crouch.json | [ ] | |
| 7 | B_Action_Dodge.json | [ ] | |
| 8 | B_Action_DrinkFlask_HP.json | [ ] | |
| 9 | B_Action_DualWieldAttack.json | [ ] | |
| 10 | B_Action_Execute.json | [ ] | |
| 11 | B_Action_GuardCancel.json | [ ] | |
| 12 | B_Action_GuardEnd.json | [ ] | |
| 13 | B_Action_GuardStart.json | [ ] | |
| 14 | B_Action_Jump.json | [ ] | |
| 15 | B_Action_JumpAttack.json | [ ] | |
| 16 | B_Action_PickupItemMontage.json | [ ] | |
| 17 | B_Action_ScrollWheel_LeftHand.json | [ ] | |
| 18 | B_Action_ScrollWheel_RightHand.json | [ ] | |
| 19 | B_Action_ScrollWheel_Tools.json | [ ] | |
| 20 | B_Action_SprintAttack.json | [ ] | |
| 21 | B_Action_StartSprinting.json | [ ] | |
| 22 | B_Action_StopSprinting.json | [ ] | |
| 23 | B_Action_ThrowProjectile.json | [ ] | |
| 24 | B_Action_TwoHandedStance_L.json | [ ] | |
| 25 | B_Action_TwoHandedStance_R.json | [ ] | |
| 26 | B_Action_UseEquippedTool.json | [ ] | |
| 27 | B_Action_WeaponAbility.json | [ ] | |

### B_Stat Classes - 28 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | B_Stat.json | [P] | Verify completeness |
| 2 | B_HP.json | [P] | Verify completeness |
| 3 | B_FP.json | [P] | Verify completeness |
| 4 | B_Stamina.json | [P] | Verify completeness |
| 5 | B_Poise.json | [P] | Verify completeness |
| 6 | B_Stance.json | [P] | Verify completeness |
| 7 | B_Weight.json | [P] | Verify completeness |
| 8 | B_Discovery.json | [P] | Verify completeness |
| 9 | B_IncantationPower.json | [P] | Verify completeness |
| 10 | B_Arcane.json | [P] | Verify completeness |
| 11 | B_Dexterity.json | [P] | Verify completeness |
| 12 | B_Endurance.json | [P] | Verify completeness |
| 13 | B_Faith.json | [P] | Verify completeness |
| 14 | B_Intelligence.json | [P] | Verify completeness |
| 15 | B_Mind.json | [P] | Verify completeness |
| 16 | B_Strength.json | [P] | Verify completeness |
| 17 | B_Vigor.json | [P] | Verify completeness |
| 18 | B_StatusEffectBuildup.json | [P] | Verify completeness |
| 19 | B_AP_Fire.json | [P] | Verify completeness |
| 20 | B_AP_Frost.json | [P] | Verify completeness |
| 21 | B_AP_Holy.json | [P] | Verify completeness |
| 22 | B_AP_Lightning.json | [P] | Verify completeness |
| 23 | B_AP_Magic.json | [P] | Verify completeness |
| 24 | B_AP_Physical.json | [P] | Verify completeness |
| 25 | B_DN_Fire.json | [P] | Verify completeness |
| 26 | B_DN_Frost.json | [P] | Verify completeness |
| 27 | B_DN_Holy.json | [P] | Verify completeness |
| 28 | B_DN_Lightning.json | [P] | Verify completeness |
| 29 | B_DN_Magic.json | [P] | Verify completeness |
| 30 | B_DN_Physical.json | [P] | Verify completeness |
| 31 | B_Resistance_Focus.json | [P] | Verify completeness |
| 32 | B_Resistance_Immunity.json | [P] | Verify completeness |
| 33 | B_Resistance_Robustness.json | [P] | Verify completeness |
| 34 | B_Resistance_Vitality.json | [P] | Verify completeness |

### B_Item Classes - 14 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | B_Item.json | [ ] | |
| 2 | B_Item_AI_Weapon.json | [ ] | |
| 3 | B_Item_AI_Weapon_BossMace.json | [ ] | |
| 4 | B_Item_AI_Weapon_Greatsword.json | [ ] | |
| 5 | B_Item_AI_Weapon_Sword.json | [ ] | |
| 6 | B_Item_Lantern.json | [ ] | |
| 7 | B_Item_Weapon.json | [ ] | |
| 8 | B_Item_Weapon_BossMace.json | [ ] | |
| 9 | B_Item_Weapon_Greatsword.json | [ ] | |
| 10 | B_Item_Weapon_Katana.json | [ ] | |
| 11 | B_Item_Weapon_PoisonSword.json | [ ] | |
| 12 | B_Item_Weapon_Shield.json | [ ] | |
| 13 | B_Item_Weapon_SwordExample01.json | [ ] | |
| 14 | B_Item_Weapon_SwordExample02.json | [ ] | |

### B_StatusEffect Classes - 9 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | B_StatusEffect.json | [ ] | |
| 2 | B_StatusEffect_Bleed.json | [ ] | |
| 3 | B_StatusEffect_Burn.json | [ ] | |
| 4 | B_StatusEffect_Corruption.json | [ ] | |
| 5 | B_StatusEffect_Frostbite.json | [ ] | |
| 6 | B_StatusEffect_Madness.json | [ ] | |
| 7 | B_StatusEffect_Plague.json | [ ] | |
| 8 | B_StatusEffect_Poison.json | [ ] | |
| 9 | B_StatusEffectArea.json | [ ] | |
| 10 | B_StatusEffectOneShot.json | [ ] | |

### B_Soulslike Characters - 9 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | B_BaseCharacter.json | [P] | Verify completeness |
| 2 | B_Soulslike_Boss.json | [ ] | |
| 3 | B_Soulslike_Boss_Malgareth.json | [ ] | |
| 4 | B_Soulslike_Character.json | [ ] | |
| 5 | B_Soulslike_Enemy.json | [ ] | |
| 6 | B_Soulslike_Enemy_Guard.json | [ ] | |
| 7 | B_Soulslike_Enemy_Showcase.json | [ ] | |
| 8 | B_Soulslike_NPC.json | [ ] | |
| 9 | B_Soulslike_NPC_ShowcaseGuide.json | [ ] | |
| 10 | B_Soulslike_NPC_ShowcaseVendor.json | [ ] | |

### B_Other Classes - 24 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | B_AbilityEffectBase.json | [P] | Verify completeness |
| 2 | B_BaseProjectile.json | [P] | Verify completeness |
| 3 | B_BossDoor.json | [P] | Verify completeness |
| 4 | B_Buff.json | [P] | Verify completeness |
| 5 | B_Buff_AttackPower.json | [ ] | |
| 6 | B_Chaos_ForceField.json | [ ] | |
| 7 | B_Container.json | [ ] | |
| 8 | B_DeathCurrency.json | [ ] | |
| 9 | B_DeathTrigger.json | [ ] | |
| 10 | B_Demo_TimeSlider.json | [ ] | |
| 11 | B_DemoDisplay.json | [ ] | |
| 12 | B_DemoRoom.json | [ ] | |
| 13 | B_Destructible.json | [ ] | |
| 14 | B_Door.json | [P] | Verify completeness |
| 15 | B_Door_Demo.json | [ ] | |
| 16 | B_Interactable.json | [P] | Verify completeness |
| 17 | B_Ladder.json | [ ] | |
| 18 | B_LocationActor.json | [ ] | |
| 19 | B_PatrolPath.json | [ ] | |
| 20 | B_PickupItem.json | [ ] | |
| 21 | B_Projectile_Boss_Fireball.json | [ ] | |
| 22 | B_Projectile_ThrowingKnife.json | [ ] | |
| 23 | B_RestingPoint.json | [ ] | |
| 24 | B_SequenceActor.json | [ ] | |
| 25 | B_ShowcaseEnemy_ExitCombat.json | [ ] | |
| 26 | B_ShowcaseEnemy_StatDisplay.json | [ ] | |
| 27 | B_SkyManager.json | [ ] | |
| 28 | B_Torch.json | [ ] | |

---

## CATEGORY: Blueprint Function Libraries (BFL_*) - 1 file
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | BFL_Helper.json | [ ] | |

---

## CATEGORY: Blueprint Macro Libraries (BML_*) - 2 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | BML_HelperMacros.json | [ ] | |
| 2 | BML_StructConversion.json | [ ] | |

---

## CATEGORY: Blueprint Interfaces (BPI_*) - 18 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | BPI_AIC.json | [P] | Verify completeness |
| 2 | BPI_BossDoor.json | [P] | Verify completeness |
| 3 | BPI_Controller.json | [P] | Verify completeness |
| 4 | BPI_DestructibleHelper.json | [P] | Verify completeness |
| 5 | BPI_Enemy.json | [P] | Verify completeness |
| 6 | BPI_EnemyHealthbar.json | [P] | Verify completeness |
| 7 | BPI_Executable.json | [P] | Verify completeness |
| 8 | BPI_ExecutionIndicator.json | [P] | Verify completeness |
| 9 | BPI_GameInstance.json | [P] | Verify completeness |
| 10 | BPI_GenericCharacter.json | [P] | Verify completeness |
| 11 | BPI_Interactable.json | [P] | Verify completeness |
| 12 | BPI_Item.json | [P] | Verify completeness |
| 13 | BPI_MainMenu.json | [P] | Verify completeness |
| 14 | BPI_NPC.json | [P] | Verify completeness |
| 15 | BPI_Player.json | [P] | Verify completeness |
| 16 | BPI_Projectile.json | [P] | Verify completeness |
| 17 | BPI_RestingPoint.json | [P] | Verify completeness |
| 18 | BPI_StatEntry.json | [P] | Verify completeness |

---

## CATEGORY: Behavior Tree Services (BTS_*) - 5 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | BTS_ChaseBounds.json | [ ] | |
| 2 | BTS_DistanceCheck.json | [ ] | |
| 3 | BTS_IsTargetDead.json | [ ] | |
| 4 | BTS_SetMovementModeBasedOnDistance.json | [ ] | |
| 5 | BTS_TryGetAbility.json | [ ] | |

---

## CATEGORY: Behavior Tree Tasks (BTT_*) - 13 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | BTT_ClearKey.json | [ ] | |
| 2 | BTT_GetCurrentLocation.json | [ ] | |
| 3 | BTT_GetRandomPoint.json | [ ] | |
| 4 | BTT_GetRandomPointNearStartPosition.json | [ ] | |
| 5 | BTT_GetStrafePointAroundTarget.json | [ ] | |
| 6 | BTT_PatrolPath.json | [ ] | |
| 7 | BTT_SetKey.json | [ ] | |
| 8 | BTT_SetMovementMode.json | [ ] | |
| 9 | BTT_SimpleMoveTo.json | [ ] | |
| 10 | BTT_SwitchState.json | [ ] | |
| 11 | BTT_SwitchToPreviousState.json | [ ] | |
| 12 | BTT_ToggleFocus.json | [ ] | |
| 13 | BTT_TryExecuteAbility.json | [ ] | |

---

## CATEGORY: Control Rigs (CR_*) - 3 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | CR_Mannequin_BasicFootIK.json | [ ] | |
| 2 | CR_Mannequin_Procedural.json | [ ] | |
| 3 | CR_SoulslikeFramework.json | [ ] | |

---

## CATEGORY: Camera Shakes (CS_*) - 6 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | CS_Boss_Roar.json | [ ] | |
| 2 | CS_Guard.json | [ ] | |
| 3 | CS_JumpHit.json | [ ] | |
| 4 | CS_Seq_Handheld.json | [ ] | |
| 5 | CS_StrongHit.json | [ ] | |
| 6 | CS_SubtleHit.json | [ ] | |

---

## CATEGORY: Enums (E_*) - 37 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | E_ActionWeaponSlot.json | [P] | Verify completeness |
| 2 | E_AI_BossEncounterType.json | [P] | Verify completeness |
| 3 | E_AI_Senses.json | [P] | Verify completeness |
| 4 | E_AI_StateHandle.json | [P] | Verify completeness |
| 5 | E_AI_States.json | [P] | Verify completeness |
| 6 | E_AI_StrafeLocations.json | [P] | Verify completeness |
| 7 | E_AttackPower.json | [P] | Verify completeness |
| 8 | E_CalculationType.json | [P] | Verify completeness |
| 9 | E_DebugWindowScaleType.json | [P] | Verify completeness |
| 10 | E_Direction.json | [P] | Verify completeness |
| 11 | E_DotProductThreshold.json | [P] | Verify completeness |
| 12 | E_EnclosureLevel.json | [P] | Verify completeness |
| 13 | E_ExecutionType.json | [P] | Verify completeness |
| 14 | E_FadeTypes.json | [P] | Verify completeness |
| 15 | E_HitReactType.json | [P] | Verify completeness |
| 16 | E_InputAction.json | [P] | Verify completeness |
| 17 | E_InventoryAmountedActionType.json | [P] | Verify completeness |
| 18 | E_InventorySlotType.json | [P] | Verify completeness |
| 19 | E_ItemCategory.json | [P] | Verify completeness |
| 20 | E_ItemSubCategory.json | [P] | Verify completeness |
| 21 | E_KeyType.json | [P] | Verify completeness |
| 22 | E_LadderClimbState.json | [P] | Verify completeness |
| 23 | E_LightningMode.json | [P] | Verify completeness |
| 24 | E_MontageSection.json | [P] | Verify completeness |
| 25 | E_MovementType.json | [P] | Verify completeness |
| 26 | E_NpcState.json | [P] | Verify completeness |
| 27 | E_OverlayState.json | [P] | Verify completeness |
| 28 | E_Progress.json | [P] | Verify completeness |
| 29 | E_SaveBehavior.json | [P] | Verify completeness |
| 30 | E_SettingCategory.json | [P] | Verify completeness |
| 31 | E_SettingEntry.json | [P] | Verify completeness |
| 32 | E_StatCategory.json | [P] | Verify completeness |
| 33 | E_StatScaling.json | [P] | Verify completeness |
| 34 | E_TraceType.json | [P] | Verify completeness |
| 35 | E_ValueType.json | [P] | Verify completeness |
| 36 | E_VendorType.json | [P] | Verify completeness |
| 37 | E_WeaponAbilityHandle.json | [P] | Verify completeness |
| 38 | E_WorldMeshStyle.json | [P] | Verify completeness |

---

## CATEGORY: Editor Utilities (EUO_*, EUW_*) - 16 files [SKIP]
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | EUO_Hook.json | [SKIP] | Editor only |
| 2 | EUW_ActionBrowser.json | [SKIP] | Editor only |
| 3 | EUW_ActionCreator.json | [SKIP] | Editor only |
| 4 | EUW_AI_AbilityCreator.json | [SKIP] | Editor only |
| 5 | EUW_BatchExport.json | [SKIP] | Editor only |
| 6 | EUW_EnemyViewer.json | [SKIP] | Editor only |
| 7 | EUW_ItemBrowser.json | [SKIP] | Editor only |
| 8 | EUW_ItemCreator.json | [SKIP] | Editor only |
| 9 | EUW_Setup.json | [SKIP] | Editor only |
| 10 | EUW_StatusEffectBrowser.json | [SKIP] | Editor only |
| 11 | EUW_StatusEffectCreator.json | [SKIP] | Editor only |
| 12 | EUW_WeaponAbilityBrowser.json | [SKIP] | Editor only |
| 13 | EUW_WeaponAbilityCreator.json | [SKIP] | Editor only |
| 14 | EUW_WeaponAnimsetBrowser.json | [SKIP] | Editor only |
| 15 | EUW_WeaponAnimsetCreator.json | [SKIP] | Editor only |

---

## CATEGORY: Structs (F*) - 4 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | FAiAttackEntry.json | [P] | Verify completeness |
| 2 | FAnimationData.json | [P] | Verify completeness |
| 3 | FEquipmentStat.json | [P] | Verify completeness |
| 4 | FExecutionAnimInfo.json | [P] | Verify completeness |

---

## CATEGORY: Game Framework (GI_*, GM_*, GS_*, PC_*, PS_*) - 7 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | GI_SoulslikeFramework.json | [P] | Verify completeness |
| 2 | GM_Menu_SoulslikeFramework.json | [ ] | |
| 3 | GM_SoulslikeFramework.json | [ ] | |
| 4 | GS_SoulslikeFramework.json | [ ] | |
| 5 | PC_Menu_SoulslikeFramework.json | [ ] | |
| 6 | PC_SoulslikeFramework.json | [ ] | |
| 7 | PS_SoulslikeFramework.json | [ ] | |

---

## CATEGORY: Primary Data Assets (PDA_*) - 22 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | PDA_Action.json | [P] | Verify completeness |
| 2 | PDA_AI_Ability.json | [P] | Verify completeness |
| 3 | PDA_AnimData.json | [P] | Verify completeness |
| 4 | PDA_BaseCharacterInfo.json | [P] | Verify completeness |
| 5 | PDA_Buff.json | [P] | Verify completeness |
| 6 | PDA_Calculations.json | [P] | Verify completeness |
| 7 | PDA_CombatReactionAnimData.json | [P] | Verify completeness |
| 8 | PDA_CombatReactionAnimData_Player.json | [P] | Verify completeness |
| 9 | PDA_Credits.json | [P] | Verify completeness |
| 10 | PDA_CustomSettings.json | [P] | Verify completeness |
| 11 | PDA_DayNight.json | [P] | Verify completeness |
| 12 | PDA_DefaultMeshData.json | [P] | Verify completeness |
| 13 | PDA_Dialog.json | [P] | Verify completeness |
| 14 | PDA_ExecutionAnimData.json | [P] | Verify completeness |
| 15 | PDA_Item.json | [P] | Verify completeness |
| 16 | PDA_LadderAnimData.json | [P] | Verify completeness |
| 17 | PDA_LoadingScreens.json | [P] | Verify completeness |
| 18 | PDA_MainMenuData.json | [P] | Verify completeness |
| 19 | PDA_MovementSpeedData.json | [P] | Verify completeness |
| 20 | PDA_PoiseBreakAnimData.json | [P] | Verify completeness |
| 21 | PDA_StatusEffect.json | [P] | Verify completeness |
| 22 | PDA_Vendor.json | [P] | Verify completeness |
| 23 | PDA_WeaponAbility.json | [P] | Verify completeness |
| 24 | PDA_WeaponAnimset.json | [P] | Verify completeness |

---

## CATEGORY: Save Games (SG_*) - 2 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | SG_SaveSlots.json | [ ] | |
| 2 | SG_SoulslikeFramework.json | [P] | Verify completeness |

---

## CATEGORY: Widgets (W_*) - 101 files
| # | File | Status | Notes |
|---|------|--------|-------|
| 1 | W_AbilityDisplay.json | [ ] | |
| 2 | W_BigScreenMessage.json | [ ] | |
| 3 | W_Boss_Healthbar.json | [ ] | |
| 4 | W_Browser_Action.json | [ ] | |
| 5 | W_Browser_Action_Tooltip.json | [ ] | |
| 6 | W_Browser_Animset.json | [ ] | |
| 7 | W_Browser_Animset_OwnerEntry.json | [ ] | |
| 8 | W_Browser_AnimsetTooltip.json | [ ] | |
| 9 | W_Browser_Categories.json | [ ] | |
| 10 | W_Browser_CategoryEntry.json | [ ] | |
| 11 | W_Browser_Item.json | [ ] | |
| 12 | W_Browser_StatusEffect.json | [ ] | |
| 13 | W_Browser_StatusEffect_Tooltip.json | [ ] | |
| 14 | W_Browser_Tooltip.json | [ ] | |
| 15 | W_Browser_WeaponAbility.json | [ ] | |
| 16 | W_Browser_WeaponAbility_Tooltip.json | [ ] | |
| 17 | W_BrowserFilterEntry.json | [ ] | |
| 18 | W_Buff.json | [ ] | |
| 19 | W_CategoryEntry.json | [ ] | |
| 20 | W_CharacterSelection.json | [ ] | |
| 21 | W_CharacterSelection_StatEntry.json | [ ] | |
| 22 | W_CharacterSelectionCard.json | [ ] | |
| 23 | W_Crafting.json | [ ] | |
| 24 | W_CraftingAction.json | [ ] | |
| 25 | W_CraftingEntry.json | [ ] | |
| 26 | W_CraftingEntrySimple.json | [ ] | |
| 27 | W_CreditEntry.json | [ ] | |
| 28 | W_CreditEntry_Extra.json | [ ] | |
| 29 | W_CreditEntry_Sub.json | [ ] | |
| 30 | W_CreditEntry_Sub_NameEntry.json | [ ] | |
| 31 | W_Credits.json | [ ] | |
| 32 | W_CurrencyContainer.json | [ ] | |
| 33 | W_CurrencyEntry.json | [ ] | |
| 34 | W_Debug_ComponentSlot.json | [ ] | |
| 35 | W_Debug_ComponentTooltip.json | [ ] | |
| 36 | W_Debug_HUD.json | [ ] | |
| 37 | W_DebugWindow.json | [ ] | |
| 38 | W_Dialog.json | [ ] | |
| 39 | W_EnemyHealthbar.json | [ ] | |
| 40 | W_Equipment.json | [ ] | |
| 41 | W_Equipment_Item_AttackPower.json | [ ] | |
| 42 | W_Equipment_Item_DamageNegation.json | [ ] | |
| 43 | W_Equipment_Item_ItemEffect.json | [ ] | |
| 44 | W_Equipment_Item_OnUseEffect.json | [ ] | |
| 45 | W_Equipment_Item_RequiredStats.json | [ ] | |
| 46 | W_Equipment_Item_Resistance.json | [ ] | |
| 47 | W_Equipment_Item_StatScaling.json | [ ] | |
| 48 | W_Equipment_Item_StatsGranted.json | [ ] | |
| 49 | W_EquipmentSlot.json | [ ] | |
| 50 | W_Error.json | [ ] | |
| 51 | W_FirstLootNotification.json | [ ] | |
| 52 | W_GameMenu.json | [P] | Verify completeness |
| 53 | W_GameMenu_Button.json | [P] | Verify completeness |
| 54 | W_GenericButton.json | [ ] | |
| 55 | W_GenericError.json | [ ] | |
| 56 | W_HUD.json | [ ] | |
| 57 | W_Interaction.json | [ ] | |
| 58 | W_InteractionError.json | [ ] | |
| 59 | W_Inventory.json | [ ] | |
| 60 | W_Inventory_ActionButton.json | [ ] | |
| 61 | W_Inventory_CategoryEntry.json | [ ] | |
| 62 | W_InventoryAction.json | [P] | Verify completeness |
| 63 | W_InventoryActionAmount.json | [P] | Verify completeness |
| 64 | W_InventorySlot.json | [ ] | |
| 65 | W_ItemInfoEntry.json | [P] | Verify completeness |
| 66 | W_ItemInfoEntry_RequiredStats.json | [P] | Verify completeness |
| 67 | W_ItemInfoEntry_StatScaling.json | [P] | Verify completeness |
| 68 | W_ItemWheel_NextSlot.json | [ ] | |
| 69 | W_ItemWheelSlot.json | [ ] | |
| 70 | W_LevelCurrencyBlock_LevelUp.json | [ ] | |
| 71 | W_LevelEntry.json | [ ] | |
| 72 | W_LevelUp.json | [ ] | |
| 73 | W_LevelUpCost.json | [ ] | |
| 74 | W_LoadGame.json | [ ] | |
| 75 | W_LoadGame_Entry.json | [ ] | |
| 76 | W_LoadingScreen.json | [ ] | |
| 77 | W_LootNotification.json | [ ] | |
| 78 | W_MainMenu.json | [ ] | |
| 79 | W_MainMenu_Button.json | [ ] | |
| 80 | W_Navigable.json | [ ] | |
| 81 | W_Navigable_InputReader.json | [ ] | |
| 82 | W_NPC_Window.json | [ ] | |
| 83 | W_NPC_Window_Vendor.json | [ ] | |
| 84 | W_Radar.json | [ ] | |
| 85 | W_Radar_Cardinal.json | [ ] | |
| 86 | W_Radar_TrackedElement.json | [ ] | |
| 87 | W_Resources.json | [ ] | |
| 88 | W_RestMenu.json | [ ] | |
| 89 | W_RestMenu_Button.json | [ ] | |
| 90 | W_RestMenu_TimeEntry.json | [ ] | |
| 91 | W_Settings.json | [ ] | |
| 92 | W_Settings_CategoryEntry.json | [ ] | |
| 93 | W_Settings_CenteredText.json | [ ] | |
| 94 | W_Settings_ControlEntry.json | [ ] | |
| 95 | W_Settings_ControlsDisplay.json | [ ] | |
| 96 | W_Settings_Entry.json | [ ] | |
| 97 | W_Settings_InputKeySelector.json | [ ] | |
| 98 | W_Settings_KeyMapping.json | [ ] | |
| 99 | W_Settings_KeyMapping_Category.json | [ ] | |
| 100 | W_Settings_KeyMapping_Entry.json | [ ] | |
| 101 | W_Settings_PlayerCard.json | [ ] | |
| 102 | W_Settings_QuitConfirmation.json | [ ] | |
| 103 | W_SkipCinematic.json | [ ] | |
| 104 | W_StatBlock.json | [ ] | |
| 105 | W_StatBlock_LevelUp.json | [ ] | |
| 106 | W_StatEntry.json | [ ] | |
| 107 | W_StatEntry_LevelUp.json | [ ] | |
| 108 | W_StatEntry_StatName.json | [ ] | |
| 109 | W_StatEntry_Status.json | [ ] | |
| 110 | W_Status.json | [P] | Verify completeness |
| 111 | W_Status_LevelCurrencyBlock.json | [ ] | |
| 112 | W_Status_StatBlock.json | [ ] | |
| 113 | W_StatusEffectBar.json | [ ] | |
| 114 | W_StatusEffectNotification.json | [ ] | |
| 115 | W_TargetExecutionIndicator.json | [ ] | |
| 116 | W_TargetLock.json | [ ] | |
| 117 | W_TimePass.json | [ ] | |
| 118 | W_Utility_Asset.json | [ ] | |
| 119 | W_Utility_AssetTooltip.json | [ ] | |
| 120 | W_Utility_Component.json | [ ] | |
| 121 | W_VendorAction.json | [ ] | |
| 122 | W_VendorSlot.json | [ ] | |

---

## MIGRATION LOG
Track each migration with timestamp and details.

### Entry Format:
```
[YYYY-MM-DD HH:MM] FILE_NAME
- Graphs: X (list names)
- Functions: Y (list names)
- Events: Z (list names)
- Variables: N
- Status: COMPLETE/PARTIAL/FAILED
- Notes: Any issues encountered
```

### Log Entries:
(Add entries as migrations complete)

---

## CHECKPOINT RECOVERY
If context is lost:
1. Read this file to find last checkpoint
2. Read MIGRATION_PROTOCOL.md for instructions
3. Continue from the last incomplete entry
4. DO NOT start over - pick up where you left off
