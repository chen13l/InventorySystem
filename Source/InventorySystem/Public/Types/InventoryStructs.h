#pragma once

#include "CoreMinimal.h"
#include "InventoryStructs.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	Eatable,
	Shield,
	Weapon,
	Money,
};

USTRUCT(BlueprintType)
struct FItemDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory|Item")
	FName ItemName = FName();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory|Item")
	int32 ItemID = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory|Item")
	float Quality = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory|Item")
	EItemType ItemType = EItemType::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory|Item")
	UTexture2D* Icon = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory|Item")
	float Price = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory|Item")
	float Quantity = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory|Item")
	FString Description = "";
};
