#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Image.h"
#include "W_TargetLock.generated.h"

UCLASS()
class SLF_5_7_API UW_TargetLock : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> TargetLockIcon;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TWeakObjectPtr<AActor> LockedTarget;

	UFUNCTION(BlueprintCallable, Category = "TargetLock")
	void SetLockedTarget(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "TargetLock")
	void ClearLockedTarget();

	UFUNCTION(BlueprintCallable, Category = "TargetLock")
	void UpdatePosition();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
