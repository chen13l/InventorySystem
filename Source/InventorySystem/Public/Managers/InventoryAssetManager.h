#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "InventoryAssetManager.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UInventoryAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UInventoryAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
