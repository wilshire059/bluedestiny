#pragma once

#include "CoreMinimal.h"
#include "W_Navigable.h"
#include "W_Navigable_InputReader.generated.h"

UCLASS()
class SLF_5_7_API UW_Navigable_InputReader : public UW_Navigable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void HandleNavigationInput(FVector2D Direction);

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void HandleConfirmInput();

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void HandleCancelInput();

protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void OnNavigationInput(FVector2D Direction);

	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void OnConfirmInput();

	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void OnCancelInput();
};
