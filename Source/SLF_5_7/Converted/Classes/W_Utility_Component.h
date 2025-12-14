#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_Utility_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUtilityComponentSelected, UActorComponent*, Component);

UCLASS()
class SLF_5_7_API UW_Utility_Component : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ComponentButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ComponentNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ComponentTypeText;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TWeakObjectPtr<UActorComponent> TrackedComponent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnUtilityComponentSelected OnUtilityComponentSelected;

	UFUNCTION(BlueprintCallable, Category = "Utility")
	void SetupComponent(UActorComponent* Component);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleComponentClicked();
};
