#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_PatrolPath.generated.h"

class USplineComponent;
class UArrowComponent;

UCLASS()
class SLF_5_7_API AB_PatrolPath : public AActor
{
    GENERATED_BODY()
    
public:    
    AB_PatrolPath();

    /** Advances current point index in a ping-pong manner (0->1->2->1->0) */
    UFUNCTION(BlueprintCallable, Category = "Patrol")
    void SetNextPointIndex();

    /** Gets world location of the current spline point */
    UFUNCTION(BlueprintPure, Category = "Patrol")
    FVector GetWorldPositionForCurrentPoint() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USplineComponent> Route;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UArrowComponent> Arrow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 CurrentPointIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 IncrementBy;
};
