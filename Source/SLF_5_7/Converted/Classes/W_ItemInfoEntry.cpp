#include "W_ItemInfoEntry.h"
#include "Styling/SlateColor.h"

void UW_ItemInfoEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (EntryText)
	{
		EntryText->SetText(EntryNameText);
	}

	if (ValueText)
	{
		ValueText->SetText(FText::AsNumber(Value));

		// Comparison Logic
		FSlateColor Color = FSlateColor(FLinearColor::White); // Default

		if (Value > CurrentStatValue)
		{
			// Blue / Better
			Color = FSlateColor(FLinearColor(0.24f, 0.3f, 0.75f, 1.0f)); 
		}
		else if (Value < CurrentStatValue)
		{
			// Red / Worse
			Color = FSlateColor(FLinearColor(0.36f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
            // Equal / Gray
            Color = FSlateColor(FLinearColor(0.86f, 0.85f, 0.83f, 1.0f));
		}

		ValueText->SetColorAndOpacity(Color);
	}
}
