#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "W_CreditEntry.generated.h"

UCLASS()
class SLF_5_7_API UW_CreditEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> RoleText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText Role;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText Name;

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void SetupEntry(FText InRole, FText InName);

protected:
	virtual void NativePreConstruct() override;
};
