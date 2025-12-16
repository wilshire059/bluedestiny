#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_DebugCentral.generated.h"

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_DebugCentral : public UActorComponent
{
	GENERATED_BODY()

public:
	UAC_DebugCentral();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bDebugEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bShowStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bShowAI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bShowCombat;

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void ToggleDebug();

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void LogDebugMessage(const FString& Message, FLinearColor Color = FLinearColor::White);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
