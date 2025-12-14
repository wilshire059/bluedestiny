#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "W_CreditEntry_Sub.generated.h"

UCLASS()
class SLF_5_7_API UW_CreditEntry_Sub : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CategoryText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> NamesContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText Category;

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void SetupSubEntry(FText InCategory, const TArray<FText>& Names);

protected:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Credits")
	void OnSetupNames(const TArray<FText>& Names);
};
