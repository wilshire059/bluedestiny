#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DataAssets/PDA_LoadingScreens.h"
#include "W_LoadingScreen.generated.h"

UCLASS()
class SLF_5_7_API UW_LoadingScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TipText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TObjectPtr<UPDA_LoadingScreens> LoadingScreenAsset;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "LoadingScreen")
	void SetupLoadingScreen();
};
