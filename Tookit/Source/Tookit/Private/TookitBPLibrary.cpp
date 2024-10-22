// Copyright Epic Games, Inc. All Rights Reserved.

#include "TookitBPLibrary.h"
#include "Tookit.h"

UTookitBPLibrary::UTookitBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

/**
 * @brief			���һ�������һ��AActor������
 * @param a						һ��AActor�����ָ��a
 * @param future_parent			һ��USceneComponent�����ָ�룬����ָ��������ĸ����
 * @param name					�����������
 * @param NewComponentClass		ָ���´������������
 * 
 * @return						�����´����������ָ��
 */
UActorComponent* UTookitBPLibrary::AddComponent(AActor* a, USceneComponent *future_parent, FName name, UClass* NewComponentClass)
{
	// ����һ��ָ�룬���ڴ洢�´��������
	UActorComponent* retComponent = nullptr;
	if (NewComponentClass)
	{
		UActorComponent* NewComponent = NewObject<UActorComponent>(a, NewComponentClass, name);		// ����һ���µ�UActorComponentʵ�������洢��NewComponent��
		// ���ڴ洢�´��������transform��Ϣ
		FTransform CmpTransform;// = dup_source->GetComponentToWorld();
		//NewComponent->AttachToComponent(sc, FAttachmentTransformRules::KeepWorldTransform);
		// Do Scene Attachment if this new Comnponent is a USceneComponent
		if (USceneComponent* NewSceneComponent = Cast<USceneComponent>(NewComponent))
		{
			if (future_parent != 0)
				NewSceneComponent->AttachToComponent(future_parent, FAttachmentTransformRules::KeepWorldTransform);
			else
				// ���û��ָ������������������ӵ�a�ĸ������
				NewSceneComponent->AttachToComponent(a->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
			// �����������transform��Ϣ
			NewSceneComponent->SetComponentToWorld(CmpTransform);
		}
		a->AddInstanceComponent(NewComponent);
		NewComponent->OnComponentCreated();
		NewComponent->RegisterComponent();

		// ���¹���ű�
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