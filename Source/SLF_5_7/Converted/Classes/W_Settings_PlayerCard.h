#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "W_Settings_PlayerCard.generated.h"

UCLASS()
class SLF_5_7_API UW_Settings_PlayerCard : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UImage> PlayerAvatar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> PlayTimeText;

	UFUNCTION(BlueprintCallable, Category = "PlayerCard")
	void SetupPlayerCard(FText PlayerName, float PlayTimeSeconds);

protected:
	virtual void NativeConstruct() override;
};
