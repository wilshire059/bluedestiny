#include "B_Item.h"
#include "Kismet/KismetSystemLibrary.h"

AB_Item::AB_Item()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;

    // DefaultSceneRoot is created automatically by Actor if no components, but usually good to be explicit if referenced. 
    // Blueprint "Components" list was empty in Export, implying just default root.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
}

void AB_Item::BeginPlay()
{
    Super::BeginPlay();
}

void AB_Item::OnUse_Implementation()
{
    // Node: Print String
    UKismetSystemLibrary::PrintString(this, TEXT("Item has been used."), true, true, FLinearColor(0.0f, 0.66f, 1.0f, 1.0f), 2.0f);

    // Node: Destroy Actor
    Destroy();
}

void AB_Item::OnWeaponEquip_Implementation(bool bRightHand)
{
    // No logic in Blueprint Graph
}

void AB_Item::OnWeaponUnequip_Implementation()
{
    // No logic in Blueprint Graph
}
