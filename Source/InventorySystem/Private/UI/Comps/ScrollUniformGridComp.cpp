#include "UI/Comps/ScrollUniformGridComp.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Helpers/InventorySystemFuncLib.h"
#include "Kismet/KismetMathLibrary.h"
#include "Managers/BaseUMGManager.h"
#include "UI/WidgetControllers/PackageOverlayController.h"

void UScrollUniformGridComp::OnCreate()
{
	Super::OnCreate();

	bShouldResetSlotPosition = true;
}

void UScrollUniformGridComp::SetRootSize_Implementation(FVector2D InNewSize)
{
	SizeBox_Root->SetWidthOverride(InNewSize.X);
	SizeBox_Root->SetHeightOverride(InNewSize.Y);
	SizeBox_Content->SetWidthOverride(InNewSize.X);

	bSizeChanged = CalSlotSize() != LastSlotSize;
	UpdateSlotRelated();
}

// 获取Slot的Size（不含UniformGrid提供的Padding）
FVector2D UScrollUniformGridComp::CalSlotSize()
{
	FVector2D OutSize = FVector2D::ZeroVector;

	FVector2D ContentBoxSize(SizeBox_Root->GetWidthOverride(), SizeBox_Root->GetWidthOverride()); // 内容盒大小

	// 获取UniformGrid中SlotPadding和
	float PaddingX = UniformGridPanel_Content->GetSlotPadding().Left + UniformGridPanel_Content->GetSlotPadding().Right;
	FVector2D UniformGridTotalPadding(PaddingX, PaddingX);
	UniformGridTotalPadding = UKismetMathLibrary::Multiply_Vector2DFloat(UniformGridTotalPadding, NumSlotARow);

	// 排除padding后Slots的Size之和
	FVector2D ActualContentSize = UKismetMathLibrary::Subtract_Vector2DVector2D(ContentBoxSize, UniformGridTotalPadding);

	// 一个Slot的Size
	OutSize = UKismetMathLibrary::Divide_Vector2DFloat(ActualContentSize, NumSlotARow);
	return OutSize;
}

// 获取Slot的Size（包含UniformGrid提供的Padding）
FVector2D UScrollUniformGridComp::GetActualSlotSize()
{
	if (UniformGridPanel_Content == nullptr) { return FVector2D(); }
	FVector2D UniformGridTotalPadding(UniformGridPanel_Content->GetSlotPadding().Left * 2, UniformGridPanel_Content->GetSlotPadding().Top * 2);

	FVector2D OutSize(CalSlotSize());
	if (OutSize.IsZero()) { return OutSize; }

	return UKismetMathLibrary::Add_Vector2DVector2D(OutSize, UniformGridTotalPadding);
}

void UScrollUniformGridComp::UpdateSlotsNeeded()
{
	if (MinSlotsShown.Num() < MinRowsNeeded * NumSlotARow) // 现有Slot数量少于最多需要显示的位置数量
	{
		int32 RowToCreate = FMath::CeilToInt((MinRowsNeeded * NumSlotARow - MinSlotsShown.Num()) / (float)NumSlotARow);
		// 创建Slot并添加
		for (int i = 0; i < RowToCreate; i++)
		{
			if (GetOwningPlayer())
			{
				UBaseUMGManager* BaseUMGManager = UInventorySystemFuncLib::GetBaseUMGManager(GetOwningPlayer());
				if (BaseUMGManager)
				{
					TArray<TObjectPtr<UWidget>> Arr;
					for (int j = 0; j < NumSlotARow; j++)
					{
						auto NewWidget = BaseUMGManager->CreateUMGWidget(SlotWidgetClass);
						if (NewWidget->Implements<UUIInterfaces>())
						{
							IUIInterfaces::Execute_SetRootSize(NewWidget, CalSlotSize());
						}
						Arr.Add(NewWidget);
					}
					MinSlotsShown.Emplace(Arr);
				}
			}
		}
	}
}

// 更新UniformGird中需要显示的Slot
void UScrollUniformGridComp::UpdateSlotRelated()
{
	// 需要的最少行数
	MinRowsNeeded = UKismetMathLibrary::FCeil(SizeBox_Root->GetHeightOverride() / GetActualSlotSize().Y) + 1;
	// 到列表底部的偏移量
	ScrolledMaxOffsetY = GetActualSlotSize().Y * (MaxSlotNum / NumSlotARow) - SizeBox_Root->GetHeightOverride();

	// 更新Slot's Size，发生在游戏窗口大小发生变化
	if (bSizeChanged)
	{
		FVector2D NewSize(CalSlotSize());
		LastSlotSize = NewSize;
		for (auto& WidgetArr : MinSlotsShown)
		{
			for (auto& RowWidget : WidgetArr)
			{
				if (RowWidget->Implements<UUIInterfaces>())
				{
					IUIInterfaces::Execute_SetRootSize(RowWidget, NewSize);
				}
			}
		}
		SizeBox_Content->SetHeightOverride(GetActualSlotSize().Y * (MaxSlotNum / NumSlotARow));

		bSizeChanged = false;
	}

	// 更新一行中Slot数量后，更新Slot位置
	if (bShouldResetSlotPosition)
	{
		// 更新UniformGird中需要显示的Slot
		UpdateSlotsNeeded();

		// 更新Slot行、列
		UniformGridPanel_Content->ClearChildren();
		for (int i = 0; i < MinSlotsShown.Num(); ++i)
		{
			for (int j = 0; j < NumSlotARow; ++j)
			{
				UniformGridPanel_Content->AddChildToUniformGrid(MinSlotsShown[i][j], i, j);
			}
		}
		UpdateAllSlots();

		bShouldResetSlotPosition = false;
	}
}

