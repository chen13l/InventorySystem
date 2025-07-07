#include "UI/InventoryHUD.h"

#include "UI/WidgetControllers/PackageOverlayController.h"

UPackageOverlayController* AInventoryHUD::GetPackageOverlayController(const FWidgetControllerParams& WCParams)
{
	if (!IsValid(PackageOverlayController))
	{
		PackageOverlayController = NewObject<UPackageOverlayController>(this,UPackageOverlayController::StaticClass());
		PackageOverlayController->SetWidgetControllerParams(WCParams);
		PackageOverlayController->InitWidgetController();
	}
	return PackageOverlayController;
}
