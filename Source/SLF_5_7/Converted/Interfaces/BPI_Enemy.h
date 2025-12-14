#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_Enemy.generated.h"

class AB_PatrolPath;

UINTERFACE(MinimalAPI)
class UBPI_Enemy : public UInterface
{
    GENERATED_BODY()
};

class SLF_5_7_API IBPI_Enemy
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
    void UpdateEnemyHealth(double CurrentValue, double MaxValue, double Change);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
    void GetExecutionMoveToTransform(FVector& MoveToLocation, FRotator& Rotation);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
    void StopRotateTowardsTarget();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
    void RotateTowardsTarget(double Duration);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
    void PickAndSpawnLoot();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
    AB_PatrolPath* GetPatrolPath();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
    void DisplayDeathVfx(FVector AttractorPosition);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
    void ToggleHealthbarVisual(bool bVisible);
};
