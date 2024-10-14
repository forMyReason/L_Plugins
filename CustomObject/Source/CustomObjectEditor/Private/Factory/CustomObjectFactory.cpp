// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomObjectFactory.h"
#include "MyCustomObject.h"

UCustomObjectFactory::UCustomObjectFactory()
{
	SupportedClass = UMyCustomObject::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UCustomObjectFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	UMyCustomObject* ProxyObj = NewObject<UMyCustomObject>(InParent, SupportedClass, InName, Flags);
	return ProxyObj;
}
