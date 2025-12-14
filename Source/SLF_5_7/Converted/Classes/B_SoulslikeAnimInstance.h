#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/AC_EquipmentManager.h"
#include "Components/AC_CombatManager.h"
#include "B_SoulslikeAnimInstance.generated.h"

UCLASS()
class SLF_5_7_API UB_SoulslikeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Soulslike|Animation")
    UAC_EquipmentManager* GetEquipmentComponent();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Soulslike|Animation")
    UAC_CombatManager* GetCombatComponent();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_EquipmentManager* EquipmentManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_CombatManager* CombatManager;

    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
