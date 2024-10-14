#pragma once

#include "AssetTypeActions_Base.h"
#include "MyCustomObject.h"

class FAssetTypeActions_CustomObject : public FAssetTypeActions_Base
{
private:
	const EAssetTypeCategories::Type AssetCategory;
	const FText Name;
	const FColor Color;
	
public:
	explicit FAssetTypeActions_CustomObject(EAssetTypeCategories::Type AssetCategory, const FText& Name, const FColor& Color = FColor::Black)
		: AssetCategory(AssetCategory), Name(Name), Color(Color)
	{		
	}

	virtual FText GetName() const override { return Name; }
	virtual FColor GetTypeColor() const override { return Color; }
	virtual UClass* GetSupportedClass() const override { return UMyCustomObject::StaticClass(); }
	virtual uint32 GetCategories() override { return AssetCategory; }
};
