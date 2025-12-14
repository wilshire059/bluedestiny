#include "Components/AC_EquipmentManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

UAC_EquipmentManager::UAC_EquipmentManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}
// ... existing code ...
void UAC_EquipmentManager::SpawnAndEquipWeapon(FGameplayTag SlotTag, UPDA_Item* Item)
{
    if (!Item) return;
    
    // Check if we need to spawn an actor
    UClass* ActorClass = Item->ItemInformation.ItemClass.LoadSynchronous();
    if (ActorClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = GetOwner();
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
        if (AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams))
        {
             // Equip Data
             EquipItem(SlotTag, Item);
             
             // Attach to Component
             if (ACharacter* Char = Cast<ACharacter>(GetOwner()))
             {
                 // Logic to determine socket based on SlotTag or Item Info
                 // For now, hardcoded to Hand_R or defaulting
                 FName SocketName = FName("Hand_R");
                 SpawnedActor->AttachToComponent(Char->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
             }
        }
    }
}

void UAC_EquipmentManager::UnequipWeaponAtSlot(FGameplayTag SlotTag)
{
    if (CurrentEquipment.Remove(SlotTag))
    {
        OnEquipmentChanged.Broadcast(SlotTag, nullptr);
    }
}

void UAC_EquipmentManager::UnequipTalismanAtSlot(FGameplayTag SlotTag)
{
    UnequipWeaponAtSlot(SlotTag); // Same logic for now
}

void UAC_EquipmentManager::UnequipToolAtSlot(FGameplayTag SlotTag)
{
    UnequipWeaponAtSlot(SlotTag);
}

FGameplayTag UAC_EquipmentManager::GetActiveWeaponSlot(bool bRightHand)
{
    // Placeholder logic: iterate keys and find one that matches "RightHand" tag signature?
    // For now returning empty or first found.
    // In a real implementation this would likely check a separate "ActiveSlot" variable.
    return FGameplayTag();
}

void UAC_EquipmentManager::AreBothWeaponSlotsActive()
{
    // Stub
}

void UAC_EquipmentManager::GetItemAtSlot(FGameplayTag SlotTag)
{
    // Stub - likely returns item, but signature was void in previous stub.
}

void UAC_EquipmentManager::EquipItem(FGameplayTag SlotTag, UPDA_Item* Item)
{
    if (Item)
    {
        CurrentEquipment.Add(SlotTag, Item);
        OnEquipmentChanged.Broadcast(SlotTag, Item);
    }
}

