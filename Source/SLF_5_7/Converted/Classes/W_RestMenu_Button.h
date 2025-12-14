#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_RestMenu_Button.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRestButtonClicked, int32, ButtonIndex);

UCLASS()
class SLF_5_7_API UW_RestMenu_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> RestButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 ButtonIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ButtonLabel;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnRestButtonClicked OnRestButtonClicked;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleButtonClicked();
};
