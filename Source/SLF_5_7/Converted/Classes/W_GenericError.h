#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_GenericError.generated.h"

UCLASS()
class SLF_5_7_API UW_GenericError : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TitleText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> OkButton;

	UFUNCTION(BlueprintCallable, Category = "Error")
	void ShowError(FText Title, FText Message);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleOkClicked();
};
