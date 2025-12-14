#include "B_Item_Lantern.h"

AB_Item_Lantern::AB_Item_Lantern()
{
    PrimaryActorTick.bCanEverTick = true;

    LanternMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LanternMesh"));
    RootComponent = LanternMesh;

    AreaLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("AreaLight"));
    AreaLight->SetupAttachment(RootComponent);
    AreaLight->SetIntensity(3000.0f);
    AreaLight->SetAttenuationRadius(1000.0f);

    RimLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("RimLight"));
    RimLight->SetupAttachment(RootComponent);
    RimLight->SetIntensity(500.0f);
    RimLight->SetAttenuationRadius(200.0f);

    bIsFading = false;
    FadeAlpha = 1.0f;
}

void AB_Item_Lantern::BeginPlay()
{
    Super::BeginPlay();
    // Logic: If lantern is "used" or auto-on?
    // JSON implied "Event LanternFinished" from Timeline.
}

void AB_Item_Lantern::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bIsFading)
    {
        FadeAlpha -= DeltaSeconds * 0.5f; // 2 seconds fade
        if (FadeAlpha <= 0.0f)
        {
            FadeAlpha = 0.0f;
            bIsFading = false;
            // Finished
            AreaLight->SetIntensity(0.0f);
            RimLight->SetIntensity(0.0f);
            Destroy(); // Or disable
        }
        else
        {
            AreaLight->SetIntensity(3000.0f * FadeAlpha);
            RimLight->SetIntensity(500.0f * FadeAlpha);
        }
    }
}

void AB_Item_Lantern::StartFadeoff()
{
    bIsFading = true;
    FadeAlpha = 1.0f;
}
