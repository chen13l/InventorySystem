#include "Helpers/InventorySystemFuncLib.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/BaseUMGManager.h"
#include "UI/InventoryHUD.h"
#include "UI/WidgetControllers/PackageOverlayController.h"

UBaseUMGManager* UInventorySystemFuncLib::GetBaseUMGManager(UObject* WorldContextObject)
{
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		return GameInstance->GetSubsystem<UBaseUMGManager>();
	}
	return nullptr;
}

UDataTable* UInventorySystemFuncLib::GetItemDataTable()
{
	UDataTable* ItemDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr,TEXT("/Game/Data/DT_ItemData.DT_ItemData")));
	if (ItemDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Load Data Success"));
		return ItemDataTable;
	}
	UE_LOG(LogTemp, Warning, TEXT("Load Data Failed"));
	return nullptr;
}

TArray<FName> UInventorySystemFuncLib::GetItemDataRowNames()
{
	TArray<FName> RowNames;
	if (GetItemDataTable())
	{
		for (auto& [RowName,Row] : GetItemDataTable()->GetRowMap())
		{
			RowNames.Add(RowName);
		}
	}

	return RowNames;
}

bool UInventorySystemFuncLib::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutParams, AInventoryHUD*& OutHUD)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutHUD = PlayerController->GetHUD<AInventoryHUD>();
		if (OutHUD)
		{
			OutParams.PlayerController = PlayerController;

			return true;
		}
	}

	return false;
}


UPackageOverlayController* UInventorySystemFuncLib::GetPackageOverlayController(UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	AInventoryHUD* InventoryHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams, InventoryHUD))
	{
		if (InventoryHUD)
		{
			return InventoryHUD->GetPackageOverlayController(WidgetControllerParams);
		}
	}
	return nullptr;
}
