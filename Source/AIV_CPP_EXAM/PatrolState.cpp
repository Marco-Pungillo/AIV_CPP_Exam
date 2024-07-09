// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolState.h"


void UPatrolState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Patrol"));
}

void UPatrolState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Patrol"));
}

void UPatrolState::ExecuteState()
{
	UE_LOG(LogTemp, Warning, TEXT("Currently Patrolling"));
}
