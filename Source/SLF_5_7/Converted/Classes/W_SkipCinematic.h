#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "W_SkipCinematic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkipCinematic);

UCLASS()
class SLF_5_7_API UW_SkipCinematic : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> SkipProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText SkipMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float HoldDuration = 2.0f;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSkipCinematic OnSkipCinematic;

protected:
	virtual void NativePreConstruct() override;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	float CurrentHoldTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsHolding = false;

public:
	UFUNCTION(BlueprintCallable, Category = "SkipCinematic")
	void StartHolding();

	UFUNCTION(BlueprintCallable, Category = "SkipCinematic")
	void StopHolding();

	UFUNCTION(BlueprintCallable, Category = "SkipCinematic")
	void UpdateProgress(float DeltaTime);
};
