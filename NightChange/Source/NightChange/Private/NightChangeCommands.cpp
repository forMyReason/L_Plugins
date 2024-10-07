// Copyright Epic Games, Inc. All Rights Reserved.

#include "NightChangeCommands.h"

#define LOCTEXT_NAMESPACE "FNightChangeModule"

void FNightChangeCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "NightChange", "Execute NightChange action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
