// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "NightChangeStyle.h"

class FNightChangeCommands : public TCommands<FNightChangeCommands>
{
public:

	FNightChangeCommands()
		: TCommands<FNightChangeCommands>(TEXT("NightChange"), NSLOCTEXT("Contexts", "NightChange", "NightChange Plugin"), NAME_None, FNightChangeStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
