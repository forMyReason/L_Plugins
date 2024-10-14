// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorExtend.h"
#include "EditorExtendStyle.h"
#include "EditorExtendCommands.h"
#include "LevelEditor.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Components/StaticMeshComponent.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "FEditorExtendModule"

void FEditorExtendModule::StartupModule()
{
	FEditorExtendStyle::Initialize();
	FEditorExtendStyle::ReloadTextures();

	FEditorExtendCommands::Register();

	BindCommands();

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this,&FEditorExtendModule::RegisterMenus));

	// MenuExtender
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension("LevelEditor", EExtensionHook::After, NULL, FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& Builder)
		{
			//第一个参数是分隔栏的Hook名，第二参数是分隔栏的显示名称
			Builder.BeginSection("CustomSection", LOCTEXT("CustomArea", "CustomArea"));
			Builder.AddMenuEntry(
				FText::FromString("Menu1"),
				FText::FromString("This is Menu1"),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateRaw(this, &FEditorExtendModule::MenuCallback))
			);
			//创建简单的分割线
			Builder.AddMenuSeparator("SeparatorHook_Name");
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

	// ToolBarExtender
	// TODO：这里的代码没有跑通，所以对于ToolBarMenu，可采用UToolMenu / 新建EditorToolBarButton插件来创建
	// TSharedPtr<FExtender> ToolBarExtender = MakeShareable(new FExtender());
	// ToolBarExtender->AddToolBarExtension("File",EExtensionHook::Before,PluginCommands,FToolBarExtensionDelegate::CreateRaw(this,&FEditorExtendModule::AddToolBarExtension));
	// LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolBarExtender);
	
	// 加载LevelEditor模块：通过指定模块名字来加载模块
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuBarExtender);
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

	
	// Outline和viewport右键菜单拓展
	auto& LVCMExtenders = LevelEditorModule.GetAllLevelViewportContextMenuExtenders();
	LVCMExtenders.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(this, &FEditorExtendModule::LVCMExtender));
}

TSharedRef<FExtender> FEditorExtendModule::LVCMExtender(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> Actors)
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtender> Extender = MakeShareable(new FExtender());
	Extender->AddMenuExtension("ActorAsset", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FEditorExtendModule::AddSubMenus));
	return Extender.ToSharedRef();
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

void FEditorExtendModule::AddToolBarExtension(FToolBarBuilder& ToolBarBuilder)
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("This is toolBar"));
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

// ToolMenu创建ToolBarMenu
void FEditorExtendModule::RegisterMenus()
{
	// TODO：不懂这里为什么分号之后还有大括号？
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	// 注册当前类作为当前Menu的所有者，作用是保证在Unregister的时候自动销毁
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Help");		// LevelEditor下的 Help 菜单
		{
			// 查找Section，如果不存在即创建
			FToolMenuSection& Section = Menu->FindOrAddSection("HelpResources");
			Section.AddMenuEntryWithCommandList(FEditorExtendCommands::Get().Action1, PluginCommands);
		}
	}

	// 顶部播放位置的工具栏
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");		// TODO:像这种名称如何查看？
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("L_Section");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEditorExtendCommands::Get().Action2));
				Entry.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(),"Icons.Save");
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorExtendModule, EditorExtend)