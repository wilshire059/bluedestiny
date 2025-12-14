#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Materials/MaterialInterface.h"
#include "W_BigScreenMessage.generated.h"

UCLASS()
class SLF_5_7_API UW_BigScreenMessage : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> Message;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> GradientImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Backdrop;

	UFUNCTION(BlueprintCallable, Category = "BigScreenMessage")
	void ShowMessage(FText InMessage, UMaterialInterface* GradientMaterial, bool bHasBackdrop, float AnimationRateScale = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "BigScreenMessage")
	void HideMessage();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float DefaultAnimationRate = 1.0f;
};
