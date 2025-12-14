#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "W_Settings_KeyMapping_Category.generated.h"

UCLASS()
class SLF_5_7_API UW_Settings_KeyMapping_Category : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CategoryNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> KeyEntriesContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText CategoryDisplayName;

	UFUNCTION(BlueprintCallable, Category = "KeyMapping")
	void SetupCategory(FText InCategoryName);

protected:
	virtual void NativePreConstruct() override;
};
