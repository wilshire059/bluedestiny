#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_Error.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnErrorDismissed);

UCLASS()
class SLF_5_7_API UW_Error : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ErrorText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> DismissButton;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnErrorDismissed OnErrorDismissed;

	UFUNCTION(BlueprintCallable, Category = "Error")
	void ShowError(FText ErrorMessage);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleDismissClicked();
};
