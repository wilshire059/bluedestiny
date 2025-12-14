#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "W_LevelEntry.generated.h"

UCLASS()
class SLF_5_7_API UW_LevelEntry : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelValueText;

	UFUNCTION(BlueprintCallable, Category = "Level")
	void SetupLevelEntry(int32 Level);
};
