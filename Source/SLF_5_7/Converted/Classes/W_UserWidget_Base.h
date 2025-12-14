#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/AC_EquipmentManager.h"
#include "Components/AC_CombatManager.h"
#include "Components/AC_InventoryManager.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_ProgressManager.h"
#include "W_UserWidget_Base.generated.h"

UCLASS()
class SLF_5_7_API UW_UserWidget_Base : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Soulslike|Widget")
    UAC_EquipmentManager* GetEquipmentComponent();

    UFUNCTION(BlueprintCallable, Category = "Soulslike|Widget")
    UAC_CombatManager* GetCombatComponent();

    UFUNCTION(BlueprintCallable, Category = "Soulslike|Widget")
    UAC_InventoryManager* GetInventoryComponent();

    UFUNCTION(BlueprintCallable, Category = "Soulslike|Widget")
    UAC_StatManager* GetStatComponent();

    UFUNCTION(BlueprintCallable, Category = "Soulslike|Widget")
    UAC_ProgressManager* GetProgressComponent();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_EquipmentManager* EquipmentManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_CombatManager* CombatManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_InventoryManager* InventoryManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_StatManager* StatManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_ProgressManager* ProgressManager;

    virtual void NativeConstruct() override;
    
    // Helper to refresh components if valid
    void RefreshComponents();
};
