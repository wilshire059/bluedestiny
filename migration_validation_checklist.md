# Migration Validation Checklist

This document contains exact values from BlueprintComponentExports that MUST be verified after reparenting each Blueprint.

---

## How to Use This Checklist

1. **Before reparenting**: Take screenshots of current component values
2. **After reparenting**: Compare against values below
3. **Check each box** when verified
4. **Run tests** at each phase

---

## B_BaseCharacter

**Source**: `BlueprintComponentExports/SoulslikeFramework_Blueprints__Characters_B_BaseCharacter.json`

### Capsule Component (CollisionCylinder)
- [ ] Capsule Half Height: `90.0`
- [ ] Capsule Radius: `35.0`
- [ ] Generate Overlap Events: `true`

### Character Mesh (CharacterMesh0)
- [ ] Skeletal Mesh: `/Game/SoulslikeFramework/Demo/SKM/Mannequins/Meshes/SKM_Manny.SKM_Manny`
- [ ] Animation Mode: `AnimationBlueprint`
- [ ] Relative Location: `(0, 0, -89)`
- [ ] Relative Rotation: `(0, -90, 0)`
- [ ] Cast Shadow: `true`

### Movement Component (CharMoveComp)
- [ ] Max Walk Speed: `500.0`
- [ ] Max Walk Speed Crouched: `300.0`
- [ ] Jump Z Velocity: `700.0`
- [ ] Air Control: `0.35`
- [ ] Gravity Scale: `1.75`
- [ ] Max Acceleration: `1500.0`
- [ ] Braking Deceleration Walking: `2000.0`
- [ ] Ground Friction: `8.0`
- [ ] Rotation Rate: `(0, 720, 0)`

### Target Lock Widget (TargetLockonWidget)
- [ ] Widget Class: `/Game/SoulslikeFramework/Widgets/World/W_TargetLock.W_TargetLock_C`
- [ ] Draw Size: `(500, 500)`
- [ ] Visible: `false`
- [ ] Relative Location: `(29.057, 0, 0)`

### Execution Widget (child of TargetLockonWidget)
- [ ] Widget Class: `/Game/SoulslikeFramework/Widgets/World/W_TargetExecutionIndicator.W_TargetExecutionIndicator_C`
- [ ] Draw Size: `(500, 500)`
- [ ] Visible: `false`

### Projectile Homing Position
- [ ] Relative Location: `(60, 0, 50)`
- [ ] Scale: `(0.25, 0.25, 0.25)`

### Actor Components
- [ ] AC_StatManager present
- [ ] AC_StatusEffectManager present
- [ ] AC_BuffManager present
- [ ] TL_GenericRotation (TimelineComponent) present
- [ ] TL_GenericLocation (TimelineComponent) present

### Test Checklist
- [ ] Spawns in level without errors
- [ ] Mesh visible
- [ ] Can move (WASD)
- [ ] Can jump
- [ ] Lock-on widget appears on enemy target

---

## B_Soulslike_Character

**Source**: `BlueprintComponentExports/SoulslikeFramework_Blueprints__Characters_B_Soulslike_Character.json`

### Inherits All from B_BaseCharacter PLUS:

### Character Mesh (CharacterMesh0) - OVERRIDES
- [ ] Anim Class: `/Game/SoulslikeFramework/Demo/_Animations/Locomotion/AnimBP/ABP_SoulslikeCharacter_Additive.ABP_SoulslikeCharacter_Additive_C`
- [ ] Relative Location: `(0, 0, -91)` (slightly different from base)
- [ ] Relative Rotation: `(0, -90, 0)`

### Movement Component - OVERRIDES
- [ ] Rotation Rate: `(0, 1080, 0)` (faster than base!)

### Modular Armor Meshes (children of CharacterMesh0)
- [ ] Head (SkeletalMeshComponent) - visible, follows master pose
- [ ] UpperBody (SkeletalMeshComponent) - visible, follows master pose
- [ ] LowerBody (SkeletalMeshComponent) - visible, follows master pose
- [ ] Arms (SkeletalMeshComponent) - visible, follows master pose

