#include "W_StatBlock_LevelUp.h"

void UW_StatBlock_LevelUp::NativeConstruct()
{
	Super::NativeConstruct();
	SetupStats();
}

void UW_StatBlock_LevelUp::SetupStats()
{
	OnSetupStats();
}
