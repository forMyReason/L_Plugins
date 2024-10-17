#include "MyClassCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "MyClass.h"

TSharedRef<IDetailCustomization> FMyClassCustomization::MakeInstance()
{
	return MakeShareable(new FMyClassCustomization());
}

void FMyClassCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
/////////////////////// Section 1 ///////////////////////
	// 获取类别句柄
	TSharedPtr<IPropertyHandle> SumPropertyHandle = DetailBuilder.GetProperty((GET_MEMBER_NAME_CHECKED(AMyClass,Sum)));
	TSharedPtr<IPropertyHandle> APropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass,A));
	// TSharedPtr<IPropertyHandle> BPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass,B));
	
	IDetailCategoryBuilder& Category_1 = DetailBuilder.EditCategory(TEXT("Add Item Second"));
	Category_1.AddProperty(SumPropertyHandle);
	
	// 通过获取句柄，以此对相应的属性作基础调整
	DetailBuilder.HideProperty(APropertyHandle);

/*
	// 隐藏一个属性
	DetailBuilder.HideProperty(Prop);

	// 隐藏一个类别
	DetailBuilder.HideCategory(TEXT("NewCategory"));

	// 将一个属性移动到一个类别中
	NewCat.AddProperty(Prop);
*/

/*
/////////////////////// Section 2 ///////////////////////
// 场景中放入多个BP_MyClass并同时选中，在细节面板的“NewCategory”下只会显示第一个被选中的Actor名称。
	// 从DetailBuilder获取弱指针. TODO:弱指针是啥？
	TArray<TWeakObjectPtr<UObject>> Object;
	DetailBuilder.GetObjectsBeingCustomized(Object);
	// 设置MyObject，选择，并强制转数组的第一个指针为MyClass类
	TWeakObjectPtr<AMyClass> MyObject = Cast<AMyClass>(Object[0].Get());

	// 在细节面板中新建一个类别
	IDetailCategoryBuilder& Category_2 = DetailBuilder.EditCategory(TEXT("NewCategory"));
	// 自定义样式
	Category_2.AddCustomRow(FText())
	[
		SNew(STextBlock)
		.Text(FText::FromName(MyObject->GetFName()))
	];
*/

/////////////////////// Section 3 - 实现自定义UI逻辑 ///////////////////////
}
















