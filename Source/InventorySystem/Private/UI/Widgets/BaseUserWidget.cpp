#include "UI/Widgets/BaseUserWidget.h"

void UBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GEngine->GameViewport->Viewport->ViewportResizedEvent.AddUObject(this, &ThisClass::OnViewportChangedCallback);
}

void UBaseUserWidget::OnViewportChangedCallback(FViewport* Viewport, uint32 Param)
{
	OnViewportChanged.Broadcast(Viewport->GetSizeXY());
}

void UBaseUserWidget::SetWidgetController(UObject* NewWidgetController)
{
	WidgetController = NewWidgetController;
	OnWidgetControllerSet();
}

void UBaseUserWidget::OnWidgetControllerSet_Implementation()
{
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
