#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "W_Settings_ControlEntry.generated.h"

UCLASS()
class SLF_5_7_API UW_Settings_ControlEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActionNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> KeyIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> KeyText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FKey BoundKey;

	UFUNCTION(BlueprintCallable, Category = "Controls")
	void SetupEntry(FText InActionName, FKey InKey);

protected:
	virtual void NativePreConstruct() override;
};
