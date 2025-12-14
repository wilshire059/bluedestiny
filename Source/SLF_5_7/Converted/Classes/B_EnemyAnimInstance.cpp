#include "B_EnemyAnimInstance.h"

void UB_EnemyAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    EnemyOwner = Cast<AB_Soulslike_Enemy>(GetOwningActor());
}

void UB_EnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (!EnemyOwner)
    {
        EnemyOwner = Cast<AB_Soulslike_Enemy>(GetOwningActor());
    }
}

AB_Soulslike_Enemy* UB_EnemyAnimInstance::GetEnemyOwner()
{
    return EnemyOwner;
}
