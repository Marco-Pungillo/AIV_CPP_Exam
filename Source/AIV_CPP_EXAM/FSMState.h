// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSMState.generated.h"


UCLASS()
class AIV_CPP_EXAM_API UFSMState : public UObject
{
	GENERATED_BODY()
	
public:
	void PrintForTest();

	virtual void OnEnter();
	virtual void OnExit();
	virtual void ExecuteState();

};
