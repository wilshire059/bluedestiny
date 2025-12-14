#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "B_LocationActor.generated.h"

class UBillboardComponent;
class UArrowComponent;

UCLASS()
class SLF_5_7_API AB_LocationActor : public AActor
{
    GENERATED_BODY()
    
public:    
    AB_LocationActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayTagContainer LocationTag;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USceneComponent> DefaultSceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> BillboardEmpty; // BillboardComponent_1

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> BillboardNavLink; // Billboard

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UArrowComponent> Arrow;
};
