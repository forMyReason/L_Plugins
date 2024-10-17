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
	// ��ȡ�����
	TSharedPtr<IPropertyHandle> SumPropertyHandle = DetailBuilder.GetProperty((GET_MEMBER_NAME_CHECKED(AMyClass,Sum)));
	TSharedPtr<IPropertyHandle> APropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass,A));
	// TSharedPtr<IPropertyHandle> BPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass,B));
	
	IDetailCategoryBuilder& Category_1 = DetailBuilder.EditCategory(TEXT("Add Item Second"));
	Category_1.AddProperty(SumPropertyHandle);
	
	// ͨ����ȡ������Դ˶���Ӧ����������������
	DetailBuilder.HideProperty(APropertyHandle);

/*
	// ����һ������
	DetailBuilder.HideProperty(Prop);

	// ����һ�����
	DetailBuilder.HideCategory(TEXT("NewCategory"));

	// ��һ�������ƶ���һ�������
	NewCat.AddProperty(Prop);
*/

/*
/////////////////////// Section 2 ///////////////////////
// �����з�����BP_MyClass��ͬʱѡ�У���ϸ�����ġ�NewCategory����ֻ����ʾ��һ����ѡ�е�Actor���ơ�
	// ��DetailBuilder��ȡ��ָ��. TODO:��ָ����ɶ��
	TArray<TWeakObjectPtr<UObject>> Object;
	DetailBuilder.GetObjectsBeingCustomized(Object);
	// ����MyObject��ѡ�񣬲�ǿ��ת����ĵ�һ��ָ��ΪMyClass��
	TWeakObjectPtr<AMyClass> MyObject = Cast<AMyClass>(Object[0].Get());

	// ��ϸ��������½�һ�����
	IDetailCategoryBuilder& Category_2 = DetailBuilder.EditCategory(TEXT("NewCategory"));
	// �Զ�����ʽ
	Category_2.AddCustomRow(FText())
	[
		SNew(STextBlock)
		.Text(FText::FromName(MyObject->GetFName()))
	];
*/

/////////////////////// Section 3 - ʵ���Զ���UI�߼� ///////////////////////
}
















