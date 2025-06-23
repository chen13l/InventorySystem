#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BaseUMGManager.generated.h"

class UBaseUserWidget;

USTRUCT(BlueprintType)
struct FUMGArrayStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UBaseUserWidget*> UMGs;
};

UCLASS()
class INVENTORYSYSTEM_API UBaseUMGManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TMap<FString, FUMGArrayStruct> Widgets;
	UPROPERTY()
	TMap<FString, int> WidgetIndexMap;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/* Get Widget */
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	UBaseUserWidget* GetUMGWidget(TSubclassOf<UBaseUserWidget> WidgetClass, int InIndex = -1, bool CanLastWidget = true);

	/* Create Widget */
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	UBaseUserWidget* CreateUMGWidget(TSubclassOf<UBaseUserWidget> WidgetClass);

	/* Show Widget */
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	UBaseUserWidget* ShowUMGWidget(UBaseUserWidget* TargetWidget, int ZOrder);
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	UBaseUserWidget* ShowUMGWidgetByClass(TSubclassOf<UBaseUserWidget> WidgetClass, int ZOrder, int InIndex = -1, bool bAutoCreate = true);

	/* Hide Widget */
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	bool HideUMGWidget(UBaseUserWidget* TargetWidget);
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	bool HideUMGWidgetByClass(TSubclassOf<UBaseUserWidget> WidgetClass, int InIndex = -1);
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	void HideAllUMGWidgets();

	/* Destroy Widget */
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	bool DestroyUMGWidget(UBaseUserWidget* TargetWidget);
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	bool DestroyUMGWidgetByClass(TSubclassOf<UBaseUserWidget> WidgetClass, int InIndex = -1);
	UFUNCTION(BlueprintCallable, Category="BaseUMGManager")
	void DestroyAllUMGWidgets();
};
