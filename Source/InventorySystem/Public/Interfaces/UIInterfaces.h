#pragma once

#include "CoreMinimal.h"
#include "Types/InventoryStructs.h"
#include "UObject/Interface.h"
#include "UIInterfaces.generated.h"

UINTERFACE()
class UUIInterfaces : public UInterface
{
	GENERATED_BODY()
};

class INVENTORYSYSTEM_API IUIInterfaces
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetRootSize(FVector2D InNewSize);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "UI")
	int GetUMGIndex();
};



UINTERFACE()
class USlotRelatedInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORYSYSTEM_API ISlotRelatedInterface 
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Slot")
	void SetSlotData(FItemDataStruct InData);
};