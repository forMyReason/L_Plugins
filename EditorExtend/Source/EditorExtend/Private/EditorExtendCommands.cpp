// Fill out your copyright notice in the Description page of Project Settings.

#include "EditorExtendCommands.h"

#define LOCTEXT_NAMESPACE "FEditorExtendCommands"

void FEditorExtendCommands::RegisterCommands()
{
	// ͨ�� UI_COMMAND ע��ָ��
	UI_COMMAND(Action1, "Action1", "Execute Action1", EUserInterfaceActionType::Button, FInputGesture()); //FInputGesture�����֧�ֿ�ݼ���ص�
	UI_COMMAND(Action2, "Action2", "Execute Action2", EUserInterfaceActionType::Button, FInputGesture());
	// ����ע��ָ�������Ҫ��style�е�����һ��
}

#undef LOCTEXT_NAMESPACE
