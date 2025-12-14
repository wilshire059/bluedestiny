#include "B_BossDoor.h"

AB_BossDoor::AB_BossDoor()
{
    DeathCurrencySpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("DeathCurrencySpawnPoint"));
    DeathCurrencySpawnPoint->SetupAttachment(RootComponent);

    InteractionText = FText::FromString("Go through");
    InteractableDisplayName = FText::FromString("Fog Wall");
}

void AB_BossDoor::BeginPlay()
{
    Super::BeginPlay();
}

void AB_BossDoor::OnInteract_Implementation(AActor* InteractingActor)
{
    // Override logic for BossDoor interaction
    // In Blueprint it calls Parent OnInteract usually, or handles specific unlocking.
    // If Unlocked, it might trigger Travel or Animation.
    
    UnlockBossDoor();
    
    Super::OnInteract_Implementation(InteractingActor);
}

void AB_BossDoor::UnlockBossDoor()
{
    // Logic to consume items and unlock
    if (LockInfo.bIsLocked)
    {
        // Custom boss door specific unlocking might happen here
        // For now relying on Parent ValidateUnlockRequirements via Super::OnInteract
    }
}

USceneComponent* AB_BossDoor::GetDeathCurrencySpawnPoint() const
{
    return DeathCurrencySpawnPoint;
}
