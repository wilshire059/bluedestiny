#include "Classes/B_DeathTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"
#include "GameFramework/DamageType.h"

AB_DeathTrigger::AB_DeathTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    // Default Config
    RelevantActorTags.Add(FName("Player"));
    DamageAmount = 99999999.0f;

    // Root - Box Component
    DeathTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DeathTriggerBox"));
    RootComponent = DeathTriggerBox;
    DeathTriggerBox->SetBoxExtent(FVector(32.f));
    DeathTriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    DeathTriggerBox->SetHiddenInGame(true);
    
    // Billboard
    Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
    Billboard->SetupAttachment(RootComponent);
    Billboard->SetRelativeScale3D(FVector(0.05f));
    Billboard->bIsScreenSizeScaled = true;
    Billboard->ScreenSize = 0.0025f;
    Billboard->SetHiddenInGame(true);
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconAsset(
        TEXT("/Engine/EditorResources/S_Emitter.S_Emitter"));
    if (IconAsset.Succeeded())
    {
        Billboard->SetSprite(IconAsset.Object);
    }
}

void AB_DeathTrigger::BeginPlay()
{
    Super::BeginPlay();
    
    if (DeathTriggerBox)
    {
        DeathTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AB_DeathTrigger::OnOverlapBegin);
    }
}

void AB_DeathTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    bool bHasTag = false;
    for (const FName& Tag : RelevantActorTags)
    {
        if (OtherActor->ActorHasTag(Tag))
        {
            bHasTag = true;
            break;
        }
    }

    if (bHasTag)
    {
        UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, GetInstigatorController(), this, UDamageType::StaticClass());
    }
}
