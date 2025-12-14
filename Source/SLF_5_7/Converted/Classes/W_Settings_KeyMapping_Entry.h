#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_Settings_KeyMapping_Entry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeyMappingEntryClicked, FName, ActionName);

UCLASS()
class SLF_5_7_API UW_Settings_KeyMapping_Entry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActionNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> KeyButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> KeyText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ActionDisplayName;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	FKey CurrentKey;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnKeyMappingEntryClicked OnKeyMappingEntryClicked;

	UFUNCTION(BlueprintCallable, Category = "KeyMapping")
	void SetupEntry(FName InActionName, FText InDisplayName, FKey InCurrentKey);

	UFUNCTION(BlueprintCallable, Category = "KeyMapping")
	void UpdateKey(FKey NewKey);

	UFUNCTION(BlueprintCallable, Category = "KeyMapping")
	void SetWaitingForInput(bool bWaiting);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleButtonClicked();
};
