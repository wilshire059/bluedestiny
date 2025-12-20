#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/E_AI_States.h"
#include "Enums/E_AI_StateHandle.h"
#include "Enums/E_StrafeMethod.h"
#include "Classes/B_PatrolPath.h"
#include "Structs/FAiPatrolPathInfo.h"
#include "Structs/FStrafeMethodInfo.h"
#include "StructUtils/InstancedStruct.h"
#include "AC_AI_BehaviorManager.generated.h"

class UBlackboardComponent;
class UBehaviorTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, E_AI_States, NewState, E_AI_States, OldState);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_AI_BehaviorManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UAC_AI_BehaviorManager();

    // ============================================================
    // PROPERTIES
    // ============================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|State")
    E_AI_States CurrentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|State")
    E_AI_States PreviousState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Behavior")
    TObjectPtr<UBehaviorTree> Behavior;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Patrol")
    TObjectPtr<AB_PatrolPath> PatrolPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Target")
    TObjectPtr<AActor> CurrentTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Distance Thresholds")
    double MaxChaseDistanceThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Distance Thresholds")
    double AttackDistanceThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Distance Thresholds")
    double StrafeDistanceThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Distance Thresholds")
    double SpeedAdjustDistanceThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Distance Thresholds")
    double MinimumStrafePointDistanceThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Strafe")
    TArray<FStrafeMethodInfo> StrafeMethods;

    // ============================================================
    // DELEGATES
    // ============================================================

    UPROPERTY(BlueprintAssignable, Category = "AI")
    FOnStateChanged OnStateChanged;

    // ============================================================
    // CORE FUNCTIONS
    // ============================================================

    UFUNCTION(BlueprintCallable, Category = "AI")
    void InitializeBehavior();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetState(E_AI_States NewState, const FInstancedStruct& Data);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetKeyValue(FName KeyName, const FInstancedStruct& Data);

    UFUNCTION(BlueprintPure, Category = "AI")
    UBlackboardComponent* GetBlackboard() const;

    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetPatrolPath(AB_PatrolPath* NewPatrolPath);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetTarget(AActor* NewTarget);

    UFUNCTION(BlueprintPure, Category = "AI")
    E_AI_States GetState(E_AI_StateHandle Handle) const;

    UFUNCTION(BlueprintPure, Category = "AI")
    AActor* GetTarget() const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
