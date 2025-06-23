#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Interfaces/InteractionInterface.h"
#include "BasePlayerCharacter.generated.h"

class UPackageCompBase;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class INVENTORYSYSTEM_API ABasePlayerCharacter : public ABaseCharacter,public IInteractionInterface
{
	GENERATED_BODY()

public:
	ABasePlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;

	/* IInteractionInterface */
	virtual void Pick_Implementation(const FItemDataStruct& PickupItemData) override;
	virtual UPackageCompBase* GetPackageComp_Implementation() override;
	/* End IInteractionInterface */
protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UPackageCompBase* PackageComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* MouseLookAction;
};
