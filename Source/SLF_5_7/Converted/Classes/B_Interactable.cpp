#include "Classes/B_Interactable.h"
#include "Components/BillboardComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interfaces/BPI_Player.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"

AB_Interactable::AB_Interactable()
{
    PrimaryActorTick.bCanEverTick = false;

    // Defaults
    bCanBeTraced = false;
    bIsActivated = false;

    // Components
    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    RootComponent = DefaultSceneRoot;

    Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent_1"));
    Billboard->SetupAttachment(RootComponent);
    Billboard->SetRelativeScale3D(FVector(0.5f));
    Billboard->SetHiddenInGame(true);
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconEmpty(TEXT("/Engine/EditorResources/EmptyActor.EmptyActor"));
    if (IconEmpty.Succeeded())
    {
        Billboard->SetSprite(IconEmpty.Object);
    }

    InteractableSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interactable SM"));
    InteractableSM->SetupAttachment(RootComponent);
    InteractableSM->SetGenerateOverlapEvents(true);
    InteractableSM->SetCanEverAffectNavigation(true);

    InteractableSK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Interactable SK"));
    InteractableSK->SetupAttachment(RootComponent);
    InteractableSK->SetGenerateOverlapEvents(false);
    InteractableSK->SetCanEverAffectNavigation(false);
}

void AB_Interactable::OnInteract_Implementation(AActor* InteractingActor)
{
    // Default implementation: Print Hello
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Hello"));
    }
}

void AB_Interactable::OnTraced_Implementation(AActor* TracedBy)
{
    if (TracedBy && TracedBy->Implements<UBPI_Player>())
    {
        IBPI_Player::Execute_OnInteractableTraced(TracedBy, this);
    }
}

void AB_Interactable::TryGetItemInfo_Implementation(FSLFItemInfo& ItemInfo)
{
    // Default implementation does nothing or returns default
}

void AB_Interactable::InitializeLoadedStates(bool bInCanBeTraced, bool bInIsActivated)
{
    bCanBeTraced = bInCanBeTraced;
    bIsActivated = bInIsActivated;
}
