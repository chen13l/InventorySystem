#include "UI/Widgets/BaseUserWidget.h"

void UBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseUserWidget::OnCreateUMG(int Index)
{
	UMGIndex = Index;
	OnBindLocalEvent();
	OnCreate();
}

void UBaseUserWidget::OnShowUMG()
{
	OnShow();
}

void UBaseUserWidget::OnHideUMG()
{
	OnHide();
}

void UBaseUserWidget::OnDestroyUMG()
{
	OnUnBindLocalEvent();
	OnDestroy();
}

void UBaseUserWidget::OnCreate()
{
}

void UBaseUserWidget::OnShow()
{
}

void UBaseUserWidget::OnHide()
{
}

void UBaseUserWidget::OnDestroy()
{
}

void UBaseUserWidget::OnBindLocalEvent()
{
}

void UBaseUserWidget::OnUnBindLocalEvent()
{
}
