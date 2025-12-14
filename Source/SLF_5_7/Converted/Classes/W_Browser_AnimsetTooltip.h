#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "W_Browser_AnimsetTooltip.generated.h"

UCLASS()
class SLF_5_7_API UW_Browser_AnimsetTooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> AnimsetNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> OwnersContainer;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupTooltip(FText AnimsetName, const TArray<FText>& Owners);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Browser")
	void OnSetupOwners(const TArray<FText>& Owners);
};
