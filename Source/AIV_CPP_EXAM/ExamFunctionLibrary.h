// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ExamSaveGame.h"
#include "ExamFunctionLibrary.generated.h"


UCLASS()
class AIV_CPP_EXAM_API UExamFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static bool GameSave(AActor* Actor, FString SlotName, int32 UserIndex, FVector Position);
	UFUNCTION(BlueprintCallable)
	static bool GameLoad(AActor* Actor, FString SlotName, int32 UserIndex);
};
