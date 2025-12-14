#include "W_NPC_Window_Vendor.h"

void UW_NPC_Window_Vendor::SetupVendorInventory(const TArray<FInventoryItem>& VendorItems)
{
	OnSetupVendorItems(VendorItems);
}

void UW_NPC_Window_Vendor::SetupPlayerInventory(const TArray<FInventoryItem>& PlayerItems)
{
	OnSetupPlayerItems(PlayerItems);
}

void UW_NPC_Window_Vendor::BuyItem(int32 ItemIndex)
{
	OnVendorItemSelected.Broadcast(ItemIndex, true);
}

void UW_NPC_Window_Vendor::SellItem(int32 ItemIndex)
{
	OnVendorItemSelected.Broadcast(ItemIndex, false);
}
