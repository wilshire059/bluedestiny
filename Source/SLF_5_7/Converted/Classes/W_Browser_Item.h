#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "W_Browser_Item.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrowserItemSelected, int32, ItemIndex);

UCLASS()
class SLF_5_7_API UW_Browser_Item : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 ItemIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBrowserItemSelected OnBrowserItemSelected;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupItem(int32 InItemIndex, FText ItemName, UTexture2D* Icon);

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetSelected(bool bSelected);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleItemClicked();
};
