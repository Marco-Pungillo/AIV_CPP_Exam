// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ExamSaveGame.generated.h"


UCLASS()
class AIV_CPP_EXAM_API UExamSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite) 
	FVector PlayerLocation;
	UPROPERTY(BlueprintReadWrite) 
	FRotator PlayerRotation;
	UPROPERTY(BlueprintReadWrite) 
	FVector PlayerScale;

};
