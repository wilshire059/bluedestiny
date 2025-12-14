#pragma once

#include "CoreMinimal.h"
#include "Classes/B_BaseCharacter.h"
#include "Interfaces/BPI_Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Classes/B_Interactable.h"
#include "B_Soulslike_Character.generated.h"

UCLASS()
class SLF_5_7_API AB_Soulslike_Character : public AB_BaseCharacter, public IBPI_Player
{
	GENERATED_BODY()

public:
	AB_Soulslike_Character();

protected:
	virtual void BeginPlay() override;

public:	
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UChildActorComponent* ChaosForceField;

    // Interface BPI_Player
    virtual void OnInteractableTraced_Implementation(AB_Interactable* Interactable) override;
    virtual void OnRest_Implementation(AActor* Campfire) override;
    virtual void OnLootItem_Implementation(AActor* Item) override;
    virtual void TriggerChaosField_Implementation(bool bEnable) override;
};
