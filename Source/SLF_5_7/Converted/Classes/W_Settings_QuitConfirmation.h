#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_Settings_QuitConfirmation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitConfirmed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitCancelled);

UCLASS()
class SLF_5_7_API UW_Settings_QuitConfirmation : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQuitConfirmed OnQuitConfirmed;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQuitCancelled OnQuitCancelled;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleConfirmClicked();

	UFUNCTION()
	void HandleCancelClicked();
};
