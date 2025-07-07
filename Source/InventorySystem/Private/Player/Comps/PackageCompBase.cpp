#include "Player/Comps/PackageCompBase.h"

UPackageCompBase::UPackageCompBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPackageCompBase::BeginPlay()
{
	Super::BeginPlay();
}

bool UPackageCompBase::AddItemToPackage(FItemDataStruct ItemData)
{
	int ItemIndex = FindItemSlotIndex(ItemData);
	if (ItemIndex == -1)
	{
		ItemIndex = ItemSlots.Emplace(ItemData);
	}
	else
	{
		ItemSlots[ItemIndex].Quantity += ItemData.Quantity;
	}

	OnSlotDataChangedDelegate.Broadcast(ItemIndex, ItemSlots[ItemIndex]);
	return true;
}

int UPackageCompBase::FindItemSlotIndex(FItemDataStruct ItemData)
{
	for (int i = 0; i < ItemSlots.Num(); i++)
	{
		if (ItemSlots[i].ItemName == ItemData.ItemName)
		{
			return i;
		}
	}
	return -1;
}
