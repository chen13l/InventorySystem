﻿#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnViewportChangedSignature, FVector2D, NewSize);

UCLASS()
class INVENTORYSYSTEM_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnViewportChangedSignature OnViewportChanged;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="BaseUserWidget")
	int UMGIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	void OnCreateUMG(int Index = 0);
	void OnShowUMG();
	void OnHideUMG();
	void OnDestroyUMG();

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* NewWidgetController);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetRootSize(FVector2D NewSize);

protected:
	void OnViewportChangedCallback( FViewport* Viewport, uint32 Param);
	
	// bind callbacks
	UFUNCTION(BlueprintNativeEvent)
	void OnWidgetControllerSet();

	virtual void OnCreate();
	virtual void OnShow();
	virtual void OnHide();
	virtual void OnDestroy();

	virtual void OnBindLocalEvent();
	virtual void OnUnBindLocalEvent();

};