### Camera System
- [ ] CameraBoom (SpringArmComponent):
  - [ ] Target Arm Length: `300.0`
  - [ ] Socket Offset: `(0, 0, 25)`
  - [ ] Enable Camera Lag: `true`
  - [ ] Camera Lag Speed: `15.0`
  - [ ] Do Collision Test: `true`
  - [ ] Relative Location: `(0, 0, 20)`

- [ ] FollowCamera (CameraComponent):
  - [ ] Field of View: `90.0`
  - [ ] Projection Mode: `Perspective`

### Additional Components
- [ ] TargetSwapTracer - Location: `(142.5, 0, 0)`
- [ ] NPC LookAt Point (SphereComponent) - Radius: `32.0`, Location: `(0, 0, 71)`
- [ ] ChaosForceField (ChildActorComponent)
- [ ] ControlRotationArrow

### Actor Components (in addition to base)
- [ ] AC_InteractionManager
- [ ] AC_CombatManager
- [ ] AC_InputBuffer
- [ ] AC_ActionManager
- [ ] AC_LadderManager
- [ ] AC_DebugCentral
- [ ] TL_ResetCamera
- [ ] TL_DialogZoom
- [ ] TL_IK_HitReact

### Test Checklist
- [ ] All B_BaseCharacter tests pass
- [ ] Camera follows player
- [ ] Camera collision works (doesn't clip through walls)
- [ ] Modular armor meshes visible and animate
- [ ] Can interact with NPCs
- [ ] Combat system works
- [ ] Input buffering works

---

## B_Door

**Source**: `BlueprintComponentExports/SoulslikeFramework_Blueprints__WorldActors_Interactables_B_Door.json`

### Door Mesh (Interactable SM)
- [ ] Static Mesh: `/Game/SoulslikeFramework/Meshes/SM/PrisonDoor/SM_PrisonDoor.SM_PrisonDoor`
- [ ] Generate Overlap Events: `true`
- [ ] Relative Location: `(0, -75, 0)`
- [ ] Relative Rotation: `(0, 90, 0)`

### Door Frame
- [ ] Static Mesh: `/Game/SoulslikeFramework/Meshes/SM/PrisonDoor/SM_PrisonDoorArch.SM_PrisonDoorArch`
- [ ] Relative Rotation: `(0, 90, 0)`

### Opening Direction Arrow (DEBUG_OpeningDirection)
- [ ] Relative Location: `(0, 0, 150)`
- [ ] Scale: `(2, 2, 2)`
- [ ] Hidden In Game: `false` (visible for debugging)

### MoveTo Billboard
- [ ] Relative Location: `(100, 0, 60)`

### Timeline
- [ ] DoorTimeline component present

### Test Checklist
- [ ] Door mesh visible
- [ ] Door frame visible
- [ ] Interaction prompt appears
- [ ] Door opens when interacted
- [ ] Door animation plays (timeline)
- [ ] Opening direction arrow shows correct direction

---

## B_Item_Weapon

**Source**: `BlueprintComponentExports/SoulslikeFramework_Blueprints__WorldActors__Items_Weapons_B_Item_Weapon.json`

### Root Component
- [ ] DefaultSceneRoot Location: `(0, 0, -100000)` (hidden until equipped)

### Weapon Mesh (StaticMesh)
- [ ] Generate Overlap Events: `true`
- [ ] Visible: `true`
- [ ] Cast Shadow: `true`

### Trail VFX (Trail - NiagaraComponent)
- [ ] Asset: `/Game/SoulslikeFramework/VFX/Systems/NS_RibbonTrail.NS_RibbonTrail`
- [ ] Auto Activate: `false`
- [ ] Relative Location: `(0, 0, -100000)` (hidden until activated)

### Debug Components (optional)
- [ ] DEBUG_HandleVisualizer - Scale: `(0.15, 0.15, 0.15)`
- [ ] DEBUG_FacingDirection (ArrowComponent)

### Actor Components
- [ ] AC_CollisionManager present

### Test Checklist
- [ ] Weapon spawns in level
- [ ] Weapon can be equipped
- [ ] Weapon attaches to correct socket
- [ ] Weapon mesh visible when equipped
- [ ] Trail VFX plays during attack
- [ ] Collision traces detect hits

---

## B_Item_Weapon_Shield

**Source**: `BlueprintComponentExports/SoulslikeFramework_Blueprints__WorldActors__Items_Weapons_Player_B_Item_Weapon_Shield.json`

### Same as B_Item_Weapon PLUS:

### Shield-Specific
- [ ] Block collision configured
- [ ] Shield mesh assigned

### Test Checklist
- [ ] All B_Item_Weapon tests pass
- [ ] Can block incoming attacks
- [ ] Block animation plays
- [ ] Damage reduction applies

---

## Component Reparenting (AC_* Components)

When reparenting components attached to actors:

### AC_StatManager
- [ ] Class changed from `AC_StatManager_C` to `UAC_StatManager`
- [ ] Stats initialize correctly
- [ ] OnStatUpdated delegate fires

### AC_EquipmentManager
- [ ] Class changed to `UAC_EquipmentManager`
- [ ] Equipment slots work
- [ ] OnWeaponEquip delegate fires

### AC_InventoryManager
- [ ] Class changed to `UAC_InventoryManager`
- [ ] Items can be added/removed
- [ ] Currency updates work

### AC_CombatManager
- [ ] Class changed to `UAC_CombatManager`
- [ ] Damage processing works
- [ ] OnDeath delegate fires

### AC_CollisionManager
- [ ] Class changed to `UAC_CollisionManager`
- [ ] Trace channels configured
- [ ] OnActorTraced delegate fires

---

## Quick Validation Commands

### In Unreal Editor Console (` key):

```
// Check for missing components
GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponents()

// Check movement settings
GetWorld()->GetFirstPlayerController()->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed
```

### PIE (Play In Editor) Tests:

1. **Movement Test**: WASD movement, sprint, jump, crouch
2. **Combat Test**: Attack, block, dodge, lock-on
3. **Interaction Test**: Talk to NPC, open door, open chest
4. **Inventory Test**: Pick up item, equip weapon, use consumable

---

## Common Issues After Reparenting

| Symptom | Cause | Fix |
|---------|-------|-----|
| Character floats above ground | Mesh Z offset wrong | Set Location.Z to -89 or -91 |
| Movement too slow | MaxWalkSpeed reset | Set to 500 |
| Can't jump high enough | JumpZVelocity reset | Set to 700 |
| Camera inside character | SpringArm length wrong | Set TargetArmLength to 300 |
| Weapon invisible | Root at -100000 Z | Normal - moves when equipped |
| Trail doesn't play | AutoActivate true | Set to false, activate in code |
| Lock-on widget always visible | Visible set to true | Set to false |

---

## Asset Path Reference

Common asset paths you may need to reassign:

### Meshes
```
/Game/SoulslikeFramework/Demo/SKM/Mannequins/Meshes/SKM_Manny.SKM_Manny
/Game/SoulslikeFramework/Meshes/SM/PrisonDoor/SM_PrisonDoor.SM_PrisonDoor
/Game/SoulslikeFramework/Meshes/SM/PrisonDoor/SM_PrisonDoorArch.SM_PrisonDoorArch
```

### Animation Blueprints
```
/Game/SoulslikeFramework/Demo/_Animations/Locomotion/AnimBP/ABP_SoulslikeCharacter_Additive.ABP_SoulslikeCharacter_Additive_C
```

### Widgets
```
/Game/SoulslikeFramework/Widgets/World/W_TargetLock.W_TargetLock_C
/Game/SoulslikeFramework/Widgets/World/W_TargetExecutionIndicator.W_TargetExecutionIndicator_C
```

### VFX
```
/Game/SoulslikeFramework/VFX/Systems/NS_RibbonTrail.NS_RibbonTrail
```

---

*Generated from BlueprintComponentExports - December 2024*
