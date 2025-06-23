#include "Managers/InventoryAssetManager.h"

UInventoryAssetManager& UInventoryAssetManager::Get()
{
	check(GEngine);

	return *Cast<UInventoryAssetManager>(GEngine->AssetManager);
}

void UInventoryAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
