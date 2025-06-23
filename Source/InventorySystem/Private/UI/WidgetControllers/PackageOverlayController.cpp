#include "UI/WidgetControllers/PackageOverlayController.h"

#include "Player/BasePlayerController.h"

void UPackageOverlayController::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PackageComp = Params.PackageComp;
}

void UPackageOverlayController::BindCallbacksToDependencies()
{
}

ABasePlayerController* UPackageOverlayController::GetMyPlayerController()
{
	if (BaseMyPlayerController == nullptr)
	{
		BaseMyPlayerController = Cast<ABasePlayerController>(PlayerController);
	}
	return BaseMyPlayerController;
}
