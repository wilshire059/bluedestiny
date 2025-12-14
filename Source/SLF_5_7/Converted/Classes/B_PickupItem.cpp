#include "B_PickupItem.h"
#include "Interfaces/BPI_Player.h"
#include "Kismet/KismetSystemLibrary.h"

AB_PickupItem::AB_PickupItem()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AB_PickupItem::BeginPlay()
{
    Super::BeginPlay();

    // Line Trace to Ground
    FVector Start = GetActorLocation();
    FVector End = Start + (GetActorUpVector() * -300.0f); // Down 300 units

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    FHitResult HitResult;
    bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(
        this,
        Start,
        End,
        ObjectTypes,
        false,
        ActorsToIgnore,
        EDrawDebugTrace::None,
        HitResult,
        true
    );

    if (bHit)
    {
        SetActorLocation(HitResult.Location);
    }
}

void AB_PickupItem::OnInteract_Implementation(AActor* InteractingActor)
{
    if (InteractingActor && InteractingActor->Implements<UBPI_Player>())
    {
        IBPI_Player::Execute_OnLootItem(InteractingActor, this);
    }
}
