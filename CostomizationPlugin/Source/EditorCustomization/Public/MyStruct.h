#pragma once

#include "MyStruct.generated.h"

USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Set Name")
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Analyzed Name")
	FString Prefix;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Analyzed Name")
	FString BaseName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Analyzed Name")
	FString Suffix;
};