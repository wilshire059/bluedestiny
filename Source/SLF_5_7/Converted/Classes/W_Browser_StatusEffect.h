#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "W_Browser_StatusEffect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrowserStatusEffectSelected, int32, EffectIndex);

UCLASS()
class SLF_5_7_API UW_Browser_StatusEffect : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> EffectButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> EffectIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> EffectNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 EffectIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBrowserStatusEffectSelected OnBrowserStatusEffectSelected;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupEffect(int32 InIndex, FText EffectName, UTexture2D* Icon);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleEffectClicked();
};
