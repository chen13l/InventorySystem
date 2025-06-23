#include "Managers/BaseUMGManager.h"
#include "UI/Widgets/BaseUserWidget.h"

void UBaseUMGManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

UBaseUserWidget* UBaseUMGManager::GetUMGWidget(TSubclassOf<UBaseUserWidget> WidgetClass, int InIndex, bool CanLastWidget)
{
	FString WidgetName = WidgetClass->GetName();

	// 没有该类对象在池中
	if (!Widgets.Contains(WidgetName)) { return nullptr; }

	TArray<UBaseUserWidget*> WidgetArr = Widgets.Find(WidgetName)->UMGs;
	if (WidgetArr.Num() <= 0) { return nullptr; }


	// 获取对应Index的对象
	UBaseUserWidget* Widget = nullptr;
	if (InIndex < 0 && CanLastWidget)
	{
		Widget = WidgetArr.Last();
	}
	else
	{
		for (auto& Item : WidgetArr)
		{
			if (Item->UMGIndex == InIndex)
			{
				Widget = Item;
				break;
			}
		}

		if (Widget == nullptr && CanLastWidget) { Widget = WidgetArr.Last(); }
	}

	return Widget;
}

UBaseUserWidget* UBaseUMGManager::CreateUMGWidget(TSubclassOf<UBaseUserWidget> WidgetClass)
{
	FString WidgetName = WidgetClass->GetName();

	UBaseUserWidget* Widget = CreateWidget<UBaseUserWidget>(GetGameInstance(), WidgetClass);
	// 创建对象

	if (Widget == nullptr) { return nullptr; }

	if (!Widgets.Contains(WidgetName))
	{
		// 保存该类最大索引
		if (WidgetIndexMap.Contains(WidgetName)) { WidgetIndexMap[WidgetName] = 0; }
		else { WidgetIndexMap.Emplace(WidgetName, 0); }

		// 创建同类对象池
		FUMGArrayStruct UMGArrayStruct;
		Widgets.Emplace(WidgetName, UMGArrayStruct);
	}
	else
	{
		// 更新该类最大索引
		WidgetIndexMap[WidgetName] = WidgetIndexMap[WidgetName] + 1;
	}

	Widget->OnCreateUMG(WidgetIndexMap[WidgetName]);
	Widgets.Find(WidgetName)->UMGs.Add(Widget);

	return Widget;
}

UBaseUserWidget* UBaseUMGManager::ShowUMGWidget(UBaseUserWidget* TargetWidget, int ZOrder)
{
	if (TargetWidget == nullptr) { return nullptr; }

	// 添加到viewport/设置可见性
	if (!TargetWidget->IsInViewport())
	{
		TargetWidget->AddToViewport(ZOrder);
	}
	else if (TargetWidget->GetVisibility() != ESlateVisibility::Visible)
	{
		TargetWidget->SetVisibility(ESlateVisibility::Visible);
	}

	TargetWidget->OnShowUMG();
	return TargetWidget;
}

UBaseUserWidget* UBaseUMGManager::ShowUMGWidgetByClass(TSubclassOf<UBaseUserWidget> WidgetClass, int InIndex, int ZOrder, bool bAutoCreate)
{
	UBaseUserWidget* Widget = GetUMGWidget(WidgetClass, InIndex, false);
	if (Widget == nullptr)
	{
		if (bAutoCreate) { Widget = CreateUMGWidget(WidgetClass); }
		else { return nullptr; }
	}

	ShowUMGWidget(Widget, ZOrder);
	return Widget;
}

bool UBaseUMGManager::HideUMGWidget(UBaseUserWidget* TargetWidget)
{
	// 设置可见性
	if (TargetWidget != nullptr)
	{
		if (TargetWidget->GetVisibility() != ESlateVisibility::Collapsed)
		{
			TargetWidget->SetVisibility(ESlateVisibility::Collapsed);
			return true;
		}
	}

	return false;
}

bool UBaseUMGManager::HideUMGWidgetByClass(TSubclassOf<UBaseUserWidget> WidgetClass, int InIndex)
{
	UBaseUserWidget* Widget = GetUMGWidget(WidgetClass, InIndex, false);

	return HideUMGWidget(Widget);
}

void UBaseUMGManager::HideAllUMGWidgets()
{
	for (auto& [WidgetName,WidgetArrStruct] : Widgets)
	{
		for (auto& Widget : WidgetArrStruct.UMGs)
		{
			HideUMGWidget(Widget);
		}
	}
}

bool UBaseUMGManager::DestroyUMGWidget(UBaseUserWidget* TargetWidget)
{
	if (TargetWidget != nullptr)
	{
		// 从池中移除
		FString WidgetName = TargetWidget->GetClass()->GetName();
		if (!Widgets.Contains(WidgetName)) { return false; }

		Widgets.Find(WidgetName)->UMGs.Remove(TargetWidget);
		if (Widgets.Find(WidgetName)->UMGs.Num() <= 0) { Widgets.Remove(WidgetName); }

		// 销毁
		if (TargetWidget->IsInViewport())
		{
			HideUMGWidget(TargetWidget);
			TargetWidget->OnDestroyUMG();
			TargetWidget->RemoveFromParent();
			TargetWidget->MarkAsGarbage();
		}
		return true;
	}
	return false;
}

bool UBaseUMGManager::DestroyUMGWidgetByClass(TSubclassOf<UBaseUserWidget> WidgetClass, int InIndex)
{
	UBaseUserWidget* Widget = GetUMGWidget(WidgetClass, InIndex, false);

	return DestroyUMGWidget(Widget);
}

void UBaseUMGManager::DestroyAllUMGWidgets()
{
	for (auto& [WidgetName,WidgetArrStruct] : Widgets)
	{
		for (auto& Widget : WidgetArrStruct.UMGs)
		{
			DestroyUMGWidget(Widget);
		}
	}

	Widgets.Empty();
}
