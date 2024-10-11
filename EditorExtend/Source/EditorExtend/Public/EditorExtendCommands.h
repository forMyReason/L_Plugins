// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorExtendStyle.h"

// TODO:ģ����
class FEditorExtendCommands : public TCommands<FEditorExtendCommands>
{

public:
    FEditorExtendCommands()
        :TCommands<FEditorExtendCommands>(TEXT("EditorExtend"), NSLOCTEXT("Contexts", "EditorExtend", "EditorExtend Toolbar"), NAME_None, FEditorExtendStyle::GetStyleSetName())
    {}
    // ���캯������������������
    //TEXT("EditorExtend")�����������ĵ����ơ�
    //NSLOCTEXT("Contexts", "EditorExtend", "EditorExtend Plugin")�����������ĵı��ػ��ı���
    //NAME_None����������ƣ�����ʹ�� NAME_None ��ʾû���ض������ơ�
    //FEditorExtendStyle::GetStyleSetName()���� FEditorExtendStyle ���ȡ��ʽ�����ơ�

    // TODO:�麯������Ҫ����д������ע��������ص�����
    virtual void RegisterCommands() override;

public:
	// TODO: copilot�Ĳ�����ctrl+->��ctrl+<-����������
    //ָ��Action1��Action2
	TSharedPtr<FUICommandInfo> Action1;     // ����ָ�룺ָ��FUICommandInfo���Ͷ���
    TSharedPtr<FUICommandInfo> Action2;
};