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
	void MenuCallback();
	void BindCommands();
	void LOG_Warning_Action_1();
	void LOG_Warning_Action_2();
	void AddMenuBarExtension(FMenuBarBuilder& Builder);
	void MenuBarPullDown(FMenuBuilder& Builder);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
