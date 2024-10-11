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
	// 创建了一个委托实例，用于相应添加菜单扩展的请求
	// this：指向当前FEditorExtendModule实例的指针
	// &FEditorExtendModule::AddMenuBarExtension：指向成员函数的指针，用于相应菜单扩展


	// 加载LevelEditor模块：通过指定模块名字来加载模块
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	// 将菜单添加到LevelEditorModule
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
//		//FSlateIcon(),		// 设置icon为空
//		FSlateIcon(FAppStyle::GetAppStyleSetName(),"Icons.Save"),		// 使用引擎内置图标
//		FUIAction(FExecuteAction::CreateRaw(this, &FEditorExtendModule::MenuCallback))
//	);
//}

//TODO:需要自定义图标集：自定义样式集+图标名称
//FSlateIcon(MyCustomStyleSetName, "MyCustomIconName");
void FEditorExtendModule::MenuBarPullDown(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(
		FEditorExtendCommands::Get().Action1,
		NAME_None,
		FText::FromString("SubMenu_1"),
		FText::FromString("This is SubMenu_1"),
		FSlateIcon(FEditorExtendStyle::GetStyleSetName(), "EditorExtendStyle.Action1")  // 关联到 Action1 图标
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

// 绑定指令
void FEditorExtendModule::BindCommands()
{
	PluginCommands = MakeShareable(new FUICommandList);

	// 将用户界面动作映射到具体的执行函数
	PluginCommands->MapAction(
		FEditorExtendCommands::Get().Action1,		// TSharedPtr:UICommandInfo
		FExecuteAction::CreateRaw(this, &FEditorExtendModule::LOG_Warning_Action_1),		// FExecuteAction:Execution Founction
		FCanExecuteAction(),		// FCanExecuteAction : Execution Condition : 被设为默认值，表示该命令总是可以被执行
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