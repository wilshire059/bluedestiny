#include "AC_CollisionManager.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UAC_CollisionManager::UAC_CollisionManager()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = false; // Default off, enabled by ToggleTrace
}

void UAC_CollisionManager::BeginPlay()
{
    Super::BeginPlay();

    // Auto-detect mesh if possible
    AActor* Owner = GetOwner();
    if (Owner)
    {
        TargetMesh = Cast<UPrimitiveComponent>(Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
        if (!TargetMesh)
        {
            TargetMesh = Cast<UPrimitiveComponent>(Owner->GetComponentByClass(UStaticMeshComponent::StaticClass()));
        }
    }
}

void UAC_CollisionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    SubsteppedTrace(DeltaTime);
}

void UAC_CollisionManager::ToggleTrace(bool bEnable)
{
    SetComponentTickEnabled(bEnable);
    if (bEnable)
    {
        Clear();
        if (TargetMesh)
        {
            LastLocation = TargetMesh->GetComponentLocation();
        }
    }
}

void UAC_CollisionManager::Clear()
{
    TracedActors.Empty();
}

void UAC_CollisionManager::SubsteppedTrace(float StepSize)
{
    if (!TargetMesh) return;

    FVector CurrentLocation = TargetMesh->GetComponentLocation(); // Simple Center Trace for now, or Socket based? 
    // JSON implies simplistic trace or maybe multiple sockets. 
    // For general weapon, usually traces start/end of blade.
    // Given the JSON "SubsteppedTrace" input, it likely does a sweep.
    
    // Improvement: Trace along the item length if sockets are known, but simplified for generic manager:
    // Sweep from LastLocation to CurrentLocation.
    
    TArray<AActor*> IgnoreActors;
    IgnoreActors.Add(GetOwner());
    IgnoreActors.Append(TracedActors);

    FHitResult HitResult;
    
    // Ensure ObjectTypes has values if empty
    if (ObjectTypes.Num() == 0)
    {
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));
    }

    bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
        this,
        LastLocation,
        CurrentLocation,
        TraceRadius,
        ObjectTypes,
        false,
        IgnoreActors,
        bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
        HitResult,
        true
    );

    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor && !TracedActors.Contains(HitActor))
        {
            TracedActors.Add(HitActor);
            OnActorTraced.Broadcast(HitActor, HitResult, 1.0f);
        }
    }

    LastLocation = CurrentLocation;
}
