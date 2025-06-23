#include "Items/PickupBase.h"

#include "Components/SphereComponent.h"
#include "Helpers/InventorySystemFuncLib.h"
#include "Interfaces/InteractionInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Managers/InventoryAssetManager.h"
#include "Types/InventoryStructs.h"

APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	PickupMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	PickupMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	PickupMesh->SetSimulatePhysics(true);
	PickupMesh->SetGenerateOverlapEvents(false);

	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupSphere->AttachToComponent(PickupMesh, FAttachmentTransformRules::KeepRelativeTransform);
	
	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();

}

void APickupBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UInteractionInterface>())
	{
		if (const UDataTable* ItemDataTable = UInventorySystemFuncLib::GetItemDataTable())
		{
			FItemDataStruct* ItemDataStruct = ItemDataTable->FindRow<FItemDataStruct>(PickupName,TEXT(""));
			IInteractionInterface::Execute_Pick(OtherActor, *ItemDataStruct);
		}
	}
	Destroy();
}

TArray<FName> APickupBase::GetItemNameOptions() const
{
	return UInventorySystemFuncLib::GetItemDataRowNames();
}
