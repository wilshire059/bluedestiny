#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BPI_Controller.h"
#include "PC_SoulslikeFramework.generated.h"

class UInputMappingContext;
class UAC_InventoryManager;
class UAC_StatManager;
class UAC_ProgressManager;

UCLASS()
class SLF_5_7_API APC_SoulslikeFramework : public APlayerController, public IBPI_Controller
{
	GENERATED_BODY()

public:
	APC_SoulslikeFramework();

	// BPI_Controller Interface Implementations
	virtual UAC_InventoryManager* GetInventoryComponent_Implementation() override;
	virtual void StartRespawn_Implementation(double FadeDelay) override;
	virtual void SendBigScreenMessage_Implementation(const FText& Text, UMaterialInterface* GradientMaterial, bool bBackdrop, double PlayRate) override;
	virtual void SwitchInputContext_Implementation(const TArray<UInputMappingContext*>& ContextsToEnable, const TArray<UInputMappingContext*>& ContextsToDisable) override;
	virtual UAC_ProgressManager* GetProgressManager_Implementation() override;
	virtual APlayerController* GetSoulslikeController_Implementation() override;
	virtual APawn* GetPawnFromController_Implementation() override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAC_InventoryManager> InventoryManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAC_StatManager> StatManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAC_ProgressManager> ProgressManager;
};
