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

USTRUCT(BlueprintType)
struct FUIWidgetStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDataChangedSignature, int, Index, FUIWidgetStruct, NewStruct);

UCLASS(BlueprintType, Blueprintable)
class INVENTORYSYSTEM_API UPackageOverlayController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetControllerParams(const FWidgetControllerParams& Params);
	virtual void BindCallbacksToDependencies();

	UFUNCTION(BlueprintCallable)
	ABasePlayerController* GetMyPlayerController();

	UPROPERTY(BlueprintAssignable)
	FOnDataChangedSignature OnDataChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<ABasePlayerController> BaseMyPlayerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPackageCompBase* PackageComp;
};
