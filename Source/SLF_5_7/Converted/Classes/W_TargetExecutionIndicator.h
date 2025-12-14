#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Image.h"
#include "Interfaces/BPI_ExecutionIndicator.h"
#include "W_TargetExecutionIndicator.generated.h"

UCLASS()
class SLF_5_7_API UW_TargetExecutionIndicator : public UW_UserWidget_Base, public IBPI_ExecutionIndicator
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ExecutionIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TObjectPtr<UTexture2D> ExecuteAvailableIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TObjectPtr<UTexture2D> ExecuteUnavailableIcon;

	// BPI_ExecutionIndicator Interface
	virtual void ShowIndicator_Implementation(AActor* TargetActor) override;
	virtual void HideIndicator_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Execution")
	void SetCanExecute(bool bCanExecute);
};
