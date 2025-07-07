#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryStructs.h"
#include "PackageCompBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotDataChangedSignature, int, Index, FItemDataStruct, NewData);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UPackageCompBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	int FindItemSlotIndex(FItemDataStruct ItemData);
	
public:
	UPackageCompBase();
	
	FORCEINLINE TArray<FItemDataStruct> GetItemSlotDatas(){return ItemSlots;}

	UFUNCTION(BlueprintCallable)
	bool AddItemToPackage(FItemDataStruct ItemData);
	
protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<FItemDataStruct> ItemSlots;

public:
	UPROPERTY(BlueprintAssignable)
	FOnSlotDataChangedSignature OnSlotDataChangedDelegate;
};
