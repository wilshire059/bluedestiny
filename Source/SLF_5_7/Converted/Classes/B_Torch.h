#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_Torch.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class UPointLightComponent;
class UBillboardComponent;

UCLASS(Blueprintable)
class SLF_5_7_API AB_Torch : public AActor
{
    GENERATED_BODY()
    
public:    
    AB_Torch();

    // Configurable properties (exposed to Blueprint)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Torch")
    float Intensity = 5000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Torch")
    float Attenuation = 1000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Torch")
    FLinearColor Color = FLinearColor::White;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Torch")
    bool bCastShadows = false;

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

    // Components (hierarchy: StaticMesh -> Niagara -> PointLight -> Billboard)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> StaticMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UNiagaraComponent> Niagara;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UPointLightComponent> PointLight;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> Billboard;
};
