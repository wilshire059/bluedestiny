#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/E_ActionWeaponSlot.h"
#include "GameplayTagContainer.h"
#include "B_Action.generated.h"

class UPDA_WeaponAnimset;
class UAC_EquipmentManager;
class UAC_StatManager;
class UPDA_Action;

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Action : public UObject
{
	GENERATED_BODY()

public:
    UB_Action();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    UPDA_Action* Action;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    AActor* OwnerActor;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
    void ExecuteAction();

    UFUNCTION(BlueprintCallable, Category = "Action")
    UPDA_WeaponAnimset* GetWeaponAnimset(E_ActionWeaponSlot WeaponSlot);

    UFUNCTION(BlueprintCallable, Category = "Action")
    bool CheckStatRequirement(E_ActionWeaponSlot StaminaMultiplierWeaponSlot);

protected:
    UFUNCTION(BlueprintCallable, Category = "Action")
    UAnimInstance* GetOwnerAnimInstance();

    // Helper functions inferred
    UAC_EquipmentManager* GetEquipmentManager() const;
    UAC_StatManager* GetStatManager() const;
};
