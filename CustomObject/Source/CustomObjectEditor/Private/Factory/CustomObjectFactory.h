// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomObjectFactory.generated.h"


UCLASS()
class CUSTOMOBJECTEDITOR_API UCustomObjectFactory : public UFactory
{
	GENERATED_BODY()

public:

	UCustomObjectFactory();

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
