#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_GenericButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGenericButtonClicked, int32, ButtonID);

UCLASS()
class SLF_5_7_API UW_GenericButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> GenericButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 ButtonID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ButtonLabel;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGenericButtonClicked OnGenericButtonClicked;

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetButtonLabel(FText NewLabel);

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetButtonEnabled(bool bEnabled);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleButtonClicked();
};
