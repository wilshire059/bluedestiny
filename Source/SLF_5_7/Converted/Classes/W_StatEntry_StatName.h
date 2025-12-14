#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Components/TextBlock.h"
#include "W_StatEntry_StatName.generated.h"

UCLASS()
class SLF_5_7_API UW_StatEntry_StatName : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> StatNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FGameplayTag StatTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText StatDisplayName;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetupStatName(FGameplayTag InStatTag, FText InDisplayName);

protected:
	virtual void NativePreConstruct() override;
};
