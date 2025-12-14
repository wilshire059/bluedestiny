#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_Debug_ComponentSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDebugComponentSelected, UActorComponent*, Component);

UCLASS()
class SLF_5_7_API UW_Debug_ComponentSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ComponentNameText;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TWeakObjectPtr<UActorComponent> TrackedComponent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDebugComponentSelected OnDebugComponentSelected;

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void SetupSlot(UActorComponent* Component);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleSlotClicked();
};
