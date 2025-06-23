#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category="BaseUserWidget")
	int UMGIndex = 0;

	void OnCreateUMG(int Index = 0);
	void OnShowUMG();
	void OnHideUMG();
	void OnDestroyUMG();
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* NewWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
protected:
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
