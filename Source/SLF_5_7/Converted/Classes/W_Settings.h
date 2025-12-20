#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/Overlay.h"
#include "Components/SizeBox.h"
#include "W_Settings.generated.h"

class UW_Settings_Entry;
class UW_Settings_CategoryEntry;
class UW_Settings_ControlsDisplay;
class UW_Settings_KeyMapping;
class UW_Settings_PlayerCard;
class UW_Settings_QuitConfirmation;
class UW_GenericButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsSaved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsCancelled);

UCLASS()
class SLF_5_7_API UW_Settings : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	// ==================== Input Icons ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> BackInputIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ScrollLeftInputIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ScrollRightInputIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ScrollLeftCategoryInputIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ScrollRightCategoryInputIcon;

	// ==================== Layout Containers ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> ButtonsBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> CategoriesBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> ExitButtonBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UOverlay> Main;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> MainBoxSizer;

	// ==================== Widget Switchers ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> CategorySwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> SettingsSwitcher;

	// ==================== Background/Blur ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> MainBlur;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> ConfirmationBorder;

	// ==================== Text Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> EntryDescriptionText;

	// ==================== Category Entry Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_CategoryEntry> W_Settings_CategoryEntry_Camera;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_CategoryEntry> W_Settings_CategoryEntry_Display;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_CategoryEntry> W_Settings_CategoryEntry_Gameplay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_CategoryEntry> W_Settings_CategoryEntry_Keybinds;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_CategoryEntry> W_Settings_CategoryEntry_Quit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_CategoryEntry> W_Settings_CategoryEntry_Sounds;

	// ==================== Settings Sub-Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_ControlsDisplay> W_Settings_ControlsDisplay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_KeyMapping> W_Settings_KeyMapping;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_PlayerCard> W_Settings_PlayerCard;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_QuitConfirmation> W_Settings_QuitConfirmation;

	// ==================== Settings Entry Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> AntialiasingQuality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> CameraSpeed;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> FoliageQuality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> GlobalIlluminationQuality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> InvertCameraX;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> InvertCameraY;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> PostprocessQuality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> ReflectionQuality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> Resolution;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> ScreenMode;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> ShaderQuality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> ShadowQuality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> TextureQuality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_Settings_Entry> ViewDistanceQuality;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UW_Settings_KeyMapping> KeyMappingSettings;

	// ==================== Generic Button Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_GenericButton> W_GB_Desktop;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_GenericButton> W_GB_Quit;

	// ==================== Events ====================
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSettingsSaved OnSettingsSaved;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSettingsCancelled OnSettingsCancelled;

	// ==================== State ====================
	UPROPERTY(BlueprintReadWrite, Category = "State")
	int32 CurrentCategoryIndex = 0;

	// Keep for compatibility
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UHorizontalBox> CategoryTabsContainer;

	// ==================== Functions ====================
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SwitchCategory(int32 CategoryIndex);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void ApplySettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void RevertSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void CloseSettings();

protected:
	virtual void NativeConstruct() override;
};
