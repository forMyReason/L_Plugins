// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyCustomObject.generated.h"


UCLASS(Blueprintable, BlueprintType)
class CUSTOMOBJECT_API UMyCustomObject : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float SomeFloat;

	UPROPERTY(EditAnywhere)
	bool bMyBool;
};
