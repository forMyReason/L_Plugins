#include "MyStruct.h"
#include "MyStructCustomization.h"
#include "EditorCustomization.h"

// 将 FMyStructCustomization 与 FMyStruct 绑定起来

IMPLEMENT_GAME_MODULE(FEditorCustomizationModule, EditorCustomization)
// 定义一个模块的接口，并将其注册到引擎的模块系统中。这个宏会创建一个全局的模块实例，并在引擎启动时加载模块，在引擎关闭时卸载模块。

#define LOCTEXT_NAMESPACE "EditorCustomization"

void FEditorCustomizationModule::StartupModule()
{
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    // 注册自定义属性，绑定结构名与自定义类
    PropertyModule.RegisterCustomPropertyTypeLayout
	(
    	FMyStruct::StaticStruct()->GetFName(),
    	// 自定义类实例
    	FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyStructCustomization::MakeInstance)
    );
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FEditorCustomizationModule::ShutdownModule()
{
    FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout("MyStruct");

	PropertyModule.NotifyCustomizationModuleChanged();
}

#undef LOCTEXT_NAMESPACE