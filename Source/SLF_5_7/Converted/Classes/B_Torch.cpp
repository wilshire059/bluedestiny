#include "Classes/B_Torch.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/BillboardComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Engine/StaticMesh.h"

AB_Torch::AB_Torch()
{
    PrimaryActorTick.bCanEverTick = false;

    // ==========================================================================
    // StaticMesh Component (Root)
    // ==========================================================================
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMesh;
    
    StaticMesh->SetMobility(EComponentMobility::Static);
    StaticMesh->SetGenerateOverlapEvents(true);
    StaticMesh->SetCanEverAffectNavigation(true);
    StaticMesh->SetCastShadow(true);
    StaticMesh->SetHiddenInGame(false);
    StaticMesh->SetVisibility(true);
    
    // Load Static Mesh asset
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/SoulslikeFramework/Meshes/SM/Torch/SM_Torch"));
    if (MeshAsset.Succeeded())
    {
        StaticMesh->SetStaticMesh(MeshAsset.Object);
    }
    
    // ==========================================================================
    // Niagara Component (attached to StaticMesh)
    // ==========================================================================
    Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
    Niagara->SetupAttachment(StaticMesh);
    Niagara->SetRelativeLocation(FVector(0.f, 6.55f, 36.31f));
    
    Niagara->SetMobility(EComponentMobility::Static);
    Niagara->SetAutoActivate(true);
    Niagara->SetGenerateOverlapEvents(false);
    Niagara->SetCanEverAffectNavigation(false);
    Niagara->SetCastShadow(false);
    Niagara->SetHiddenInGame(false);
    Niagara->SetVisibility(true);
    
    // Load Niagara System asset
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(
        TEXT("/Game/SoulslikeFramework/VFX/Systems/NS_Firex"));
    if (NiagaraAsset.Succeeded())
    {
        Niagara->SetAsset(NiagaraAsset.Object);
    }
    
    // ==========================================================================
    // PointLight Component (attached to Niagara)
    // ==========================================================================
    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->SetupAttachment(Niagara);
    PointLight->SetRelativeLocation(FVector(0.f, 47.35f, 48.0f));
    
    PointLight->SetMobility(EComponentMobility::Stationary);
    PointLight->SetIntensity(5000.0f);
    PointLight->SetAttenuationRadius(1000.0f);
    PointLight->SetLightColor(FLinearColor::White);
    PointLight->SetCastShadows(false);
    PointLight->SetHiddenInGame(false);
    PointLight->SetVisibility(true);
    PointLight->SetCanEverAffectNavigation(false);
    
    // ==========================================================================
    // Billboard Component (attached to PointLight - editor only)
    // ==========================================================================
    Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
    Billboard->SetupAttachment(PointLight);
    Billboard->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
    Billboard->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
    
    Billboard->SetMobility(EComponentMobility::Movable);
    Billboard->SetHiddenInGame(true);
    Billboard->SetVisibility(true);
    Billboard->SetGenerateOverlapEvents(false);
    Billboard->SetCanEverAffectNavigation(false);
    Billboard->SetCastShadow(false);
}

void AB_Torch::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    
    // Apply configurable properties to point light (allows per-instance overrides)
    if (PointLight)
    {
        PointLight->SetIntensity(Intensity);
        PointLight->SetAttenuationRadius(Attenuation);
        PointLight->SetLightColor(Color);
        PointLight->SetCastShadows(bCastShadows);
    }
}
