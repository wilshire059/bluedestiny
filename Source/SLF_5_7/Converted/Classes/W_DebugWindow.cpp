#include "W_DebugWindow.h"

void UW_DebugWindow::SetTitle(FText Title)
{
	if (TitleText)
	{
		TitleText->SetText(Title);
	}
}

void UW_DebugWindow::AddDebugLine(FText Line)
{
	OnAddDebugLine(Line);
}

void UW_DebugWindow::ClearContent()
{
	if (ContentContainer)
	{
		ContentContainer->ClearChildren();
	}
}
