#include "B_RestingPoint.h"
#include "Interfaces/BPI_Player.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

AB_RestingPoint::AB_RestingPoint()
{
    PrimaryActorTick.bCanEverTick = false;

    SittingZone = CreateDefaultSubobject<UBillboardComponent>(TEXT("SittingZone"));
    SittingZone->SetupAttachment(RootComponent);

    CampfireLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("CampfireLight"));
    CampfireLight->SetupAttachment(RootComponent);
}

void AB_RestingPoint::BeginPlay()
{
    Super::BeginPlay();
}

void AB_RestingPoint::OnInteract_Implementation(AActor* InteractingActor)
{
    if (!InteractingActor) return;

    SittingActor = InteractingActor;

    // Call OnRest on Player
    if (InteractingActor->Implements<UBPI_Player>())
    {
        IBPI_Player::Execute_OnRest(InteractingActor, this);
    }

    // Delay 1.0s then Move/Rotate
    FTimerHandle UnusedHandle;
    FTimerDelegate TimerDel;
    TimerDel.BindLambda([this]()
    {
        if (IsValid(this) && IsValid(SittingActor) && IsValid(SittingZone))
        {
            // Move Actor
            SittingActor->SetActorLocation(SittingZone->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);

            // Rotate Actor to look at InteractableSM
            // Note: InteractableSM is in base class. Assuming functionality.
            if (IsValid(InteractableSM)) // Check if base class has this public/protected
            {
                FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(SittingZone->GetComponentLocation(), InteractableSM->GetComponentLocation());
                // Only Yaw usually? JSON didn't split, but typically sitting implies flat rotation.
                // Keeping full rotation as per Blueprint implicit logic unless split pin used.
                // Blueprint N6 SetActorRotation.
                SittingActor->SetActorRotation(LookRot, ETeleportType::TeleportPhysics);
            }
        }
    });

    GetWorld()->GetTimerManager().SetTimer(UnusedHandle, TimerDel, 1.0f, false);
}
