// Copyright Epic Games, Inc. All Rights Reserved.

#include "NightChange.h"
#include "NightChangeStyle.h"
#include "NightChangeCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"
#include "Engine/PostProcessVolume.h"
#include "Editor/EditorEngine.h"

static const FName NightChangeTabName("NightChange");

#define LOCTEXT_NAMESPACE "FNightChangeModule"

void FNightChangeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FNightChangeStyle::Initialize();
	FNightChangeStyle::ReloadTextures();

	FNightChangeCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FNightChangeCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FNightChangeModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNightChangeModule::RegisterMenus));
}

void FNightChangeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FNightChangeStyle::Shutdown();

	FNightChangeCommands::Unregister();
}

void FNightChangeModule::PluginButtonClicked()
{
	//FText DialogText = FText::Format(
	//						LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
	//						FText::FromString(TEXT("FNightChangeModule::PluginButtonClicked()")),
	//						FText::FromString(TEXT("NightChange.cpp"))
	//				   );
	//FMessageDialog::Open(EAppMsgType::Ok, DialogText);

	AActor* FoundActor;
	FoundActor = FindActor(ADirectionalLight::StaticClass());

	if (FoundActor)
	{
		ADirectionalLight* Sun = Cast<ADirectionalLight>(FoundActor);
		Sun->GetLightComponent()->SetIntensity(1.0f);
	}

	FoundActor = FindActor(APostProcessVolume::StaticClass());
	APostProcessVolume* ppVol;

	if (!FoundActor)
	{
		FText DialogText = FText::FromString("Actor PostProcessVolume Not Found! Creating One... ");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		FoundActor = AddActor(APostProcessVolume::StaticClass());
	}

	ppVol = Cast<APostProcessVolume>(FoundActor);
	ppVol->Settings.bOverride_AutoExposureBias = true;
	ppVol->Settings.AutoExposureBias = -3.f;
	ppVol->bUnbound = true;
}

void FNightChangeModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FNightChangeCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FNightChangeCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

AActor* FNightChangeModule::FindActor(TSubclassOf<AActor> ActorClass)
{
	TArray<AActor*> FoundActors;
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		UGameplayStatics::GetAllActorsOfClass(World, ActorClass, FoundActors);
		if (FoundActors.Num()>0)
		{
			return FoundActors[0];
		}
	}
	return nullptr;
}

AActor* FNightChangeModule::AddActor(TSubclassOf<AActor> ActorClass)
{
	ULevel* Level = GEditor->GetEditorWorldContext().World()->GetCurrentLevel();
	return GEditor->AddActor(Level, ActorClass, FTransform());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNightChangeModule, NightChange)