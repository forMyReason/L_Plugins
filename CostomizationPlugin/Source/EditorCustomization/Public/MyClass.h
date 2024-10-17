// Plugins/CustomizationPlugin/Source/EditorCustomization/Public/MyClass.h

#pragma once

#include "MyClass.generated.h"

UCLASS(Blueprintable)
class AMyClass : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Add Items")
	float A;

	UPROPERTY(EditAnywhere, Category = "Add Items")
	float B;

	UPROPERTY(EditAnywhere, Category = "Result")
	float Sum;
};