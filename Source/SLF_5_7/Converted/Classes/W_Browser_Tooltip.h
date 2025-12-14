#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "W_Browser_Tooltip.generated.h"

UCLASS()
class SLF_5_7_API UW_Browser_Tooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TitleText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> DescriptionText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UImage> PreviewImage;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupTooltip(FText Title, FText Description, UTexture2D* Preview = nullptr);
};
