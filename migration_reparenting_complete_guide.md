# Complete Blueprint Reparenting Guide

This guide provides step-by-step instructions for reparenting Blueprints to their new C++ base classes, including handling duplicate components, manual data verification, and testing procedures.

---

## Table of Contents
1. [Understanding the Duplicate Component Problem](#understanding-the-duplicate-component-problem)
2. [Pre-Reparenting Checklist](#pre-reparenting-checklist)
3. [Reparenting Procedure](#reparenting-procedure)
4. [Post-Reparenting Validation](#post-reparenting-validation)
5. [Manual Data Reference Tables](#manual-data-reference-tables)
6. [Testing Procedures](#testing-procedures)
7. [Blueprint-Specific Instructions](#blueprint-specific-instructions)

---

## Understanding the Duplicate Component Problem

### Why Duplicates Occur
When you reparent a Blueprint to a C++ class:
1. The C++ constructor creates components (e.g., `StaticMeshComponent`, `CollisionManager`)
2. The Blueprint already has components with the same purpose but different names
3. Result: You get BOTH sets of components

### Solution: Delete Blueprint Components BEFORE Reparenting
You must delete the Blueprint-side components FIRST, then reparent. The C++ class will provide the equivalent components.

---

## Pre-Reparenting Checklist

### Before You Start (Per Blueprint)

- [ ] **Document current state** - Take screenshots of:
  - [ ] Component hierarchy in Blueprint editor
  - [ ] Details panel for key components (meshes, materials)
  - [ ] Any custom default values

- [ ] **Record asset references** from BlueprintComponentExports:
  - [ ] Skeletal Mesh paths
  - [ ] Static Mesh paths
  - [ ] Material paths
  - [ ] Widget class paths
  - [ ] Niagara/VFX asset paths
  - [ ] Animation Blueprint paths

- [ ] **Record transform data**:
  - [ ] Relative locations
  - [ ] Relative rotations
  - [ ] Relative scales

- [ ] **Record numeric settings**:
  - [ ] Movement speeds
  - [ ] Capsule sizes
  - [ ] Physics settings

---

## Reparenting Procedure

### Phase 1: Preparation (In Blueprint Editor)

1. **Open the Blueprint** in Unreal Editor
2. **Go to Components tab**
3. **Identify components that will be duplicated**:
   - Components created by C++ constructor
   - Components with same purpose in Blueprint

4. **For each duplicate component**:
   ```
   a. Select the Blueprint component
   b. Copy any custom property values (mesh, materials, transforms)
   c. DELETE the Blueprint component
   ```

5. **Save the Blueprint** (still has old parent)

### Phase 2: Reparent

1. **Open Class Settings** (toolbar button or File menu)
2. **Click Parent Class dropdown**
3. **Search for the C++ class** (e.g., `AB_BaseCharacter`, `UAC_StatManager`)
4. **Select the new parent**
5. **Compile the Blueprint** (may show warnings - this is normal)
6. **Save the Blueprint**

### Phase 3: Restore Data

1. **Go to Components tab**
2. **Select C++ components** (they now exist from the new parent)
3. **Restore property values**:
   - Assign meshes
   - Assign materials
   - Set transforms
   - Configure other properties

4. **Compile and Save**

---

## Post-Reparenting Validation

### Immediate Checks

- [ ] No duplicate components in hierarchy
- [ ] All required components present
- [ ] No compilation errors
- [ ] No "None" references in Details panel

### Property Validation

For each component, verify against BlueprintComponentExports data:

| Property Type | How to Verify |
|---------------|---------------|
| Mesh Reference | Details panel → Mesh property |
| Material | Details panel → Materials array |
| Transform | Details panel → Transform section |
| Widget Class | Details panel → Widget Class |
| Collision | Details panel → Collision section |

---

## Manual Data Reference Tables

### B_BaseCharacter Components

| Component | C++ Name | Blueprint Name | Manual Data Required |
|-----------|----------|----------------|---------------------|
| Capsule | CapsuleComponent (inherited) | CollisionCylinder | Height: 90, Radius: 35 |
| Mesh | Mesh (inherited) | CharacterMesh0 | SKM_Manny, AnimBP, Location: (0,0,-89), Rotation: (0,-90,0) |
| Movement | CharacterMovement (inherited) | CharMoveComp | MaxWalkSpeed: 500, JumpZ: 700, GravityScale: 1.75 |
| TargetLock Widget | TargetLockonWidget | TargetLockonWidget | W_TargetLock class, DrawSize: 500x500 |
| Execution Widget | (child of above) | ExecutionWidget | W_TargetExecutionIndicator class |
| Homing Position | ProjectileHomingPosition | ProjectileHomingPosition | Location: (60, 0, 50), Scale: 0.25 |

### B_Item_Weapon Components

| Component | C++ Name | Blueprint Name | Manual Data Required |
|-----------|----------|----------------|---------------------|
| Root | DefaultSceneRoot | DefaultSceneRoot | Location: (0,0,-100000) |
| Static Mesh | WeaponStaticMesh | StaticMesh | Assign weapon mesh |
| Trail VFX | Trail (if exists) | Trail | NS_RibbonTrail, AutoActivate: false |
| Collision | CollisionManager | AC_CollisionManager | Trace settings |

### B_Door Components

| Component | C++ Name | Blueprint Name | Manual Data Required |
|-----------|----------|----------------|---------------------|
| Door Frame | DoorFrame | DoorFrame | Assign door mesh |
| Timeline | DoorTimeline | DoorTimeline | Curve assignment |
| Arrow | OpeningDirection | OpeningDirection | Direction indicator |

### Movement Component Settings (B_BaseCharacter)

```
MaxWalkSpeed: 500.0
MaxWalkSpeedCrouched: 300.0
JumpZVelocity: 700.0
AirControl: 0.35
GravityScale: 1.75
MaxAcceleration: 1500.0
BrakingDecelerationWalking: 2000.0
GroundFriction: 8.0
RotationRate: (0, 720, 0)
```

---

## Testing Procedures

### Before Reparenting Tests

Run these tests BEFORE making changes to establish baseline:

#### For Characters (B_BaseCharacter, B_Soulslike_Character, etc.)

1. **Spawn Test**
   - [ ] Place actor in level
   - [ ] Press Play
   - [ ] Actor spawns without errors in Output Log

2. **Movement Test**
   - [ ] Character moves with WASD
   - [ ] Sprint works (if applicable)
   - [ ] Jump works
   - [ ] Crouch works

3. **Visual Test**
   - [ ] Mesh visible
   - [ ] Materials correct
   - [ ] Animations playing

4. **Combat Test** (if applicable)
   - [ ] Can lock on to target
   - [ ] Lock-on widget appears
   - [ ] Can attack

#### For Weapons (B_Item_Weapon, etc.)

1. **Spawn Test**
   - [ ] Weapon spawns in level
   - [ ] No errors in Output Log

2. **Equip Test**
   - [ ] Can equip weapon
   - [ ] Attaches to correct socket
   - [ ] Mesh visible

3. **Combat Test**
   - [ ] Attack traces work
   - [ ] Damage applies
   - [ ] Trail VFX plays (if applicable)

#### For Interactables (B_Door, B_Container, etc.)

1. **Spawn Test**
   - [ ] Actor spawns in level
   - [ ] Mesh visible

2. **Interaction Test**
   - [ ] Interaction prompt appears
   - [ ] Interaction executes
   - [ ] Animation/timeline plays

### After Reparenting Tests

Run the SAME tests after reparenting. Results should be identical.

#### Comparison Checklist

| Test | Before | After | Match? |
|------|--------|-------|--------|
| Spawns correctly | | | |
| No console errors | | | |
| Mesh visible | | | |
| Materials correct | | | |
| Movement works | | | |
| Interactions work | | | |
| Combat works | | | |

---

## Blueprint-Specific Instructions

### Phase 1: Base Classes (Do First)

These must be reparented FIRST as other Blueprints depend on them.

#### 1.1 B_BaseCharacter → AB_BaseCharacter

**Components to DELETE from Blueprint before reparenting:**
- None (ACharacter components are handled automatically)

**After reparenting, verify/set:**
```
CharacterMesh0:
  - Skeletal Mesh: /Game/SoulslikeFramework/Demo/SKM/Mannequins/Meshes/SKM_Manny
  - Anim Class: (set to your AnimBP)
  - Location: (0, 0, -89)
  - Rotation: (0, -90, 0)

CharacterMovement:
  - Max Walk Speed: 500
  - Jump Z Velocity: 700
  - Gravity Scale: 1.75
  - Max Acceleration: 1500

TargetLockonWidget:
  - Widget Class: W_TargetLock
  - Draw Size: (500, 500)
  - Visible: false (hidden until lock-on)
```

**Test:** Spawn in level, verify movement and mesh.

---

#### 1.2 B_Item → AB_Item

**Components to DELETE from Blueprint before reparenting:**
- DefaultSceneRoot (if C++ creates one)
- BillboardComponent (if duplicated)

**After reparenting, verify/set:**
```
- ItemInfo property (if using data asset)
```

**Test:** Spawn in level, verify no errors.

---

#### 1.3 B_Weapon → AB_Weapon

**Components to DELETE from Blueprint before reparenting:**
- StaticMesh/SkeletalMesh (C++ has WeaponStaticMesh/WeaponSkeletalMesh)
- AC_CollisionManager (C++ creates this)

**After reparenting, verify/set:**
```
WeaponStaticMesh OR WeaponSkeletalMesh:
  - Assign correct mesh
  - Set collision presets

CollisionManager:
  - Configure trace channels
```

**Test:** Equip weapon, verify mesh and collision traces.

---

### Phase 2: Derived Characters

#### 2.1 B_Soulslike_Character → AB_Soulslike_Character

**Prerequisite:** B_BaseCharacter already reparented

**Components to DELETE:**
- Any duplicated from B_BaseCharacter

**After reparenting, verify/set:**
```
- All B_BaseCharacter settings (inherited)
- Player-specific components
- Input settings
```

**Test:** Full player movement, combat, inventory access.

---

#### 2.2 B_Soulslike_Enemy → AB_Soulslike_Enemy

**Prerequisite:** B_BaseCharacter already reparented

**Components to DELETE:**
- Duplicates from B_BaseCharacter

**After reparenting, verify/set:**
```
- AI Controller class
- Behavior Tree reference
- Combat settings
```

**Test:** AI spawns, patrols, detects player, attacks.

---

### Phase 3: Items and Weapons

#### 3.1 B_Item_Weapon → AB_Item_Weapon

**Prerequisite:** B_Weapon already reparented

**Components to DELETE from Blueprint:**
- StaticMesh (use C++ WeaponStaticMesh)
- Trail NiagaraComponent (if C++ has it)
- AC_CollisionManager (C++ creates this)
- DEBUG components (optional, can keep)

**After reparenting, verify/set:**
```
WeaponStaticMesh:
  - Static Mesh: (assign your weapon mesh)
  - Generate Overlap Events: true

Trail (NiagaraComponent):
  - Asset: /Game/SoulslikeFramework/VFX/Systems/NS_RibbonTrail
  - Auto Activate: false
  - Location: (0, 0, -100000) [hidden until activated]

CollisionManager:
  - Trace Channel: Weapon
  - Trace sockets configured
```

**Test:**
1. Spawn weapon in level
2. Equip to character
3. Attack and verify traces hit targets
4. Verify trail VFX activates during swing

---

#### 3.2 B_Item_Weapon_Shield → AB_Item_Weapon_Shield

**Prerequisite:** B_Item_Weapon or B_Weapon reparented

**Components to DELETE:**
- Same as B_Item_Weapon

**After reparenting, verify/set:**
```
- Shield mesh
- Block collision settings
```

**Test:** Equip shield, block attacks, verify damage reduction.

---

### Phase 4: World Actors

#### 4.1 B_Door → AB_Door

**Components to DELETE:**
- DoorFrame StaticMesh (if C++ creates one)
- Timeline (if C++ creates DoorTimeline)

**After reparenting, verify/set:**
```
DoorFrame:
  - Static Mesh: (assign door mesh)

DoorTimeline:
  - Curve: (assign float curve for door movement)

LockInfo:
  - Configure key requirements
```

**Test:** Interact with door, verify it opens/closes with animation.

---

#### 4.2 B_Container → AB_Container

**Components to DELETE:**
- Lid mesh (if duplicated)
- Timeline (if duplicated)

**After reparenting, verify/set:**
```
- Container mesh
- Loot table reference
- Open animation curve
```

**Test:** Interact with container, verify loot spawns.

---

### Phase 5: Components (AC_*)

Components are reparented differently - they're attached to actors.

#### For AC_StatManager, AC_EquipmentManager, etc.

1. Open the **Actor** Blueprint that uses this component
2. Find the component in the Components list
3. In Details panel, change **Component Class** to the C++ version
4. OR delete and re-add with C++ class

**Test:** Verify component functions work (stats update, equipment changes, etc.)

---

## Troubleshooting

### "Class mismatch" Error
- The Blueprint expects old parent class
- Solution: Delete and recreate the Blueprint component

### Duplicate Components After Reparenting
- You didn't delete Blueprint components first
- Solution: Delete duplicates manually, keep C++ versions

### Missing Mesh/Material
- Asset reference not restored
- Solution: Manually assign in Details panel

### Functions Not Working
- Blueprint graph references old parent's variables
- Solution: Update variable references in Blueprint graph

### Movement Feels Different
- Movement component settings reset to C++ defaults
- Solution: Manually set values from the reference table above

---

## Quick Reference: C++ Class Names

| Blueprint | C++ Class |
|-----------|-----------|
| B_BaseCharacter | AB_BaseCharacter |
| B_Soulslike_Character | AB_Soulslike_Character |
| B_Soulslike_Enemy | AB_Soulslike_Enemy |
| B_Item | AB_Item |
| B_Weapon | AB_Weapon |
| B_Item_Weapon | AB_Item_Weapon |
| B_Item_Weapon_Shield | AB_Item_Weapon_Shield |
| B_Door | AB_Door |
| B_Container | AB_Container |
| B_Interactable | AB_Interactable |
| AC_StatManager | UAC_StatManager |
| AC_EquipmentManager | UAC_EquipmentManager |
| AC_InventoryManager | UAC_InventoryManager |
| AC_CombatManager | UAC_CombatManager |
| B_Stat | UB_Stat |
| PDA_Item | UPDA_Item |

---

## Appendix: BlueprintComponentExports Location

All original Blueprint data is preserved in:
```
C:\scripts\BlueDestiny\Saved\BlueprintComponentExports\
```

Use these JSON files to verify exact values if something looks wrong after reparenting.

---

*Last Updated: December 2024*
