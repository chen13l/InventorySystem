#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/BaseUserWidget.h"
#include "ScrollUniformGridComp.generated.h"

class UPackageOverlayController;
class UUniformGridPanel;
class UScrollBox;
class USizeBox;

UCLASS()
class INVENTORYSYSTEM_API UScrollUniformGridComp : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetRootSize_Implementation(FVector2D InNewSize) override;
	UFUNCTION(BlueprintCallable)
	void SetMaxSlotNum(int InNewMaxSlotNum);
	UFUNCTION(BlueprintCallable)
	void SetNumSlotARow(int InNewNumSlotARow);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool UpdateSlotData(UWidget* TargetWidget,int SlotIndex);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateAllSlots();

private:
	virtual void OnCreate() override;
	virtual void OnBindLocalEvent() override;
	virtual void OnUnBindLocalEvent() override;
	virtual void OnWidgetControllerSet_Implementation() override;

	FVector2D CalSlotSize();
	FVector2D GetActualSlotSize();
	void UpdateSlotsNeeded();
	void UpdateSlotRelated();
	UFUNCTION()
	void OnUserScrolledCallback(float InOffset);
	void MoveSlotRow(bool bMoveDown, int InRowOffset = 1);

	UFUNCTION()
	void SlotDataChangedCallback(int InIndex, FItemDataStruct NewData);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Scroll Uniform Grid", meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Scroll Uniform Grid", meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Content;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Scroll Uniform Grid", meta=(BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Scroll Uniform Grid", meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> UniformGridPanel_Content;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Scroll Uniform Grid", meta=(AllowPrivateAccess))
	TSubclassOf<UBaseUserWidget> SlotWidgetClass;
	TArray<TArray<TObjectPtr<UWidget>>> MinSlotsShown;
	TArray<FItemDataStruct> SlotDatas;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	UPackageOverlayController* PackageOverlayController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Scroll Uniform Grid", meta=(AllowPrivateAccess))
	int NumSlotARow = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Scroll Uniform Grid", meta=(AllowPrivateAccess))
	int MaxSlotNum = 0;

	int LastCurrentRow = 0;
	int MinRowsNeeded = 0;
	float ScrolledMaxOffsetY = 0;
	FVector2D LastSlotSize = FVector2D::ZeroVector;
	bool bShouldResetSlotPosition = false;
	bool bSizeChanged = false;
};
