#include "W_Navigable_InputReader.h"

void UW_Navigable_InputReader::HandleNavigationInput(FVector2D Direction)
{
	OnNavigationInput(Direction);
}

void UW_Navigable_InputReader::HandleConfirmInput()
{
	OnConfirmInput();
}

void UW_Navigable_InputReader::HandleCancelInput()
{
	OnCancelInput();
}

FReply UW_Navigable_InputReader::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FKey Key = InKeyEvent.GetKey();

	if (Key == EKeys::Up || Key == EKeys::W || Key == EKeys::Gamepad_DPad_Up)
	{
		HandleNavigationInput(FVector2D(0.0f, -1.0f));
		return FReply::Handled();
	}
	if (Key == EKeys::Down || Key == EKeys::S || Key == EKeys::Gamepad_DPad_Down)
	{
		HandleNavigationInput(FVector2D(0.0f, 1.0f));
		return FReply::Handled();
	}
	if (Key == EKeys::Left || Key == EKeys::A || Key == EKeys::Gamepad_DPad_Left)
	{
		HandleNavigationInput(FVector2D(-1.0f, 0.0f));
		return FReply::Handled();
	}
	if (Key == EKeys::Right || Key == EKeys::D || Key == EKeys::Gamepad_DPad_Right)
	{
		HandleNavigationInput(FVector2D(1.0f, 0.0f));
		return FReply::Handled();
	}
	if (Key == EKeys::Enter || Key == EKeys::SpaceBar || Key == EKeys::Gamepad_FaceButton_Bottom)
	{
		HandleConfirmInput();
		return FReply::Handled();
	}
	if (Key == EKeys::Escape || Key == EKeys::Gamepad_FaceButton_Right)
	{
		HandleCancelInput();
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply UW_Navigable_InputReader::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyUp(InGeometry, InKeyEvent);
}
