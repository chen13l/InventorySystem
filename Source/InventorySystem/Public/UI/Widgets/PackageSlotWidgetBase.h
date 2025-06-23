#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "PackageSlotWidgetBase.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UPackageSlotWidgetBase : public UBaseUserWidget
{
	GENERATED_BODY()
public:
	UTexture2D* GetIcon(){return Icon;};

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Slot",meta=(AllowPrivateAccess=true))
	UTexture2D* Icon = nullptr;
	
};
