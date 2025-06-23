#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventoryHUD.generated.h"

struct FWidgetControllerParams;
class UPackageOverlayController;

UCLASS()
class INVENTORYSYSTEM_API AInventoryHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPackageOverlayController* GetPackageOverlayController(const FWidgetControllerParams& WCParams);

private:
	UPROPERTY()
	UPackageOverlayController* PackageOverlayController;
};
