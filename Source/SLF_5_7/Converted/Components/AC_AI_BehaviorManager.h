#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/E_AI_States.h"
#include "Classes/B_PatrolPath.h"
#include "Structs/FAiPatrolPathInfo.h"
#include "StructUtils/InstancedStruct.h"
#include "AC_AI_BehaviorManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, E_AI_States, NewState, E_AI_States, OldState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_AI_BehaviorManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_AI_BehaviorManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    E_AI_States CurrentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TObjectPtr<AB_PatrolPath> PatrolPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    double MaxChaseDistanceThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    double MinChaseDistanceThreshold;

    UPROPERTY(BlueprintAssignable, Category = "AI")
    FOnStateChanged OnStateChanged;

    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetState(E_AI_States NewState, const FInstancedStruct& Data);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetKeyValue(FName KeyName, const FInstancedStruct& Data); // Simplified for interface match

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
