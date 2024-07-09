#pragma region DEPRECATEDAndCOMMENTED

//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "ExamFSM.h"
//
//// Sets default values for this component's properties
//UExamFSM::UExamFSM()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	UPatrolState* PatrolState = NewObject<UPatrolState>();
//	RegisterState(EFSMState::Patrol, PatrolState);
//	SetInitialState(EFSMState::Patrol);
//	CurrentState = InitialState;
//}
//
//
//
//// Called when the game starts
//void UExamFSM::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//}
//
//
//// Called every frame
//void UExamFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	UFSMState* PlayingState = States[CurrentState];
//	if (States.Contains(CurrentState) && PlayingState)
//	{
//		// Execute State behavior (State is an object)
//		PlayingState->PrintForTest();
//
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Not Working"));
//	}
//
//}
//
//#pragma region StateManagement
//
//void UExamFSM::RegisterState(EFSMState StateType, UFSMState* State)
//{
//	States.Add(StateType, State);
//}
//
//void UExamFSM::ChangeState(EFSMState nextState)
//{
//	States[CurrentState]->OnExit();
//	CurrentState = nextState;
//	States[CurrentState]->OnEnter();
//}
//
//void UExamFSM::SetInitialState(EFSMState NewInitialState)
//{
//	this->InitialState = NewInitialState;
//}
//
//
//#pragma endregion


#pragma endregion

