#pragma once

#include "CoreMinimal.h"
#include "Types/InventoryStructs.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

class UPackageCompBase;

UINTERFACE()
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORYSYSTEM_API IInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Pick(const FItemDataStruct& PickupItemData);
	UFUNCTION(BlueprintNativeEvent)
	UPackageCompBase* GetPackageComp();
};
