// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorExtendStyle.h"
#include "EditorExtend.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

// 替换，否则后面图标 IMAGE_BRUSH 会出问题
#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FEditorExtendStyle::StyleInstance = nullptr;

void FEditorExtendStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		// 注册样式集
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FEditorExtendStyle::Create()
{
	// 创建新的样式集实例
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("EditorExtendStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("EditorExtend")->GetBaseDir() / TEXT("Resources"));		// 图标位于Resource文件夹下面

	// 注册图标（大图标和小图标）：Action1、Action2
	Style->Set("EditorExtendStyle.Action1", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon40x40));
	Style->Set("EditorExtendStyle.Action1.Small", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon16x16));	// 指定图标的大小
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
		// 在slate初始化后，获取Slate的当前实例
		// 指示slate的渲染器组件重新加载纹理资源
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

// 返回当前实例的引用，允许调用者访问风格数据
const ISlateStyle& FEditorExtendStyle::Get()
{
	return *StyleInstance;
}