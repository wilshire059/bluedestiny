#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "W_CreditEntry_Sub_NameEntry.generated.h"

UCLASS()
class SLF_5_7_API UW_CreditEntry_Sub_NameEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText Name;

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void SetName(FText InName);

protected:
	virtual void NativePreConstruct() override;
};
