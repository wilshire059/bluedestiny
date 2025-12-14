#pragma once

#include "CoreMinimal.h"
#include "B_Interactable.h"
#include "Components/BillboardComponent.h"
#include "Components/PointLightComponent.h"
#include "B_RestingPoint.generated.h"

UCLASS()
class SLF_5_7_API AB_RestingPoint : public AB_Interactable
{
    GENERATED_BODY()

public:
    AB_RestingPoint();

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> SittingZone;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UPointLightComponent> CampfireLight;

    // Variables
    UPROPERTY(BlueprintReadWrite, Category = "Resting")
    TObjectPtr<AActor> SittingActor;

    // Logic
    virtual void OnInteract_Implementation(AActor* InteractingActor) override;

protected:
    virtual void BeginPlay() override;
};
