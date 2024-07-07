// Fill out your copyright notice in the Description page of Project Settings.


#include "TelekineticActor.h"

// Sets default values
ATelekineticActor::ATelekineticActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->MeshInstance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	FString MeshPath = "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder";
	USkeletalMesh* BaseMesh = LoadObject<USkeletalMesh>(nullptr, *MeshPath);
	SetRootComponent(MeshInstance);

}

// Called when the game starts or when spawned
void ATelekineticActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATelekineticActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATelekineticActor::OnObjectHold()
{
	MeshInstance->SetMaterial(0, TargetMaterial);
}

void ATelekineticActor::OnObjectHoldStop()
{
	MeshInstance->SetMaterial(0, NoTargetMaterial);
}

void ATelekineticActor::OnObjectPush()
{
	UE_LOG(LogTemp, Warning, TEXT("Interface: Object Pushed"));
}

void ATelekineticActor::OnObjectPull()
{
	UE_LOG(LogTemp, Warning, TEXT("Interface: Object Pulled"));
}

