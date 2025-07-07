#include "UI/WidgetControllers/PackageOverlayController.h"

#include "Player/BasePlayerController.h"
#include "Player/Comps/PackageCompBase.h"

void UPackageOverlayController::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PackageComp = Params.PackageComp;
}

void UPackageOverlayController::BindCallbacksToDependencies()
{
	if (PackageComp)
	{
		PackageComp->OnSlotDataChangedDelegate.AddDynamic(this, &UPackageOverlayController::UpdateSlotData);
	}
}

void UPackageOverlayController::BroadcastInitializeValues()
{
	for (int i = 0; i < ItemDatas.Num(); ++i)
	{
		OnDataChangedDelegate.Broadcast(i, ItemDatas[i]);
	}
}

void UPackageOverlayController::InitWidgetController()
{
	ACharacter* Character = PlayerController->GetCharacter();
	if (Character && Character->Implements<UInteractionInterface>())
	{
		PackageComp = IInteractionInterface::Execute_GetPackageComp(Character);
		ItemDatas = PackageComp->GetItemSlotDatas();
	}

	BindCallbacksToDependencies();
	BroadcastInitializeValues();
}

void UPackageOverlayController::UpdateSlotData(int InIndex, FItemDataStruct NewData)
{
	if (ItemDatas.Num() - 1 < InIndex)
	{
		if (PackageComp)
		{
			ItemDatas = PackageComp->GetItemSlotDatas();
		}
		else
		{
			ItemDatas.SetNum(InIndex + 1);
		}
	}

	ItemDatas[InIndex] = NewData;

	OnDataChangedDelegate.Broadcast(InIndex, NewData);
}

ABasePlayerController* UPackageOverlayController::GetMyPlayerController()
{
	if (BaseMyPlayerController == nullptr)
	{
		BaseMyPlayerController = Cast<ABasePlayerController>(PlayerController);
	}
	return BaseMyPlayerController;
}
