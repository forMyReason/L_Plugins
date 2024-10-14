#include "CustomObjectEditor.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_CustomObject.h"

#define LOCTEXT_NAMESPACE "FCustomObjectEditorModule"

void FCustomObjectEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	CustomObjectCategory = AssetTools.RegisterAdvancedAssetCategory(FName("MyCustom"), FText::FromString("My Custom Category"));

	Internal_RegisterTypeActions<FAssetTypeActions_CustomObject>("Custom Object");
}

void FCustomObjectEditorModule::ShutdownModule()
{
	if (const FAssetToolsModule* AssetToolsModulePtr = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools"))
    {
	    IAssetTools& AssetTools = AssetToolsModulePtr->Get();
    	for (const auto& Action : RegisteredAssetTypeActions)
    	{
    		AssetTools.UnregisterAssetTypeActions(Action);
    	}
    }
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FCustomObjectEditorModule, CustomObjectEditor)