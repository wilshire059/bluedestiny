#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Image.h"
#include "W_ItemWheel_NextSlot.generated.h"

UCLASS()
class SLF_5_7_API UW_ItemWheel_NextSlot : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 SlotOffset = 1;

	UFUNCTION(BlueprintCallable, Category = "ItemWheel")
	void UpdateSlotDisplay(UTexture2D* Icon);

	UFUNCTION(BlueprintCallable, Category = "ItemWheel")
	void ClearSlot();
};
