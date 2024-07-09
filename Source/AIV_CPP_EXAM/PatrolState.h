// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMState.h"
#include "PatrolState.generated.h"

UCLASS()
class AIV_CPP_EXAM_API UPatrolState : public UFSMState
{
	GENERATED_BODY()


public:
	/*UPatrolState();*/

	// Ereditato tramite UFSMState
	virtual void OnEnter() override;

	virtual void OnExit() override;

	virtual void ExecuteState() override;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TargetPointsNumber = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> PatrolPoints;
};
