#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "W_CharacterSelection_StatEntry.generated.h"

UCLASS()
class SLF_5_7_API UW_CharacterSelection_StatEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> StatNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> StatValueText;

	UFUNCTION(BlueprintCallable, Category = "CharacterSelection")
	void SetupStatEntry(FText StatName, int32 StatValue);
};
