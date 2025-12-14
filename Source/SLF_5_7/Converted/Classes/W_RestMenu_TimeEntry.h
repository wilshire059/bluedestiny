#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_RestMenu_TimeEntry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeEntrySelected, int32, TimeIndex);

UCLASS()
class SLF_5_7_API UW_RestMenu_TimeEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> TimeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 TimeIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText TimeLabel;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTimeEntrySelected OnTimeEntrySelected;

	UFUNCTION(BlueprintCallable, Category = "TimeEntry")
	void SetupTimeEntry(int32 InTimeIndex, FText InTimeLabel);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleButtonClicked();
};
