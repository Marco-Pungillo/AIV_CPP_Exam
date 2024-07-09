// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// My Interfaces
#include "Impulsable.h"

// My Components
#include "ExamFSM.h"


#include "Enemy.generated.h"

UCLASS()
class AIV_CPP_EXAM_API AEnemy : public ACharacter, public IImpulsable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	void OnReceiveImpulse() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Machine")
	UExamFSM* FSM;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetUpCharacterMesh();
	void SetUpStateMachine();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
