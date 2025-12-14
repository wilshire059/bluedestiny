#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Enums/E_SettingEntry.h"
#include "W_Settings_Entry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSettingValueChanged, E_SettingEntry, Setting, float, Value);

UCLASS()
class SLF_5_7_API UW_Settings_Entry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> SettingNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> SettingValueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	E_SettingEntry SettingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText SettingName;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	float CurrentValue = 0.0f;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSettingValueChanged OnSettingValueChanged;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetupEntry(E_SettingEntry InSettingType, FText InSettingName, float InitialValue);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void UpdateValue(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void IncrementValue();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void DecrementValue();

protected:
	virtual void NativePreConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float MinValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float MaxValue = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float StepSize = 10.0f;
};
