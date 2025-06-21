#include "Helpers/InventorySystemFuncLib.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Managers/BaseUMGManager.h"

UBaseUMGManager* UInventorySystemFuncLib::GetBaseUMGManager(UObject* WorldContextObject)
{
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		return GameInstance->GetSubsystem<UBaseUMGManager>();
	}
	return nullptr;
}
