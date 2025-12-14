#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "W_TimePass.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimePassComplete);

UCLASS()
class SLF_5_7_API UW_TimePass : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UImage> SunMoonIcon;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTimePassComplete OnTimePassComplete;

	UFUNCTION(BlueprintCallable, Category = "TimePass")
	void StartTimePass(float TargetTime, float Duration);

	UFUNCTION(BlueprintCallable, Category = "TimePass")
	void UpdateTimeDisplay(float CurrentTime);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsTransitioning = false;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	float TransitionProgress = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	float TransitionDuration = 2.0f;
};
