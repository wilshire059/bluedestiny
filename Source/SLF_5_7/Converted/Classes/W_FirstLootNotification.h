#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "W_FirstLootNotification.generated.h"

UCLASS()
class SLF_5_7_API UW_FirstLootNotification : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> FirstTimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float DisplayDuration = 5.0f;

	UFUNCTION(BlueprintCallable, Category = "Loot")
	void ShowFirstLootNotification(UTexture2D* Icon, FText ItemName);

protected:
	FTimerHandle HideTimerHandle;

	UFUNCTION()
	void HideNotification();
};
