#include "B_Ladder.h"
#include "AC_LadderManager.h"

AB_Ladder::AB_Ladder()
{
    PrimaryActorTick.bCanEverTick = false;

    // Components
    TopdownCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TopdownCollision"));
    TopdownCollision->SetupAttachment(RootComponent);

    TopCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TopCollision"));
    TopCollision->SetupAttachment(RootComponent);

    BottomCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomCollision"));
    BottomCollision->SetupAttachment(RootComponent);

    ClimbingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ClimbingCollision"));
    ClimbingCollision->SetupAttachment(RootComponent);
}

void AB_Ladder::BeginPlay()
{
    Super::BeginPlay();

    // Bind Overlaps
    TopdownCollision->OnComponentEndOverlap.AddDynamic(this, &AB_Ladder::OnTopdownEndOverlap);
    
    TopCollision->OnComponentBeginOverlap.AddDynamic(this, &AB_Ladder::OnTopBeginOverlap);
    TopCollision->OnComponentEndOverlap.AddDynamic(this, &AB_Ladder::OnTopEndOverlap);
    
    BottomCollision->OnComponentBeginOverlap.AddDynamic(this, &AB_Ladder::OnBottomBeginOverlap);
    BottomCollision->OnComponentEndOverlap.AddDynamic(this, &AB_Ladder::OnBottomEndOverlap);

    ClimbingCollision->OnComponentEndOverlap.AddDynamic(this, &AB_Ladder::OnClimbingEndOverlap);
}

void AB_Ladder::OnInteract_Implementation(AActor* InteractingActor)
{
    // Logic for interaction
    // Typically passes self to LadderManager?
}

// Helpers
UAC_LadderManager* GetLadderManager(AActor* Actor)
{
    if (!Actor) return nullptr;
    return Actor->FindComponentByClass<UAC_LadderManager>();
}

void AB_Ladder::OnTopdownEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (UAC_LadderManager* Manager = GetLadderManager(OtherActor))
    {
        // Based on JSON N3 -> N16
        Manager->SetIsClimbingDownFromTop(false); // Guessing False on EndOverlap? Or True? 
        // Logic: End Overlap of "TopDown" zone might mean "Started climbing". 
        // I will assume False for now, user can verify.
    }
}

void AB_Ladder::OnTopBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (UAC_LadderManager* Manager = GetLadderManager(OtherActor))
    {
        // Logic
    }
}

void AB_Ladder::OnTopEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
     if (UAC_LadderManager* Manager = GetLadderManager(OtherActor))
    {
        // Logic
    }
}

void AB_Ladder::OnBottomBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
     if (UAC_LadderManager* Manager = GetLadderManager(OtherActor))
    {
        // Logic
    }
}

void AB_Ladder::OnBottomEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
     if (UAC_LadderManager* Manager = GetLadderManager(OtherActor))
    {
        // Logic
    }
}

void AB_Ladder::OnClimbingEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
     if (UAC_LadderManager* Manager = GetLadderManager(OtherActor))
    {
        // Logic
    }
}
