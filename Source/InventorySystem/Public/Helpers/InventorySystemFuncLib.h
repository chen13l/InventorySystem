#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventorySystemFuncLib.generated.h"

class AInventoryHUD;
struct FWidgetControllerParams;
class UPackageOverlayController;
class UBaseUMGManager;

UCLASS()
class INVENTORYSYSTEM_API UInventorySystemFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "InventorySystemHealper|Manager", meta=(DefaultToSelf="WorldContextObject"))
	static UBaseUMGManager* GetBaseUMGManager(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "InventorySystemHealper|Manager")
	static UDataTable* GetItemDataTable();
	UFUNCTION(BlueprintCallable, Category = "InventorySystemHealper|Manager")
	static TArray<FName> GetItemDataRowNames();

	UFUNCTION(BlueprintCallable, Category = "InventorySystemHealper|Manager", meta=(DefaultToSelf="WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutParams,AInventoryHUD*& OutHUD);
	UFUNCTION(BlueprintCallable, Category = "InventorySystemHealper|Manager", meta=(DefaultToSelf="WorldContextObject"))
	static UPackageOverlayController* GetPackageOverlayController(UObject* WorldContextObject);
};
