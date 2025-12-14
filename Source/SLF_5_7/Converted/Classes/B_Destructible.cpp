#include "B_Destructible.h"
#include "Kismet/GameplayStatics.h"

AB_Destructible::AB_Destructible()
{
	PrimaryActorTick.bCanEverTick = false;

    // Create geometry collection as root
    DestructibleMesh = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("DestructibleMesh"));
    RootComponent = DestructibleMesh;
    
    // Disable damage from collision (matches original BP)
    DestructibleMesh->SetEnableDamageFromCollision(false);
    
    // NOTE: CollisionProfilePerLevel must be set in the Blueprint
    // The property is protected and cannot be set from C++ constructor
    // In BP: Set Collision Profile Per Level to [None, Debris, Debris]

    // Create billboard as child of DestructibleMesh (for editor visibility)
    Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
    Billboard->SetupAttachment(DestructibleMesh);
}

void AB_Destructible::BeginPlay()
{
	Super::BeginPlay();
    
    if (DestructibleMesh)
    {
        DestructibleMesh->OnChaosBreakEvent.AddDynamic(this, &AB_Destructible::OnChaosBreakEvent);
        DestructibleMesh->SetNotifyBreaks(true);
    }
}

void AB_Destructible::OnChaosBreakEvent(const FChaosBreakEvent& BreakEvent)
{
    if (bSoundPlayed) return;
    
    if (DestructionSound.ToSoftObjectPath().IsValid())
    {
        USoundBase* LoadedSound = DestructionSound.LoadSynchronous();
        if (LoadedSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, LoadedSound, GetActorLocation());
        }
    }
    
    bSoundPlayed = true;
}
