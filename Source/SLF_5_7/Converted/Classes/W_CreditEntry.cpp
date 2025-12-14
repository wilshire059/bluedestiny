#include "W_CreditEntry.h"

void UW_CreditEntry::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (RoleText && !Role.IsEmpty())
	{
		RoleText->SetText(Role);
	}

	if (NameText && !Name.IsEmpty())
	{
		NameText->SetText(Name);
	}
}

void UW_CreditEntry::SetupEntry(FText InRole, FText InName)
{
	Role = InRole;
	Name = InName;

	if (RoleText)
	{
		RoleText->SetText(Role);
	}

	if (NameText)
	{
		NameText->SetText(Name);
	}
}
