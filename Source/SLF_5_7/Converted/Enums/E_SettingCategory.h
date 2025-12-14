#pragma once

#include "CoreMinimal.h"
#include "E_SettingCategory.generated.h"

UENUM(BlueprintType)
enum class E_SettingCategory : uint8
{
	GameOptions UMETA(DisplayName = "Game Options"),
	CameraOptions UMETA(DisplayName = "Camera Options"),
	DisplayOptions UMETA(DisplayName = "Display Options"),
	SoundOptions UMETA(DisplayName = "Sound Options"),
	KeybindOptions UMETA(DisplayName = "Keybind Options"),
	QuitGame UMETA(DisplayName = "Quit Game")
};
