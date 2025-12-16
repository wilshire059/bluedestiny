#pragma once

#include "CoreMinimal.h"
#include "B_Door.h"
#include "B_BossDoor.generated.h"

class UAnimMontage;

UCLASS()
class SLF_5_7_API AB_BossDoor : public AB_Door
{
    GENERATED_BODY()

public:
    AB_BossDoor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossDoor")
    TObjectPtr<UAnimMontage> InteractMontage_RH;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossDoor")
    TObjectPtr<UAnimMontage> InteractMontage_LH;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossDoor")
    FText InteractionText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossDoor")
    FText InteractableDisplayName;

    // Components
    // Assuming DeathCurrencySpawnPoint is a SceneComponent
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USceneComponent> DeathCurrencySpawnPoint;

    // Functions
    UFUNCTION(BlueprintCallable, Category = "BossDoor")
    void UnlockBossDoor();

    UFUNCTION(BlueprintCallable, Category = "BossDoor")
    USceneComponent* GetDeathCurrencySpawnPoint() const;

    virtual void OnInteract_Implementation(AActor* InteractingActor) override;

protected:
    virtual void BeginPlay() override;
};
