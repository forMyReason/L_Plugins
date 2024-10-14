#pragma once

#include "CoreMinimal.h"
#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "IAssetTypeActions.h"
#include "Modules/ModuleManager.h"

class FCustomObjectEditorModule : public IModuleInterface
{
    TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;
    EAssetTypeCategories::Type CustomObjectCategory = EAssetTypeCategories::None;
    
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:

    template<class T>
    void Internal_RegisterTypeActions(const FString& Name)
    {
        IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

        const auto Action = MakeShared<T>(CustomObjectCategory, FText::FromString(Name));
        RegisteredAssetTypeActions.Emplace(Action);
        AssetTools.RegisterAssetTypeActions(Action);
    }
};
