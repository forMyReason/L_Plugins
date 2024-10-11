// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorExtend.h"
#include "EditorExtendStyle.h"
#include "EditorExtendCommands.h"
#include "LevelEditor.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Components/StaticMeshComponent.h"

#define LOCTEXT_NAMESPACE "FEditorExtendModule"

void FEditorExtendModule::StartupModule()
{
	FEditorExtendStyle::Initialize();
	FEditorExtendStyle::ReloadTextures();

	FEditorExtendCommands::Register();

	BindCommands();

	// MenuExtender
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension("EditHistory", EExtensionHook::After, NULL, FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& Builder)
		{
			Builder.BeginSection("CustomMenu");
			Builder.AddMenuEntry(
				FText::FromString("Menu1"),
				FText::FromString("This is Menu1"),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateRaw(this, &FEditorExtendModule::MenuCallback))
			);

			Builder.AddSubMenu(
				FText::FromString("Menu2"),
				FText::FromString("this is menu2"),
				FNewMenuDelegate::CreateRaw(this, &FEditorExtendModule::AddSubMenus)
			);
			Builder.EndSection();
		})
	);

	// MenuBarExtender
	TSharedPtr<FExtender> MenuBarExtender = MakeShareable(new FExtender());
	MenuBarExtender->AddMenuBarExtension("Help", EExtensionHook::After, PluginCommands, FMenuBarExtensionDelegate::CreateRaw(this, &FEditorExtendModule::AddMenuBarExtension));
	// ������һ��ί��ʵ����������Ӧ��Ӳ˵���չ������
	// this��ָ��ǰFEditorExtendModuleʵ����ָ��
	// &FEditorExtendModule::AddMenuBarExtension��ָ���Ա������ָ�룬������Ӧ�˵���չ


	// ����LevelEditorģ�飺ͨ��ָ��ģ������������ģ��
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	// ���˵���ӵ�LevelEditorModule
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuBarExtender);
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FEditorExtendModule::ShutdownModule()
{
	FEditorExtendStyle::Shutdown();
	FEditorExtendCommands::Unregister();
}

void FEditorExtendModule::AddMenuBarExtension(FMenuBarBuilder& Builder)
{
	Builder.AddPullDownMenu(
		LOCTEXT("PullMenu", "AdvancedMenu"),			
		LOCTEXT("PullMenu Tips", "Advanced Menu Tips"),
		FNewMenuDelegate::CreateRaw(this, &FEditorExtendModule::MenuBarPullDown)
	);
}

//void FEditorExtendModule::MenuBarPullDown(FMenuBuilder& Builder)
//{
//	Builder.AddMenuEntry(
//		FText::FromString("SubMenu_1"),
//		FText::FromString("This is SubMenu_1"),
//		//FSlateIcon(),		// ����iconΪ��
//		FSlateIcon(FAppStyle::GetAppStyleSetName(),"Icons.Save"),		// ʹ����������ͼ��
//		FUIAction(FExecuteAction::CreateRaw(this, &FEditorExtendModule::MenuCallback))
//	);
//}

//TODO:��Ҫ�Զ���ͼ�꼯���Զ�����ʽ��+ͼ������
//FSlateIcon(MyCustomStyleSetName, "MyCustomIconName");
void FEditorExtendModule::MenuBarPullDown(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(
		FEditorExtendCommands::Get().Action1,
		NAME_None,
		FText::FromString("SubMenu_1"),
		FText::FromString("This is SubMenu_1"),
		FSlateIcon(FEditorExtendStyle::GetStyleSetName(), "EditorExtendStyle.Action1")  // ������ Action1 ͼ��
	);
}

void FEditorExtendModule::AddSubMenus(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(
		FText::FromString("SubMenu"),
		FText::FromString("This is SubMenus"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FEditorExtendModule::MenuCallback))
	);
}

void FEditorExtendModule::MenuCallback()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Just a SubMenu"));
}

// ��ָ��
void FEditorExtendModule::BindCommands()
{
	PluginCommands = MakeShareable(new FUICommandList);

	// ���û����涯��ӳ�䵽�����ִ�к���
	PluginCommands->MapAction(
		FEditorExtendCommands::Get().Action1,		// TSharedPtr:UICommandInfo
		FExecuteAction::CreateRaw(this, &FEditorExtendModule::LOG_Warning_Action_1),		// FExecuteAction:Execution Founction
		FCanExecuteAction(),		// FCanExecuteAction : Execution Condition : ����ΪĬ��ֵ����ʾ���������ǿ��Ա�ִ��
		EUIActionRepeatMode::RepeatDisabled
	);

	PluginCommands->MapAction(
		FEditorExtendCommands::Get().Action2,
		FExecuteAction::CreateRaw(this, &FEditorExtendModule::LOG_Warning_Action_2),
		FCanExecuteAction()
	);
}

void FEditorExtendModule::LOG_Warning_Action_1()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("LOG_Warning_Action_1"));
}

void FEditorExtendModule::LOG_Warning_Action_2()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("LOG_Warning_Action_2"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorExtendModule, EditorExtend)