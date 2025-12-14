#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "W_Browser_Animset_OwnerEntry.generated.h"

UCLASS()
class SLF_5_7_API UW_Browser_Animset_OwnerEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> OwnerNameText;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetOwnerName(FText OwnerName);
};
