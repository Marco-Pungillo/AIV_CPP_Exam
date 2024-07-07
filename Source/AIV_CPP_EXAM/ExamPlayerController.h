// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"


#include "ExamPlayerController.generated.h"

//Forward Declaration
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class AIV_CPP_EXAM_API AExamPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AExamPlayerController();

};
