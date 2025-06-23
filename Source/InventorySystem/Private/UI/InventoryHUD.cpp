#include "UI/InventoryHUD.h"

#include "UI/WidgetControllers/PackageOverlayController.h"

UPackageOverlayController* AInventoryHUD::GetPackageOverlayController(const FWidgetControllerParams& WCParams)
{
	if (PackageOverlayController == nullptr)
	{
		PackageOverlayController = NewObject<UPackageOverlayController>(this,UPackageOverlayController::StaticClass());
		PackageOverlayController->SetWidgetControllerParams(WCParams);
		PackageOverlayController->BindCallbacksToDependencies();
	}
	return PackageOverlayController;
}
