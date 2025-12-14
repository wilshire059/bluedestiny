#include "B_DN_Magic.h"

UB_DN_Magic::UB_DN_Magic()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Defense.Negation.Magic"));
	MaxValue = 9999.0f;
}
