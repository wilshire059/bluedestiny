#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "W_Debug_ComponentTooltip.generated.h"

UCLASS()
class SLF_5_7_API UW_Debug_ComponentTooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ComponentNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ComponentClassText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> PropertiesContainer;

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void SetupTooltip(UActorComponent* Component);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Debug")
	void OnSetupProperties(UActorComponent* Component);
};
