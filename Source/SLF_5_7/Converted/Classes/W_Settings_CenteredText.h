#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "W_Settings_CenteredText.generated.h"

UCLASS()
class SLF_5_7_API UW_Settings_CenteredText : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CenteredText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText DisplayText;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetText(FText NewText);

protected:
	virtual void NativePreConstruct() override;
};
