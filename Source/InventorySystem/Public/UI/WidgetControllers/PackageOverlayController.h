#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractionInterface.h"
#include "UObject/Object.h"
#include "PackageOverlayController.generated.h"

class UPackageCompBase;
class ABasePlayerController;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams()
	{
	}

	FWidgetControllerParams(APlayerController* InPC): PlayerController(InPC)
	{
		ACharacter* Character = InPC->GetCharacter();
		if (Character && Character->Implements<UInteractionInterface>())
		{
			PackageComp = IInteractionInterface::Execute_GetPackageComp(Character);
		}
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	APlayerController* PlayerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPackageCompBase* PackageComp;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDataChangedSignature, int, Index, FItemDataStruct, NewData);

UCLASS(BlueprintType, Blueprintable)
class INVENTORYSYSTEM_API UPackageOverlayController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetControllerParams(const FWidgetControllerParams& Params);
	virtual void InitWidgetController();

	UFUNCTION(BlueprintCallable)
	ABasePlayerController* GetMyPlayerController();

	FORCEINLINE TArray<FItemDataStruct> GetItemDatas(){return ItemDatas;}

protected:
	virtual void BindCallbacksToDependencies();
	virtual void BroadcastInitializeValues();

private:
	UFUNCTION()
	void UpdateSlotData(int InIndex, FItemDataStruct NewData);
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnDataChangedSignature OnDataChangedDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<ABasePlayerController> BaseMyPlayerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPackageCompBase* PackageComp;
	TArray<FItemDataStruct> ItemDatas;
};
