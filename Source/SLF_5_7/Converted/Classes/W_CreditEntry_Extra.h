#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Structs/FCreditsExtra.h"
#include "W_CreditEntry_Extra.generated.h"

UCLASS()
class SLF_5_7_API UW_CreditEntry_Extra : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ExtraText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ExtraContent;

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void SetupExtraEntry(const FCreditsExtra& ExtraData);

protected:
	virtual void NativePreConstruct() override;
};
