#include "W_Status_StatBlock.h"

void UW_Status_StatBlock::NativeConstruct()
{
	Super::NativeConstruct();
	SetupStats();
}

void UW_Status_StatBlock::SetupStats()
{
	OnSetupStats();
}
