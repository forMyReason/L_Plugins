// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorExtendStyle.h"
#include "EditorExtend.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

// �滻���������ͼ�� IMAGE_BRUSH �������
#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FEditorExtendStyle::StyleInstance = nullptr;

void FEditorExtendStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		// ע����ʽ��
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FEditorExtendStyle::Create()
{
	// �����µ���ʽ��ʵ��
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("EditorExtendStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("EditorExtend")->GetBaseDir() / TEXT("Resources"));		// ͼ��λ��Resource�ļ�������

	// ע��ͼ�꣨��ͼ���Сͼ�꣩��Action1��Action2
	Style->Set("EditorExtendStyle.Action1", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon40x40));
	Style->Set("EditorExtendStyle.Action1.Small", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon16x16));	// ָ��ͼ��Ĵ�С
	Style->Set("EditorExtendStyle.Action2", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon40x40));
	Style->Set("EditorExtendStyle.Action2.Small", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon16x16));

	return Style;
}


void FEditorExtendStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FEditorExtendStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("EditorExtendStyle"));
	return StyleSetName;
}

TSharedPtr<class FSlateStyleSet> FEditorExtendStyle::GetStyleSet()
{
	return TSharedPtr<class FSlateStyleSet>();
}

void FEditorExtendStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		// ��slate��ʼ���󣬻�ȡSlate�ĵ�ǰʵ��
		// ָʾslate����Ⱦ��������¼���������Դ
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

// ���ص�ǰʵ�������ã���������߷��ʷ������
const ISlateStyle& FEditorExtendStyle::Get()
{
	return *StyleInstance;
}