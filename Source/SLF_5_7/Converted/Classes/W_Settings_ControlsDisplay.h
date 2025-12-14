#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "W_Settings_ControlsDisplay.generated.h"

UCLASS()
class SLF_5_7_API UW_Settings_ControlsDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> ControlsContainer;

	UFUNCTION(BlueprintCallable, Category = "Controls")
	void SetupControlsDisplay();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Controls")
	void OnSetupControls();
};
