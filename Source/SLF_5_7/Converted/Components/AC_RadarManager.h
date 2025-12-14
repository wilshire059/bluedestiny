#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_RadarManager.generated.h"

class UAC_RadarElement;
class UUserWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_RadarManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UAC_RadarManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Radar")
	TObjectPtr<UUserWidget> RadarWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Radar")
	TObjectPtr<APawn> TrackedPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Radar")
	TArray<TObjectPtr<UAC_RadarElement>> RegisteredElements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	float RadarRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	float RadarScale;

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void Initialize(UUserWidget* InRadarWidget, APawn* InPawn);

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void RegisterElement(UAC_RadarElement* Element);

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void UnregisterElement(UAC_RadarElement* Element);

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void UpdateRadar();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
