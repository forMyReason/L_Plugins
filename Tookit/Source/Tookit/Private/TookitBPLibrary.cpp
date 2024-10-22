// Copyright Epic Games, Inc. All Rights Reserved.

#include "TookitBPLibrary.h"
#include "Tookit.h"

UTookitBPLibrary::UTookitBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

/**
 * @brief			添加一个组件到一个AActor对象中
 * @param a						一个AActor对象的指针a
 * @param future_parent			一个USceneComponent对象的指针，用于指定新组件的父组件
 * @param name					新组件的名称
 * @param NewComponentClass		指定新创建组件的类型
 * 
 * @return						返回新创建的组件的指针
 */
UActorComponent* UTookitBPLibrary::AddComponent(AActor* a, USceneComponent *future_parent, FName name, UClass* NewComponentClass)
{
	// 声明一个指针，用于存储新创建的组件
	UActorComponent* retComponent = nullptr;
	if (NewComponentClass)
	{
		UActorComponent* NewComponent = NewObject<UActorComponent>(a, NewComponentClass, name);		// 创建一个新的UActorComponent实例，并存储在NewComponent中
		// 用于存储新创建组件的transform信息
		FTransform CmpTransform;// = dup_source->GetComponentToWorld();
		//NewComponent->AttachToComponent(sc, FAttachmentTransformRules::KeepWorldTransform);
		// Do Scene Attachment if this new Comnponent is a USceneComponent
		if (USceneComponent* NewSceneComponent = Cast<USceneComponent>(NewComponent))
		{
			if (future_parent != 0)
				NewSceneComponent->AttachToComponent(future_parent, FAttachmentTransformRules::KeepWorldTransform);
			else
				// 如果没有指定父组件，则将新组件添加到a的根组件上
				NewSceneComponent->AttachToComponent(a->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
			// 设置新组件的transform信息
			NewSceneComponent->SetComponentToWorld(CmpTransform);
		}
		a->AddInstanceComponent(NewComponent);
		NewComponent->OnComponentCreated();
		NewComponent->RegisterComponent();

		// 更新构造脚本
		a->RerunConstructionScripts();
		retComponent = NewComponent;
	}

	return retComponent;
}

void UTookitBPLibrary::RunFunction(UObject *CDO, UFunction *Function)
{
	// UE_LOG(LogTemp, Warning, TEXT("RunFunction"));
	// We don't run this on the CDO, as bad things could occur!
	UObject *TempObject = NewObject<UObject>(GetTransientPackage(), Cast<UObject>(CDO)->GetClass());
	TempObject->AddToRoot(); // Some Blutility actions might run GC so the TempObject needs to be rooted to avoid getting destroyed
	
	FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "BlutilityAction", "Blutility Action"));
	FEditorScriptExecutionGuard ScriptGuard;
	TempObject->ProcessEvent(Function, nullptr);
	TempObject->RemoveFromRoot();
}