// 移动背包中的一行到显示的最后（最前）
void UScrollUniformGridComp::MoveSlotRow(bool bMoveDown, int InRowOffset/* =1 */)
{
	// 获取最后（前）一行，并在Grid中更新（该函数只会在容量大于显示数量时调用）
	for (int i = 0; i < FMath::Abs(InRowOffset); ++i)
	{
		int32 WidgetArrIndex = bMoveDown ? 0 : MinSlotsShown.Num() - 1;
		auto WidgetArr = MinSlotsShown[WidgetArrIndex];

		int32 InsertRow = MinSlotsShown.Num() > 0
			                  ? (bMoveDown
				                     ? UWidgetLayoutLibrary::SlotAsUniformGridSlot(MinSlotsShown.Last()[0])->GetRow()
				                     : UWidgetLayoutLibrary::SlotAsUniformGridSlot(MinSlotsShown[0][0])->GetRow())
			                  : 0;

		MinSlotsShown.RemoveAt(WidgetArrIndex);
		if (bMoveDown) { MinSlotsShown.EmplaceAt(MinSlotsShown.Num(), WidgetArr); }
		else { MinSlotsShown.Insert(WidgetArr, 0); }


		for (auto& RowWidget : WidgetArr)
		{
			if (UUniformGridSlot* SlotAsUniformGridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(RowWidget))
			{
				SlotAsUniformGridSlot->SetRow(FMath::Max(InRowOffset + InsertRow, 0));

				int32 WidgetIndexInData = SlotAsUniformGridSlot->GetRow() * NumSlotARow + SlotAsUniformGridSlot->GetColumn();
				UpdateSlotData(RowWidget, WidgetIndexInData);
			}
		}
	}
}

// 背包上下滑动，使用少量Widget，通过更新Slot位置和数据更新背包
void UScrollUniformGridComp::OnUserScrolledCallback(float InOffset)
{
	// 到列表底
	if (InOffset >= ScrolledMaxOffsetY) { return; }

	// 行数不变
	int CurrentRow = InOffset / GetActualSlotSize().Y;
	if (CurrentRow == LastCurrentRow) { return; }

	// 移动行数与方向 (>0为下滑)
	int RowOffset = CurrentRow - LastCurrentRow;
	LastCurrentRow = CurrentRow;

	//往上拖的时候，第一行变成最后一行；往下拖的时候，最后一行变成第一行
	MoveSlotRow(RowOffset > 0, RowOffset);
}

void UScrollUniformGridComp::OnBindLocalEvent()
{
	Super::OnBindLocalEvent();

	if (ScrollBox)
	{
		ScrollBox->OnUserScrolled.AddDynamic(this, &UScrollUniformGridComp::OnUserScrolledCallback);
	}
}

void UScrollUniformGridComp::OnUnBindLocalEvent()
{
	Super::OnUnBindLocalEvent();

	ScrollBox->OnUserScrolled.RemoveAll(this);
}

void UScrollUniformGridComp::SlotDataChangedCallback(int InIndex, FItemDataStruct NewData)
{
	if (SlotDatas.Num() - 1 < InIndex)
	{
		if (PackageOverlayController)
		{
			SlotDatas = PackageOverlayController->GetItemDatas();
		}
		else
		{
			SlotDatas.SetNum(InIndex + 1);
		}
	}
	SlotDatas[InIndex] = NewData;

	// update ui
	if (MinSlotsShown.Num() > InIndex)
	{
		auto TargetSlot = MinSlotsShown[(InIndex / NumSlotARow) % MinSlotsShown.Num()][InIndex % NumSlotARow];
		UpdateSlotData(TargetSlot, InIndex);
	}
}

void UScrollUniformGridComp::OnWidgetControllerSet_Implementation()
{
	Super::OnWidgetControllerSet_Implementation();

	if (IsValid(WidgetController))
	{
		if (Cast<UPackageOverlayController>(WidgetController))
		{
			PackageOverlayController = Cast<UPackageOverlayController>(WidgetController);
			PackageOverlayController->OnDataChangedDelegate.AddDynamic(this, &UScrollUniformGridComp::SlotDataChangedCallback);
		}
	}
}

void UScrollUniformGridComp::SetMaxSlotNum(int InNewMaxSlotNum)
{
	MaxSlotNum = InNewMaxSlotNum;
	UpdateSlotRelated();
}

void UScrollUniformGridComp::SetNumSlotARow(int InNewNumSlotARow)
{
	NumSlotARow = InNewNumSlotARow;
	bShouldResetSlotPosition = true;
	UpdateSlotRelated();
}

void UScrollUniformGridComp::UpdateAllSlots_Implementation()
{
	for (auto& WidgetArr : MinSlotsShown)
	{
		for (auto& RowWidget : WidgetArr)
		{
			if (UUniformGridSlot* SlotAsUniformGridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(RowWidget))
			{
				int SlotIndex = SlotAsUniformGridSlot->GetRow() * NumSlotARow + SlotAsUniformGridSlot->GetColumn();
				if (!UpdateSlotData(RowWidget, SlotIndex) && RowWidget->Implements<USlotRelatedInterface>())
				{
					FItemDataStruct DataStruct;
					ISlotRelatedInterface::Execute_SetSlotData(RowWidget, DataStruct);
				}
			}
		}
	}
}

bool UScrollUniformGridComp::UpdateSlotData_Implementation(UWidget* TargetWidget, int SlotIndex)
{
	FItemDataStruct SlotData;
	if (SlotIndex < SlotDatas.Num())
	{
		SlotData = SlotDatas[SlotIndex];
	}

	if (TargetWidget && TargetWidget->Implements<USlotRelatedInterface>())
	{
		ISlotRelatedInterface::Execute_SetSlotData(TargetWidget, SlotData);
		return true;
	}
	return false;
}
