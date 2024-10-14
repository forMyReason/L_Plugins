// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEditorExtendModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void AddSubMenus(FMenuBuilder& Builder);
	void AddToolBarExtension(FToolBarBuilder& ToolBarBuilder);
	void AddMenuBarExtension(FMenuBarBuilder& Builder);
	void MenuBarPullDown(FMenuBuilder& Builder);
	void MenuCallback();
	void BindCommands();
	void LOG_Warning_Action_1();
	void LOG_Warning_Action_2();
	TSharedRef<FExtender> LVCMExtender(const TSharedRef<FUICommandList> PluginCommands, const TArray<AActor*> Actors);

private:
	void RegisterMenus();
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
