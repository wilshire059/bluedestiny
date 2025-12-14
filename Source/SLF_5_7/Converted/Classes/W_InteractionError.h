#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "W_InteractionError.generated.h"

UCLASS()
class SLF_5_7_API UW_InteractionError : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ErrorText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float DisplayDuration = 2.0f;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ShowInteractionError(FText ErrorMessage);

protected:
	FTimerHandle HideTimerHandle;

	UFUNCTION()
	void HideError();
};
