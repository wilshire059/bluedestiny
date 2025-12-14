#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/InputKeySelector.h"
#include "W_Settings_InputKeySelector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKeySelected, FName, ActionName, FKey, NewKey);

UCLASS()
class SLF_5_7_API UW_Settings_InputKeySelector : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActionNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInputKeySelector> KeySelector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ActionDisplayName;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnKeySelected OnKeySelected;

	UFUNCTION(BlueprintCallable, Category = "KeyBinding")
	void SetupKeySelector(FName InActionName, FText InDisplayName, FKey CurrentKey);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleKeySelected(FInputChord SelectedKey);
};
