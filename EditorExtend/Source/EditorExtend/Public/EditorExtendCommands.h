// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorExtendStyle.h"

// TODO:模板类
class FEditorExtendCommands : public TCommands<FEditorExtendCommands>
{

public:
    FEditorExtendCommands()
        :TCommands<FEditorExtendCommands>(TEXT("EditorExtend"), NSLOCTEXT("Contexts", "EditorExtend", "EditorExtend Toolbar"), NAME_None, FEditorExtendStyle::GetStyleSetName())
    {}
    // 构造函数：命令上下文名称
    //TEXT("EditorExtend")：命令上下文的名称。
    //NSLOCTEXT("Contexts", "EditorExtend", "EditorExtend Plugin")：命令上下文的本地化文本。
    //NAME_None：命令的名称，这里使用 NAME_None 表示没有特定的名称。
    //FEditorExtendStyle::GetStyleSetName()：从 FEditorExtendStyle 类获取样式集名称。

    // TODO:虚函数：需要被重写，用于注册与插件相关的命令
    virtual void RegisterCommands() override;

public:
	// TODO: copilot的操作，ctrl+->，ctrl+<-？？？？？
    //指令Action1、Action2
	TSharedPtr<FUICommandInfo> Action1;     // 智能指针：指向FUICommandInfo类型对象
    TSharedPtr<FUICommandInfo> Action2;
};