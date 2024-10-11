// Fill out your copyright notice in the Description page of Project Settings.

#include "EditorExtendCommands.h"

#define LOCTEXT_NAMESPACE "FEditorExtendCommands"

void FEditorExtendCommands::RegisterCommands()
{
	// 通过 UI_COMMAND 注册指令
	UI_COMMAND(Action1, "Action1", "Execute Action1", EUserInterfaceActionType::Button, FInputGesture()); //FInputGesture这个是支持快捷键相关的
	UI_COMMAND(Action2, "Action2", "Execute Action2", EUserInterfaceActionType::Button, FInputGesture());
	// 这里注册指令的名称要与style中的名称一致
}

#undef LOCTEXT_NAMESPACE
