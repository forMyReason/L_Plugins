// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorExtendTest.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "FEditorExtendTestModule"

void FEditorExtendTestModule::StartupModule()
{
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension("EditHistory", EExtensionHook::After, NULL, FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& Builder)
		{
			Builder.BeginSection("CustomMenu");
			Builder.AddMenuEntry(
				FText::FromString("Menu1"),
				FText::FromString("This is Menu1"),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateRaw(this, &FEditorExtendTestModule::MenuCallback))
			);

			Builder.AddSubMenu(
				FText::FromString("Menu2"),
				FText::FromString("this is menu2"),
				FNewMenuDelegate::CreateRaw(this, &FEditorExtendTestModule::AddSubMenus)
			);

			Builder.AddMenuSeparator();
			Builder.EndSection();
		})
	);

	// TODO:如何使用command list的方式添加菜单？
	
	// 加载LevelEditor模块：通过指定模块名字来加载模块
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	// 将菜单添加到LevelEditorModule
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FEditorExtendTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FEditorExtendTestModule::AddSubMenus(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(
		FText::FromString("SubMenus111111111111111111111111"),
		FText::FromString("This is SubMenus"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FEditorExtendTestModule::MenuCallback))
	);
}

void FEditorExtendTestModule::MenuCallback()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Just a Test"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorExtendTestModule, EditorExtendTest)