#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class INVENTORYSYSTEM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess=true))
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess=true))
	UInputAction* PackageWidgetAction;

	UFUNCTION(BlueprintNativeEvent)
	void OpenPackage();
	
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	
};
