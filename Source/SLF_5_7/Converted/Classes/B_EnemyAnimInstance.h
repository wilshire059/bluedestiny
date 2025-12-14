#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Classes/B_Soulslike_Enemy.h"
#include "B_EnemyAnimInstance.generated.h"

UCLASS()
class SLF_5_7_API UB_EnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Soulslike|Animation")
    AB_Soulslike_Enemy* GetEnemyOwner();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
    AB_Soulslike_Enemy* EnemyOwner;

    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
