#include "PDA_Vendor.h"
#include "PDA_Item.h"

UPDA_Vendor::UPDA_Vendor()
{
}

void UPDA_Vendor::ReduceItemStock(UPDA_Item* Item, int32 Delta)
{
	for (FVendorItem& VendorItem : Items)
	{
		if (VendorItem.Item == Item && VendorItem.Stock > 0)
		{
			VendorItem.Stock = FMath::Max(0, VendorItem.Stock - Delta);
			return;
		}
	}
}

void UPDA_Vendor::IncreaseItemStock(UPDA_Item* Item, int32 Delta)
{
	for (FVendorItem& VendorItem : Items)
	{
		if (VendorItem.Item == Item)
		{
			VendorItem.Stock += Delta;
			return;
		}
	}
}

int32 UPDA_Vendor::GetItemStock(UPDA_Item* Item) const
{
	for (const FVendorItem& VendorItem : Items)
	{
		if (VendorItem.Item == Item)
		{
			return VendorItem.Stock;
		}
	}
	return 0;
}

int32 UPDA_Vendor::GetItemPrice(UPDA_Item* Item) const
{
	for (const FVendorItem& VendorItem : Items)
	{
		if (VendorItem.Item == Item)
		{
			return VendorItem.Price;
		}
	}
	return 0;
}
