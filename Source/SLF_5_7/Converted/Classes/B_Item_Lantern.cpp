#include "B_Item_Lantern.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

AB_Item_Lantern::AB_Item_Lantern()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create static mesh component as root
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMesh;

    // Create area light component
    AreaLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("AreaLight"));
    AreaLight->SetupAttachment(RootComponent);
    AreaLight->SetIntensity(2500.0f);
    AreaLight->SetAttenuationRadius(1000.0f);

    // Create rim light component
    RimLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("RimLight"));
    RimLight->SetupAttachment(RootComponent);
    RimLight->SetIntensity(1000.0f);
    RimLight->SetAttenuationRadius(500.0f);

    // Initialize properties
    LanternLife = 60.0f; // Default from JSON: 60 seconds
    bIsFadingOff = false;
    FadeoffAlpha = 0.0f;
    FadeoffDuration = 2.0f; // Estimated from timeline in Blueprint

    // Load the lantern off material
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> LanternOffMatFinder(
        TEXT("/Game/SoulslikeFramework/Meshes/SM/Lantern/Textures/MI_Lantern_Off.MI_Lantern_Off")
    );
    if (LanternOffMatFinder.Succeeded())
    {
        LanternOffMaterial = LanternOffMatFinder.Object;
    }
}

void AB_Item_Lantern::BeginPlay()
{
    Super::BeginPlay();
}

void AB_Item_Lantern::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Handle fadeoff timeline simulation
    if (bIsFadingOff)
    {
        FadeoffAlpha += DeltaTime / FadeoffDuration;

        if (FadeoffAlpha >= 1.0f)
        {
            FadeoffAlpha = 1.0f;
            bIsFadingOff = false;

            // Timeline finished - set lights to 0 and set off material
            if (RimLight)
            {
                RimLight->SetIntensity(0.0f);
            }
            if (AreaLight)
            {
                AreaLight->SetIntensity(0.0f);
            }
            if (StaticMesh && LanternOffMaterial)
            {
                StaticMesh->SetMaterial(0, LanternOffMaterial);
            }

            // Set timer to destroy the lantern after 5 seconds
            GetWorld()->GetTimerManager().SetTimer(
                DestroyTimer,
                this,
                &AB_Item_Lantern::DestroyLantern,
                5.0f,
                false
            );
        }
        else
        {
            // Update light intensities during fadeoff
            // Lerp from initial values to 0
            // RimLight: 0 -> 1000
            // AreaLight: 0 -> 2500
            float RimIntensity = UKismetMathLibrary::Lerp(0.0, 1000.0, FadeoffAlpha);
            float AreaIntensity = UKismetMathLibrary::Lerp(0.0, 2500.0, FadeoffAlpha);

            if (RimLight)
            {
                RimLight->SetIntensity(RimIntensity);
            }
            if (AreaLight)
            {
                AreaLight->SetIntensity(AreaIntensity);
            }
        }
    }
}

void AB_Item_Lantern::OnUse_Implementation()
{
    Super::OnUse_Implementation();

    // Print debug message
    UKismetSystemLibrary::PrintString(
        this,
        TEXT("Lantern used"),
        true,  // PrintToScreen
        true,  // PrintToLog
        FLinearColor(0.0f, 0.66f, 1.0f, 1.0f),  // TextColor
        2.0f   // Duration
    );

    // Get instigator (player)
    APawn* InstigatorPawn = GetInstigator();
    if (!InstigatorPawn)
    {
        return;
    }

    // Get the player's skeletal mesh component
    USkeletalMeshComponent* PlayerMesh = InstigatorPawn->FindComponentByClass<USkeletalMeshComponent>();
    if (!PlayerMesh)
    {
        return;
    }

    // Attach to the lantern socket on the player
    K2_AttachToComponent(
        PlayerMesh,
        FName(TEXT("LanternSocket")),
        EAttachmentRule::SnapToTarget,  // Location
        EAttachmentRule::SnapToTarget,  // Rotation
        EAttachmentRule::SnapToTarget,  // Scale
        true  // WeldSimulatedBodies
    );

    // Set timer for lantern lifetime
    FTimerDelegate LanternFinishedDelegate;
    LanternFinishedDelegate.BindUFunction(this, FName("LanternFinished"));

    GetWorld()->GetTimerManager().SetTimer(
        LanternLifetimeTimer,
        LanternFinishedDelegate,
        LanternLife,
        false
    );
}

void AB_Item_Lantern::StartFadeoff()
{
    bIsFadingOff = true;
    FadeoffAlpha = 0.0f;
}

void AB_Item_Lantern::LanternFinished()
{
    // Start the fadeoff timeline
    StartFadeoff();

    // Enable physics on the static mesh
    if (StaticMesh)
    {
        StaticMesh->SetSimulatePhysics(true);
    }
}

void AB_Item_Lantern::DestroyLantern()
{
    // Destroy the actor
    K2_DestroyActor();
}
