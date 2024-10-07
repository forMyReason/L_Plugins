// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPlugins.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Misc/MessageDialog.h"


#define LOCTEXT_NAMESPACE "FMyPluginsModule"

void FMyPluginsModule::StartupModule()
{
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension("LevelEditor", EExtensionHook::After, NULL, FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& Builder)
		{
			Builder.BeginSection("CustomMenu");
			Builder.AddMenuEntry(
				FText::FromString("Menu1"), // �˵�����
				FText::FromString("This is Menu1"), // �˵���ʾ
				FSlateIcon(), // �˵�ͼ��
				FUIAction(FExecuteAction::CreateRaw(this, &FMyPluginsModule::MenuCallback)) // �˵��ص�����
			);

			Builder.AddSubMenu(
				FText::FromString("Menu2"),// �˵�����
				FText::FromString("This is Menu2"),// �˵���ʾ
				FNewMenuDelegate::CreateRaw(this, &FMyPluginsModule::AddSubMenus) // �����Ӳ˵���ί��
			);
			Builder.EndSection();//�����˵�����
		})
	);

	MenuExtender->AddMenuBarExtension("Help", EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateLambda([this](FMenuBarBuilder& Builder)
		{
			Builder.AddPullDownMenu(
				FText::FromString("Menu2"),// �˵�����
				FText::FromString("This is Menu2"),// �˵���ʾ
				FNewMenuDelegate::CreateRaw(this, &FMyPluginsModule::AddSubMenus) // �����Ӳ˵���ί��
			);
		})
	);

	//����LevelEditorģ��
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor"); // ����LevelEditorģ��
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender); // �����չ
}


void FMyPluginsModule::AddSubMenus(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(
		FText::FromString("SubMenu1"),
		FText::FromString("This is SubMenu1"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FMyPluginsModule::MenuCallback))
	);
	Builder.AddMenuEntry(
		FText::FromString("SubMenu2"),
		FText::FromString("This is SubMenu2"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FMyPluginsModule::MenuCallback))
	);
}

void FMyPluginsModule::MenuCallback()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Just a test!"));
}


void FMyPluginsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyPluginsModule, MyPlugins)