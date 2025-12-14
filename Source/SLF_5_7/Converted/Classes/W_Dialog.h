#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "W_Dialog.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogAdvanced);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogChoiceSelected, int32, ChoiceIndex);

UCLASS()
class SLF_5_7_API UW_Dialog : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> SpeakerNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> DialogText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> SpeakerPortrait;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UVerticalBox> ChoicesContainer;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDialogAdvanced OnDialogAdvanced;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDialogChoiceSelected OnDialogChoiceSelected;

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void SetDialog(FText SpeakerName, FText Dialog, UTexture2D* Portrait);

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void SetChoices(const TArray<FText>& Choices);

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void AdvanceDialog();

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void SelectChoice(int32 ChoiceIndex);

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void CloseDialog();
};
