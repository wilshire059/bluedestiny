#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "W_DebugWindow.generated.h"

UCLASS()
class SLF_5_7_API UW_DebugWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TitleText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> ContentContainer;

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void SetTitle(FText Title);

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void AddDebugLine(FText Line);

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void ClearContent();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Debug")
	void OnAddDebugLine(const FText& Line);
};
