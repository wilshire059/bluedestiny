# Blueprint to C++ Migration Tracker

## Overview
This tracker monitors the progress of migrating Blueprints from bp_only to C++ classes in BlueDestiny.

**Migration Process:** See `.agent/workflows/blueprint-migration.md` for detailed steps.

---

## Status Legend
- `[ ]` Not started
- `[/]` In progress  
- `[x]` Complete and verified
- `[!]` Has issues / needs attention

---

## Completed Migrations

### Classes
- [x] `B_Destructible` - Chaos physics actor with destruction
  - C++ class: `AB_Destructible`
  - Notes: Required Blueprint-side configuration of `CollisionProfilePerLevel`
  - Verified: Yes

---

## In Progress

### Classes  
- [x] `B_LocationActor` - Level marker with tags
  - C++ class: `AB_LocationActor`
  - Status: **Complete - Pure C++**
  - Notes: Pure C++ with ConstructorHelpers. `LocationTag` exposed as config.

- [x] `B_Torch` - Simple torch actor with fire VFX and point light
  - C++ class: `AB_Torch`  
  - Status: **Complete - Pure C++**
  - Notes: Self-contained with ConstructorHelpers loading SM_Torch and NS_Firex assets

---

## Pending Migrations

- [x] `B_DeathTrigger`
  - C++ class: `AB_DeathTrigger`
  - Status: **Complete - Pure C++**
  - Notes: Pure C++ with OnOverlap logic and damage application.
- [x] `B_PatrolPath`
  - C++ class: `AB_PatrolPath`
  - Status: **Complete - Pure C++**
  - Notes: Implemented Ping-Pong spline logic. Verified build.

### Interactables
- [x] `B_Interactable` (base class)
  - C++ class: `AB_Interactable`
  - Status: **Complete - Pure C++**
  - Notes: Implemented along with `FSLFItemInfo`, `BPI_Interactable`, `BPI_Player`.
- [x] `B_BossDoor`
  - C++ class: `AB_BossDoor`
  - Status: **Complete - Pure C++**
  - Notes: Inherits from `AB_Door`.
- [ ] `B_Container`
- [x] `B_Door`
  - C++ class: `AB_Door`
  - Status: **Complete - Pure C++**
  - Notes: Added `DoorTimeline`, `LockInfo`, `MoveTo`, `OpeningDirection`.
- [ ] `B_Ladder`
- [ ] `B_RestingPoint`

### Characters (Complex - do later)
- [ ] `B_BaseCharacter`
- [ ] `B_Soulslike_Character`
- [ ] `B_Soulslike_Enemy`
- [ ] `B_Soulslike_Boss`
- [ ] `B_Soulslike_NPC`

### Items
- [ ] `B_Item`
- [ ] `B_PickupItem`
- [ ] `B_Item_Weapon`

### Projectiles
- [ ] `B_BaseProjectile`
- [ ] `B_Projectile_Boss_Fireball`
- [ ] `B_Projectile_ThrowingKnife`

### Stats/Buffs
- [ ] `B_Stat`
- [ ] `B_Buff`
- [ ] `B_StatusEffect`

---

## Components (AC_*)
- [ ] `AC_ActionManager`
- [ ] `AC_CombatManager`
- [ ] `AC_EquipmentManager`
- [ ] `AC_InventoryManager`
- [ ] (... more to add)

---

## Notes
- Protected properties like `CollisionProfilePerLevel` cannot be set in C++ constructors
- Always pre-test Blueprint functionality before migration
- Post-migration testing required before marking complete

---

## Data Sources
- NodeToCode JSON: `Plugins/NodeToCode/ExportedBlueprints/`
- Component Exports: `Saved/BlueprintComponentExports/`
- 405 component exports + 438 NodeToCode exports available
