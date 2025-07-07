#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/UIInterfaces.h"
#include "BaseUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnViewportChangedSignature, FVector2D, NewSize);

UCLASS()
class INVENTORYSYSTEM_API UBaseUserWidget : public UUserWidget, public IUIInterfaces
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnViewportChangedSignature OnViewportChanged;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="BaseUserWidget")
	int UMGIndex = 0;

	void OnCreateUMG(int Index = 0);
	void OnShowUMG();
	void OnHideUMG();
	void OnDestroyUMG();
	virtual int GetUMGIndex_Implementation() override { return UMGIndex; }

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* NewWidgetController);

	UFUNCTION(BlueprintImplementableEvent)
	void SetRootSize_Implementation(FVector2D InNewSize) override;

protected:
	void OnViewportChangedCallback(FViewport* Viewport, uint32 Param);

	// bind callbacks
	UFUNCTION(BlueprintNativeEvent)
	void OnWidgetControllerSet();

	virtual void OnCreate();
	virtual void OnShow();
	virtual void OnHide();
	virtual void OnDestroy();

	virtual void OnBindLocalEvent();
	virtual void OnUnBindLocalEvent();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
};
