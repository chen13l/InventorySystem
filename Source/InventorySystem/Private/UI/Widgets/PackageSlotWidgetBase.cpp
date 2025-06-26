#include "UI/Widgets/PackageSlotWidgetBase.h"

bool UPackageSlotWidgetBase::SetIconTexture(UTexture2D* Texture)
{
	if (Texture == nullptr && Icon == nullptr) { return false; }
	StartChanging();
	Icon->SetBrushResourceObject(Texture);
	FinishChanged();

	return true;
}

void UPackageSlotWidgetBase::StartChanging()
{
	InvalidationBox->SetCanCache(false);
}

void UPackageSlotWidgetBase::FinishChanged()
{
	InvalidationBox->SetCanCache(true);
}
