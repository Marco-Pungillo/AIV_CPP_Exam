
#pragma region DEPRECATEDAndCOMMENTED

//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Enemy.h"
//
//// Sets default values
//AEnemy::AEnemy()
//{
//	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	this->SetUpCharacterMesh();
//	this->SetUpStateMachine();
//
//
//	//for(EFSMState stateType : States.)
//	//{
//	//	UFSMState* Patrol = NewObject<stateClass>(GetOuter());
//	//	FSM->RegisterState();
//	//}
//
//}
//
//void AEnemy::OnReceiveImpulse()
//{
//
//}
//
//void AEnemy::SetUpCharacterMesh()
//{
//	// I initialize the mesh as the default Unreal Engine Manny, through the blueprint i change it to the Skeletal i want to use
//	USkeletalMeshComponent* characterMesh = this->GetMesh();
//	FString SkeletalMeshPath = "/Script/Engine.SkeletalMesh'/Game/Custom/Enemies/Meshes/Ch50_nonPBR.Ch50_nonPBR'";
//	USkeletalMesh* charMesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
//
//	if (characterMesh && charMesh)
//	{
//		characterMesh->SetSkeletalMeshAsset(charMesh);
//		characterMesh->SetRelativeLocation(FVector(0, 0, -88));
//		characterMesh->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0, 0, -90)));
//	}
//
//
//}
//
//void AEnemy::SetUpStateMachine()
//{
//	FSM = CreateDefaultSubobject<UExamFSM>(TEXT("StateMachine"));
//}
//
//// Called when the game starts or when spawned
//void AEnemy::BeginPlay()
//{
//	Super::BeginPlay();
//
//}
//
//// Called every frame
//void AEnemy::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
#pragma endregion




