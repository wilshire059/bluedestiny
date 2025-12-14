#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "W_Debug_HUD.generated.h"

UCLASS()
class SLF_5_7_API UW_Debug_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> DebugInfoContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> FPSText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> LocationText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> StateText;

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void UpdateDebugInfo();

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void ToggleDebugHUD();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
