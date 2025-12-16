#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_CollisionManager.generated.h"

class UPrimitiveComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorTraced, AActor*, Actor, FHitResult, Hit, double, Multiplier);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_CollisionManager : public UActorComponent
{
    GENERATED_BODY()

public:    
    UAC_CollisionManager();

    UPROPERTY(BlueprintAssignable, Category = "Collision")
    FOnActorTraced OnActorTraced;

    UFUNCTION(BlueprintCallable, Category = "Collision")
    void ToggleTrace(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "Collision")
    void Clear();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SubsteppedTrace(float StepSize);

    UPROPERTY()
    TObjectPtr<UPrimitiveComponent> TargetMesh;

    UPROPERTY()
    TArray<AActor*> TracedActors;

    FVector LastLocation;
    
    // Config
    UPROPERTY(EditAnywhere, Category = "Collision")
    float TraceRadius = 20.0f;

    UPROPERTY(EditAnywhere, Category = "Collision")
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

    UPROPERTY(EditAnywhere, Category = "Collision")
    bool bDebug = false;
};
