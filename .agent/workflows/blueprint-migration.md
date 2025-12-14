---
description: Blueprint to C++ Migration - Reparenting Workflow
---

# Blueprint to C++ Migration Workflow

## Overview
**Pure C++ approach** - Create self-contained C++ classes with hardcoded asset references.
No Blueprint wrappers needed. Place the C++ class directly in levels.

## Prerequisites
- BlueDestiny project workspace at `c:\scripts\BlueDestiny`
- NodeToCode exports in `Plugins/NodeToCode/ExportedBlueprints/*.json`
- Component exports in `Saved/BlueprintComponentExports/*.json`

## Migration Tracker
Local tracker: `c:\scripts\BlueDestiny\migration_tracker.md`

---

## Step-by-Step Migration Process

### Phase 1: Data Gathering
// turbo
1. **Review NodeToCode JSON** at `Plugins/NodeToCode/ExportedBlueprints/<BlueprintName>.json`
   - Check `graphs` for EventGraph logic
   - Check `functions` for custom functions
   - Check `classDefaults` for default values and asset paths

// turbo  
2. **Run Complete Property Dumper** in Unreal Editor:
   - Modify `complete_property_dumper.py` with Blueprint path
   - Execute Python script
   - Output: `Saved/BlueprintComponentExports/<BlueprintName>_COMPLETE.json`

### Phase 2: C++ Implementation
3. **Create header file** at `Source/SLF_5_7/Converted/Classes/<ClassName>.h`
   - Match component structure from export
   - Use `TObjectPtr<>` for component pointers

4. **Create cpp file** at `Source/SLF_5_7/Converted/Classes/<ClassName>.cpp`
   - Create components in constructor
   - **Load assets using ConstructorHelpers**:
   ```cpp
   static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
       TEXT("/Game/Path/To/Asset"));
   if (MeshAsset.Succeeded())
   {
       StaticMesh->SetStaticMesh(MeshAsset.Object);
   }
   ```
   - Set all properties using setter methods
   - Document any properties that don't have setters

5. **Update Build.cs** if new modules needed

// turbo
6. **Build the project** with editor closed:
```powershell
& 'C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat' SLF_5_7Editor Development Win64 -project='C:\scripts\BlueDestiny\SLF_5_7.uproject' -WaitMutex
```

If build fails due to cache, add `-NoUBA` flag.

### Phase 3: Testing
7. **Open Unreal Editor**
8. **Place the C++ class directly** in level (Content Browser → C++ Classes)
9. **Verify functionality** matches original Blueprint
10. **Delete the original Blueprint** (optional - keeps repo clean)

---

## Asset Loading Patterns

### Static Mesh
```cpp
static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
    TEXT("/Game/SoulslikeFramework/Meshes/SM/Torch/SM_Torch"));
if (MeshAsset.Succeeded()) StaticMesh->SetStaticMesh(MeshAsset.Object);
```

### Niagara System
```cpp
static ConstructorHelpers::FObjectFinder<UNiagaraSystem> VFXAsset(
    TEXT("/Game/SoulslikeFramework/VFX/Systems/NS_Firex"));
if (VFXAsset.Succeeded()) Niagara->SetAsset(VFXAsset.Object);
```

### Sound
```cpp
static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(
    TEXT("/Game/Path/To/Sound"));
if (SoundAsset.Succeeded()) AudioComponent->SetSound(SoundAsset.Object);
```

### Material
```cpp
static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatAsset(
    TEXT("/Game/Path/To/Material"));
if (MatAsset.Succeeded()) MeshComp->SetMaterial(0, MatAsset.Object);
```

---

## Key Notes

### What Goes in C++
- Component hierarchy and attachment
- All transforms and properties
- **Asset references via ConstructorHelpers**
- Event handlers and logic

### Private Members (can't set in C++)
- `bAbsoluteScale` on SceneComponent
- Some advanced light/collision settings
- Document these but they're usually defaults anyway

### Performance
- Pure C++ is the most performant approach
- ConstructorHelpers load once at class load time
- No Blueprint VM overhead

---

## Scripts Reference
| Script | Purpose |
|--------|---------|
| `complete_property_dumper.py` | Dumps ALL component properties |
| `component_exporter.py` | Batch exports component hierarchy |
