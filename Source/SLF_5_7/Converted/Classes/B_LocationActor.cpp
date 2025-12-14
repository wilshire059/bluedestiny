#include "Classes/B_LocationActor.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"

AB_LocationActor::AB_LocationActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // ==========================================================================
    // DefaultSceneRoot (Root)
    // ==========================================================================
    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    RootComponent = DefaultSceneRoot;
    
    // ==========================================================================
    // BillboardEmpty (was BillboardComponent_1)
    // Sprite: /Engine/EditorResources/EmptyActor.EmptyActor
    // Scale: 0.5
    // ==========================================================================
    BillboardEmpty = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardEmpty"));
    BillboardEmpty->SetupAttachment(RootComponent);
    BillboardEmpty->SetRelativeScale3D(FVector(0.5f));
    BillboardEmpty->bIsScreenSizeScaled = true;
    BillboardEmpty->ScreenSize = 0.0025f;
    BillboardEmpty->SetHiddenInGame(true);
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconEmpty(
        TEXT("/Engine/EditorResources/EmptyActor.EmptyActor"));
    if (IconEmpty.Succeeded())
    {
        BillboardEmpty->SetSprite(IconEmpty.Object);
    }
    
    // ==========================================================================
    // BillboardNavLink (was Billboard)
    // Sprite: /Engine/EditorResources/AI/S_NavLink.S_NavLink
    // Location: (0, 0, 32.5), Scale: 0.605
    // ==========================================================================
    BillboardNavLink = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardNavLink"));
    BillboardNavLink->SetupAttachment(RootComponent);
    BillboardNavLink->SetRelativeLocation(FVector(0.f, 0.f, 32.5f));
    BillboardNavLink->SetRelativeScale3D(FVector(0.605f));
    BillboardNavLink->bIsScreenSizeScaled = true;
    BillboardNavLink->ScreenSize = 0.0025f;
    BillboardNavLink->SetHiddenInGame(true);
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconNavLink(
        TEXT("/Engine/EditorResources/AI/S_NavLink.S_NavLink"));
    if (IconNavLink.Succeeded())
    {
        BillboardNavLink->SetSprite(IconNavLink.Object);
    }
    
    // ==========================================================================
    // Arrow
    // Location: (0, 0, 80.0)
    // ==========================================================================
    Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    Arrow->SetupAttachment(RootComponent);
    Arrow->SetRelativeLocation(FVector(0.f, 0.f, 80.0f));
    Arrow->SetHiddenInGame(true);
}
