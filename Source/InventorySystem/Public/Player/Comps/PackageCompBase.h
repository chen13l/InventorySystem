#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryStructs.h"
#include "PackageCompBase.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UPackageCompBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UPackageCompBase();

protected:
	virtual void BeginPlay() override;
	
public:
	FORCEINLINE TArray<FItemDataStruct> GetItemSlots(){return ItemSlots;}

	UFUNCTION(BlueprintCallable)
	bool AddItemToPackage(FItemDataStruct ItemData);
	
protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<FItemDataStruct> ItemSlots;

	int FindItemSlotIndex(FItemDataStruct ItemData);
};
