#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "Components/Image.h"
#include "Components/InvalidationBox.h"
#include "PackageSlotWidgetBase.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UPackageSlotWidgetBase : public UBaseUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	bool SetIconTexture(UTexture2D* Texture);

protected:
	UPROPERTY(meta=(BindWidget))
	UImage* Icon = nullptr;
	UPROPERTY(meta=(BindWidget))
	UInvalidationBox* InvalidationBox;

private:
	UFUNCTION(BlueprintCallable)
	void StartChanging();
	UFUNCTION(BlueprintCallable)
	void FinishChanged();
};
