#pragma once

#include "CoreMinimal.h"
#include "B_Item.h"
#include "Components/PointLightComponent.h"
#include "Components/TimelineComponent.h"
#include "B_Item_Lantern.generated.h"

UCLASS()
class SLF_5_7_API AB_Item_Lantern : public AB_Item
{
    GENERATED_BODY()

public:
    AB_Item_Lantern();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> LanternMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UPointLightComponent> AreaLight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UPointLightComponent> RimLight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern")
    float LanternLife = 100.0f;

    // Simulate Timeline for Fadeoff
    void StartFadeoff();
    
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    bool bIsFading;
    float FadeAlpha;
};
