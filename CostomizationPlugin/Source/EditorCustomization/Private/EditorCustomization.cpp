#include "MyStruct.h"
#include "MyStructCustomization.h"
#include "EditorCustomization.h"
#include "MyClass.h"
#include "MyClassCustomization.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

// 用于注册绑定：将 FMyStructCustomization 与 FMyStruct / AMyClass 绑定起来
// 每次更新完细节面板,需要关掉,重新打开,UI刷新

// 定义一个模块的接口，并将其注册到引擎的模块系统中。这个宏会创建一个全局的模块实例，并在引擎启动时加载模块，在引擎关闭时卸载模块。
IMPLEMENT_GAME_MODULE(FEditorCustomizationModule, EditorCustomization)

#define LOCTEXT_NAMESPACE "EditorCustomization"

// 注册自定义属性，绑定结构名与自定义类
// void FEditorCustomizationModule::StartupModule()
// {
//     FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
// 	
//     PropertyModule.RegisterCustomPropertyTypeLayout
// 	(
//     	FMyStruct::StaticStruct()->GetFName(),
//     	// 自定义类实例
//     	FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyStructCustomization::MakeInstance)
//     );
// 	
// 	PropertyModule.NotifyCustomizationModuleChanged();
// }
//
// void FEditorCustomizationModule::ShutdownModule()
// {
// 	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
// 	{
// 		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
// 		
// 		PropertyModule.UnregisterCustomPropertyTypeLayout("MyStruct");
// 		
// 		PropertyModule.NotifyCustomizationModuleChanged();
// 	}
// }

// 自定义细节面板的类
void FEditorCustomizationModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	PropertyModule.RegisterCustomClassLayout
	(
		AMyClass::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FMyClassCustomization::MakeInstance)
	);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FEditorCustomizationModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		
		PropertyModule.UnregisterCustomClassLayout("MyClass");
		
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

#undef LOCTEXT_NAMESPACE