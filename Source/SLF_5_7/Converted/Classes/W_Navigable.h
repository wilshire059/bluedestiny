#pragma once

#include "CoreMinimal.h"
#include "Classes/W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "InputMappingContext.h"
#include "W_Navigable.generated.h"

UCLASS()
class SLF_5_7_API UW_Navigable : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigable")
    FGameplayTag NavigableTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigable")
    TObjectPtr<UInputMappingContext> NavigableInputMapping;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Navigable")
    bool CanNavigate();

    virtual bool CanNavigate_Implementation();

    // Input management helpers could be added here if C++ needs to handle them explicitly
    // For now, mirroring Blueprint structure which likely handles input in Event Graph or specific overrides
};
