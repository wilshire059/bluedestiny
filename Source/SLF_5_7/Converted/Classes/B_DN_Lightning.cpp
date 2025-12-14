#include "B_DN_Lightning.h"

UB_DN_Lightning::UB_DN_Lightning()
{
	StatTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Defense.Negation.Lightning"));
	MaxValue = 9999.0f;
}
