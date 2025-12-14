#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Structs/FCreditsEntry.h"
#include "W_Credits.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCreditsFinished);

UCLASS()
class SLF_5_7_API UW_Credits : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> CreditsContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float ScrollSpeed = 50.0f;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCreditsFinished OnCreditsFinished;

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void StartCredits();

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void SkipCredits();

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void SetupCredits(const TArray<FCreditsEntry>& Entries);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsScrolling = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "Credits")
	void OnSetupCredits(const TArray<FCreditsEntry>& Entries);
};
