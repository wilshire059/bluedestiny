#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/E_LadderClimbState.h"
#include "AC_LadderManager.generated.h"

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_LadderManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_LadderManager();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder")
    bool bIsClimbing;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder")
    E_LadderClimbState ClimbAnimState;

    UFUNCTION(BlueprintCallable, Category = "Ladder")
    void ToggleClimbing(bool bEnable, const FVector& StartLocation, const FRotator& StartRotation);

    UFUNCTION(BlueprintCallable, Category = "Ladder")
    void SetClimbState(E_LadderClimbState NewState);

    // Called by Player Input
    UFUNCTION(BlueprintCallable, Category = "Ladder")
    void HandleMoveInput(const FVector2D& InputValue);

    UFUNCTION(BlueprintCallable, Category = "Ladder")
    void SetIsClimbingDownFromTop(bool bIsDown);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
