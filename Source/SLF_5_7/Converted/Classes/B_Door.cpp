#include "B_Door.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AB_Door::AB_Door()
{
    // DoorFrame setup
    DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
    DoorFrame->SetupAttachment(RootComponent);

    // Initial attachment of InteractableSM (from parent) is likely to Root, but here we might need adjustment
    // In Blueprint, DoorFrame is sibling to InteractableSM? Let's check JSON.
    // JSON: DoorFrame attached to DefaultSceneRoot. InteractableSM is also to DefaultSceneRoot.
    // Base class AB_Interactable has InteractableSM.

    // DoorTimeline
    DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));

    // MoveTo
    MoveTo = CreateDefaultSubobject<UBillboardComponent>(TEXT("MoveTo"));
    MoveTo->SetupAttachment(RootComponent);

    // OpeningDirection
    OpeningDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("OpeningDirection"));
    OpeningDirection->SetupAttachment(RootComponent);
}

void AB_Door::BeginPlay()
{
    Super::BeginPlay();

    if (DoorCurve)
    {
        UpdateTimelineFloat.BindDynamic(this, &AB_Door::OnTimelineUpdated);
        DoorTimeline->AddInterpFloat(DoorCurve, UpdateTimelineFloat, TEXT("Alpha"));
    }
}

void AB_Door::OnInteract_Implementation(AActor* InteractingActor)
{
    if (!LockInfo.bIsLocked)
    {
        // Unlock logic or pure open logic?
        // Blueprint: Checks LockInfo. Only if locked do we check IsLocked?
        // Actually the logic is: Get LockInfo -> Check "IsLocked?".
        // If True (Locked) -> ValidateUnlockRequirements.
        // If False (Unlocked) -> OpenDoor (Timeline).
        DoorTimeline->Play(); 
    }
    else
    {
        if (ValidateUnlockRequirements(InteractingActor))
        {
            // Unlock success
            LockInfo.bIsLocked = false; 
            DoorTimeline->Play();
        }
    }
}

bool AB_Door::ValidateUnlockRequirements(AActor* PlayerActor)
{
    if (!PlayerActor) return false;

    // Get Inventory Component from Player
    // In Blueprint it uses "GetInventoryComponent" from BFL_Helper.
    // Since we don't have BFL_Helper yet, we see if we can find component by class.
    UAC_InventoryManager* Inventory = PlayerActor->FindComponentByClass<UAC_InventoryManager>();
    
    if (!Inventory) return false;

    // Iterate through RequiredItemAmount (Map: GameplayTag -> Int)
    bool bHasAll = true;
    for (const TPair<FGameplayTag, int32>& Pair : LockInfo.RequiredItemAmount)
    {
         FGameplayTag RequiredTag = Pair.Key;
         int32 RequiredAmount = Pair.Value;

         int32 CurrentAmount = Inventory->GetAmountOfItemByTag(RequiredTag);
         if (CurrentAmount < RequiredAmount)
         {
             bHasAll = false;
             break;
         }
    }

    if (!bHasAll) return false;

    // If success, consume items (Optional? Blueprint calls "Unlock").
    // Blueprint logic for UnlockBossDoor suggests checking; consuming might happen elsewhere or simple interaction.
    // For B_Door base, usually items are keys (conserved) or specific costs. 
    // Assuming keys are NOT consumed unless specified. B_BossDoor logic had "GetAmount" checks.
    
    return true;
}

void AB_Door::OnTimelineUpdated(float Value)
{
    if (InteractableSM)
    {
        FRotator NewRot = FMath::Lerp(FRotator::ZeroRotator, FRotator(0, 90, 0), Value); // Simplified 90 deg open
        InteractableSM->SetRelativeRotation(NewRot);
    }
}

void AB_Door::OpenDoor(float Value)
{
    // Not used directly, mostly loop back from Timeline
}
