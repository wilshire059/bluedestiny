#include "W_Browser_Animset_OwnerEntry.h"

void UW_Browser_Animset_OwnerEntry::SetOwnerName(FText OwnerName)
{
	if (OwnerNameText)
	{
		OwnerNameText->SetText(OwnerName);
	}
}
