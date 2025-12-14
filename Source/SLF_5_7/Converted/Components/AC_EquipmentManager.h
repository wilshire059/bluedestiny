#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "DataAssets/PDA_Item.h"
#include "AC_EquipmentManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentChanged, FGameplayTag, Slot, const UPDA_Item*, Item);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_EquipmentManager : public UActorComponent
{
    GENERATED_BODY()

public:    
    UAC_EquipmentManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    TMap<FGameplayTag, UPDA_Item*> CurrentEquipment;

    UPROPERTY(BlueprintAssignable, Category = "Equipment")
    FOnEquipmentChanged OnEquipmentChanged;

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UnequipWeaponAtSlot(FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UnequipTalismanAtSlot(FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UnequipToolAtSlot(FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    FGameplayTag GetActiveWeaponSlot(bool bRightHand);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void AreBothWeaponSlotsActive(); 

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void GetItemAtSlot(FGameplayTag SlotTag);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void SpawnAndEquipWeapon(FGameplayTag SlotTag, UPDA_Item* Item);

    // Helpers
    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void EquipItem(FGameplayTag SlotTag, UPDA_Item* Item);
};
