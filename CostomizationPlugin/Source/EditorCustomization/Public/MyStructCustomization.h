#pragma once

class FMyStructCustomization : public IPropertyTypeCustomization
{
public:
	// MakeInstance is a auxiliary Founction for Initializing an instance of our custome class repidly.
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	// CustomizeHeader 用于自定义Header
	virtual void CustomizeHeader(
		TSharedRef<IPropertyHandle> PropertyHandle,
		FDetailWidgetRow& HeaderRow,
		IPropertyTypeCustomizationUtils& CustomizationUtils) override;

	// CustomizeChildren 用于自定义Children
	virtual void CustomizeChildren(
		TSharedRef<IPropertyHandle> PropertyHandle,
		IDetailChildrenBuilder& ChildBuilder,
		IPropertyTypeCustomizationUtils& CustomizationUtils) override;
};
