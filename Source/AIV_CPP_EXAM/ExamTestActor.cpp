// Fill out your copyright notice in the Description page of Project Settings.


#include "ExamTestActor.h"

// Sets default values
AExamTestActor::AExamTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExamTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExamTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

