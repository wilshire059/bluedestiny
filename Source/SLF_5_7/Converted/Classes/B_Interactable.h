#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/BPI_Interactable.h"
#include "B_Interactable.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UBillboardComponent;

UCLASS()
class SLF_5_7_API AB_Interactable : public AActor, public IBPI_Interactable
{
    GENERATED_BODY()
    
public:    
    AB_Interactable();

    // Interface Implementation
    virtual void OnInteract_Implementation(AActor* InteractingActor) override;
    virtual void OnTraced_Implementation(AActor* TracedBy) override;
    virtual void TryGetItemInfo_Implementation(FSLFItemInfo& ItemInfo) override;

    UFUNCTION(BlueprintCallable, Category = "Interactable")
    void InitializeLoadedStates(bool bInCanBeTraced, bool bInIsActivated);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USceneComponent> DefaultSceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> Billboard;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> InteractableSM;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USkeletalMeshComponent> InteractableSK;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bCanBeTraced;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bIsActivated;
};
