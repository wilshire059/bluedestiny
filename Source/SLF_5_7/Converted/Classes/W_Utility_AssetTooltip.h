#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "W_Utility_AssetTooltip.generated.h"

UCLASS()
class SLF_5_7_API UW_Utility_AssetTooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> AssetNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> AssetPathText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> PropertiesContainer;

	UFUNCTION(BlueprintCallable, Category = "Utility")
	void SetupTooltip(UObject* Asset);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Utility")
	void OnSetupProperties(UObject* Asset);
};
