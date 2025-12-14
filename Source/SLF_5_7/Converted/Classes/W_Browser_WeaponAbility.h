#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "W_Browser_WeaponAbility.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrowserWeaponAbilitySelected, int32, AbilityIndex);

UCLASS()
class SLF_5_7_API UW_Browser_WeaponAbility : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> AbilityButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> AbilityIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> AbilityNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 AbilityIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBrowserWeaponAbilitySelected OnBrowserWeaponAbilitySelected;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupAbility(int32 InIndex, FText AbilityName, UTexture2D* Icon);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleAbilityClicked();
};
