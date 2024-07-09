#pragma region DEPRECATEDACOMMENTED
//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//
//// My Components
//#include "FSMState.h"
//#include "PatrolState.h"
//
//
//#include "ExamFSM.generated.h"
//
//UENUM(BlueprintType)
//enum class EFSMState
//{
//	Patrol,
//	Chase,
//};
//
//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
//class AIV_CPP_EXAM_API UExamFSM : public UActorComponent
//{
//	GENERATED_BODY()
//
//public:
//	// Sets default values for this component's properties
//	UExamFSM();
//
//	void RegisterState(EFSMState StateType, UFSMState* State);
//
//protected:
//
//	EFSMState InitialState;
//
//	EFSMState CurrentState;
//	TMap<EFSMState, UFSMState*> States;
//
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//
//public:
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//	UFUNCTION(BlueprintCallable)
//	void ChangeState(EFSMState NextState);
//	UFUNCTION(BlueprintCallable)
//	void SetInitialState(EFSMState NewInitialState);
//};
#pragma endregion

