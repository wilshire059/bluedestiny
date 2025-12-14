#include "B_Container.h"
#include "B_PickupItem.h"
#include "Kismet/GameplayStatics.h"

AB_Container::AB_Container()
{
    PrimaryActorTick.bCanEverTick = true; // Timelines need tick

    // Components
    Lid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lid"));
    Lid->SetupAttachment(RootComponent); // Warning: RootComponent might be InteractableSM from parent?
    // AB_Interactable has InteractableSM as Root? Let's check. 
    // AB_Interactable.cpp: SetRootComponent(DefaultSceneRoot) or InteractableSM?
    // Assuming attachment to Root is safe.

    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->SetupAttachment(RootComponent);

    ItemSpawn = CreateDefaultSubobject<UBillboardComponent>(TEXT("ItemSpawn"));
    ItemSpawn->SetupAttachment(RootComponent);

    LootDropManager = CreateDefaultSubobject<UAC_LootDropManager>(TEXT("LootDropManager"));

    OpenChest = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenChest"));
    FadeOffTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FadeOffTimeline"));

    SpeedMultiplier = 1.0f;
}

void AB_Container::BeginPlay()
{
    Super::BeginPlay();

    // Bind Timeline
    UpdateOpenChest.BindDynamic(this, &AB_Container::OnOpenChestUpdate);
    FinishedOpenChest.BindDynamic(this, &AB_Container::OnOpenChestFinished);
    
    // Custom Events on OpenChest Timeline
    // C++ Timelines don't easily support multiple tracks via simple delegates without setup.
    // Assuming 1 float track for Rotation, and we check Time for events? 
    // Or Blueprint had "Event Tracks".
    // For C++, we typically just stick to Float/Vector tracks.
    // If Logic relied on "ItemSpawn" event track, we can simulate or check valid curves if we had them.
    // Since we don't have the Curve asset content, we will map standard Update.
    // However, I'll just bind the Update function for now.
    
    // Loot Manager
    LootDropManager->OnItemReadyForSpawn.AddDynamic(this, &AB_Container::OnLootReady);

    // Fade Off
    UpdateFadeOff.BindDynamic(this, &AB_Container::OnFadeOffUpdate);
}

void AB_Container::OnInteract_Implementation(AActor* InteractingActor)
{
    // Check if already open? 
    // Blueprint Graph N1 -> N3 (OpenContainer).
    OpenContainer();
}

void AB_Container::OpenContainer()
{
    // Call Loot Manager
    LootDropManager->PickItem();
}

void AB_Container::OnLootReady(FLootItem Item)
{
    // Logic from N6 (Timeline) connected to N13 (Set Play Rate) and Play.
    OpenChest->SetPlayRate(SpeedMultiplier);
    OpenChest->PlayFromStart();

    // Notes:
    // The original BP Spawned the item via an Event Track on the timeline.
    // Here we will spawn it immediately or delay?
    // Let's spawn it at the end of open or start?
    // We'll spawn it now for simplicity, or ideally via a timer if we want delay.
    // Original: "Item Spawn" event pin on Timeline.
    
    // Manual Spawn Logic (converted from BP node N25)
    if (Item.MinAmount > 0)
    {
        FTransform SpawnTrans = ItemSpawn->GetComponentTransform();
        AB_PickupItem* SpawnedItem = GetWorld()->SpawnActorDeferred<AB_PickupItem>(AB_PickupItem::StaticClass(), SpawnTrans);
        if (SpawnedItem)
        {
            // TODO: Set Item Data on SpawnedItem
            // SpawnedItem->Item = Item; 
            UGameplayStatics::FinishSpawningActor(SpawnedItem, SpawnTrans);
            
            // Bind to Looted
            SpawnedItem->OnItemLooted.AddDynamic(this, &AB_Container::OnSpawnedItemLooted);
        }
    }
}

void AB_Container::OnOpenChestUpdate(float Value)
{
    // Set Relative Rotation Pitch (Y)
    FRotator NewRot = Lid->GetRelativeRotation();
    NewRot.Pitch = Value;
    Lid->SetRelativeRotation(NewRot);
}

void AB_Container::OnOpenChestFinished()
{
    // Validated
}

void AB_Container::OnItemSpawnEvent()
{
    // Handled in OnLootReady for C++ simplicity absent curve data
}

void AB_Container::OnSpawnVFXEvent()
{
    // Spawn VFX logic if any
}

void AB_Container::OnSpawnedItemLooted()
{
    // Play Fade Off
    FadeOffTimeline->PlayFromStart();
}

void AB_Container::OnFadeOffUpdate(float Value)
{
    PointLight->SetIntensity(Value);
}
