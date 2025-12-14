#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/VerticalBox.h"
#include "W_Status_StatBlock.generated.h"

UCLASS()
class SLF_5_7_API UW_Status_StatBlock : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> StatContainer;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Status")
	void SetupStats();

	UFUNCTION(BlueprintImplementableEvent, Category = "Status")
	void OnSetupStats();
};
