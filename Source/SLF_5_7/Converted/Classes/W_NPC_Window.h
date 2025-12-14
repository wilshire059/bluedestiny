#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "W_NPC_Window.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNPCOptionSelected, int32, OptionIndex);

UCLASS()
class SLF_5_7_API UW_NPC_Window : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NPCNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> OptionsContainer;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnNPCOptionSelected OnNPCOptionSelected;

	UFUNCTION(BlueprintCallable, Category = "NPC")
	void SetupNPCWindow(FText NPCName, const TArray<FText>& Options);

	UFUNCTION(BlueprintCallable, Category = "NPC")
	void SelectOption(int32 OptionIndex);

	UFUNCTION(BlueprintCallable, Category = "NPC")
	void CloseWindow();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "NPC")
	void OnSetupOptions(const TArray<FText>& Options);
};
