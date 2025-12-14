#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "W_Settings_KeyMapping.generated.h"

UCLASS()
class SLF_5_7_API UW_Settings_KeyMapping : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> KeyMappingsContainer;

	UFUNCTION(BlueprintCallable, Category = "KeyMapping")
	void SetupKeyMappings();

	UFUNCTION(BlueprintCallable, Category = "KeyMapping")
	void ResetToDefaults();

	UFUNCTION(BlueprintCallable, Category = "KeyMapping")
	void ApplyKeyMappings();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "KeyMapping")
	void OnSetupKeyMappings();
};
