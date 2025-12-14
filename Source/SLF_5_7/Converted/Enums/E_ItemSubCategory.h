#pragma once

#include "CoreMinimal.h"
#include "E_ItemSubCategory.generated.h"

UENUM(BlueprintType)
enum class E_ItemSubCategory : uint8
{
	None UMETA(DisplayName="None"),
	Flasks UMETA(DisplayName="Flasks"),
	Consumables UMETA(DisplayName="Consumables"),
	Projectiles UMETA(DisplayName="Projectiles"),
	Enchants UMETA(DisplayName="Enchants"),
	Miscellaneous UMETA(DisplayName="Miscellaneous"),
	Runes UMETA(DisplayName="Runes"),
	Head UMETA(DisplayName="Head"),
	Chest UMETA(DisplayName="Chest"),
	Arms UMETA(DisplayName="Arms"),
	Legs UMETA(DisplayName="Legs"),
	Talismans UMETA(DisplayName="Talismans"),
	InfoItems UMETA(DisplayName="Info Items"),
	Sword UMETA(DisplayName="Sword"),
	Katana UMETA(DisplayName="Katana"),
	Axe UMETA(DisplayName="Axe"),
	Mace UMETA(DisplayName="Mace"),
	Staff UMETA(DisplayName="Staff"),
};

