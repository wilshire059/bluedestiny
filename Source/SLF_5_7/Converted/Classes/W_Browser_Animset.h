#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_Browser_Animset.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrowserAnimsetSelected, int32, AnimsetIndex);

UCLASS()
class SLF_5_7_API UW_Browser_Animset : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> AnimsetButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> AnimsetNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 AnimsetIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBrowserAnimsetSelected OnBrowserAnimsetSelected;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupAnimset(int32 InIndex, FText AnimsetName);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleAnimsetClicked();
};
