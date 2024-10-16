#include "MyStructCustomization.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "MyStruct.h"

TSharedRef<IPropertyTypeCustomization> FMyStructCustomization::MakeInstance()
{
	return MakeShareable(new FMyStructCustomization());
}

void FMyStructCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	HeaderRow.NameContent()[PropertyHandle->CreatePropertyNameWidget()];
	// 获取Name属性的句柄
	TSharedPtr<IPropertyHandle> NamePropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyStruct,Name));
	// 检查句柄是否为空
	check(NamePropertyHandle.IsValid());
	// 构建slate
	// 在HeaderRow下看上去有点奇怪的代码是UE中的Slate框架代码。它们虽然奇怪但并不难理解，却也不是三言两语能够解释清楚的东西。
	// 如果你此前从未见过它们，不妨Google一下“Slate”进一步学习相关知识。
	HeaderRow
		// 每一个默认的content都分为NameContent和 Value Content
		// NameContent和ValueContent之间由一道分隔线区分：
		// [ Struct Value Category      ]
		// [ NameContent | ValueContent ] ( HeaderRow )
		// [      ...    |      ...     ] ( ChildrenRow )
	.NameContent()[PropertyHandle->CreatePropertyNameWidget()]
	.ValueContent()
	.HAlign(HAlign_Fill)
	[
		SNew(SBox)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoWidth()
			.Padding(5.0f,0.0f)
			[
				NamePropertyHandle->CreatePropertyNameWidget()
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				NamePropertyHandle->CreatePropertyValueWidget()
			]
		]
	];
}

void FMyStructCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	TSharedPtr<IPropertyHandle> PrefixPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyStruct, Prefix));
	TSharedPtr<IPropertyHandle> BaseNamePropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyStruct, BaseName));
	TSharedPtr<IPropertyHandle> SuffixPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyStruct, Suffix));

	check(PrefixPropertyHandle.IsValid() && BaseNamePropertyHandle.IsValid() && SuffixPropertyHandle.IsValid());
	
	ChildBuilder.AddCustomRow(FText())
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.Padding(5.0f, 0.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[PrefixPropertyHandle->CreatePropertyNameWidget()]
			+ SVerticalBox::Slot()
			[PrefixPropertyHandle->CreatePropertyValueWidget()]
		]
		+ SHorizontalBox::Slot()
		.Padding(5.0f, 0.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[BaseNamePropertyHandle->CreatePropertyNameWidget()]
			+ SVerticalBox::Slot()
			[BaseNamePropertyHandle->CreatePropertyValueWidget()]
		]
		+ SHorizontalBox::Slot()
		.Padding(5.0f, 0.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[SuffixPropertyHandle->CreatePropertyNameWidget()]
			+ SVerticalBox::Slot()
			[SuffixPropertyHandle->CreatePropertyValueWidget()]
		]
	];
	// UE_LOG(LogTemp, Warning, TEXT("%s - The children customization is called"), ANSI_TO_TCHAR(__FU  NCTION__));
}