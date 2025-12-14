#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "W_Browser_Action.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrowserActionSelected, int32, ActionIndex);

UCLASS()
class SLF_5_7_API UW_Browser_Action : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ActionButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ActionIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActionNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 ActionIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBrowserActionSelected OnBrowserActionSelected;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupAction(int32 InActionIndex, FText ActionName, UTexture2D* Icon);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleActionClicked();
};
