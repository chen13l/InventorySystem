#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class UUserDefinedEnum;
class USphereComponent;

UCLASS()
class INVENTORYSYSTEM_API APickupBase : public AActor
{
	GENERATED_BODY()

public:
	APickupBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                  AActor* OtherActor,
	                                  UPrimitiveComponent* OtherComp,
	                                  int32 OtherBodyIndex,
	                                  bool bFromSweep,
	                                  const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup Base", meta=(AllowPrivateAccess))
	UStaticMeshComponent* PickupMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup Base", meta=(AllowPrivateAccess))
	USphereComponent* PickupSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup Base", meta=(AllowPrivateAccess, GetOptions="GetItemNameOptions"))
	FName PickupName;
	UFUNCTION()
	TArray<FName> GetItemNameOptions() const;
};
