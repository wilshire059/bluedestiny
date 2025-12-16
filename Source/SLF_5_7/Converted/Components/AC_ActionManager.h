#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/E_Direction.h"
#include "AC_ActionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDirectionChanged, E_Direction, NewDirection);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_ActionManager : public UActorComponent
{
    GENERATED_BODY()

public:    
    UAC_ActionManager();

    UPROPERTY(BlueprintAssignable, Category = "Action")
    FOnDirectionChanged OnDirectionChanged;

    UFUNCTION(BlueprintCallable, Category = "Action")
    void SetMoveDir(FVector2D IAMove);

    // RPCs
    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Action")
    void SRV_SetDirection(E_Direction Direction);

    UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Action")
    void MC_SetDirection(E_Direction Direction);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action")
    E_Direction MovementDirection;

protected:
    virtual void BeginPlay() override;
};
