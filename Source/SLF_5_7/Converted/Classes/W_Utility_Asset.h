#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "W_Utility_Asset.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUtilityAssetSelected, UObject*, Asset);

UCLASS()
class SLF_5_7_API UW_Utility_Asset : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> AssetButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> AssetIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> AssetNameText;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TWeakObjectPtr<UObject> TrackedAsset;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnUtilityAssetSelected OnUtilityAssetSelected;

	UFUNCTION(BlueprintCallable, Category = "Utility")
	void SetupAsset(UObject* Asset, FText AssetName, UTexture2D* Icon);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleAssetClicked();
};
