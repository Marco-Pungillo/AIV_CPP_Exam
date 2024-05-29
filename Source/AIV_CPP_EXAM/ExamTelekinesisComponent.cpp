// Fill out your copyright notice in the Description page of Project Settings.


#include "ExamTelekinesisComponent.h"

// Sets default values for this component's properties
UExamTelekinesisComponent::UExamTelekinesisComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UExamTelekinesisComponent::TelekineticPush(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel)
{
	FVector EndPosition = StartPosition + (Direction * TelekinesisRange);
	FHitResult* TraceResult = TelekinesisRay(World, StartPosition, EndPosition, TelekinesisChannel);
	UPrimitiveComponent* ComponentToPush = TraceResult->GetComponent();

	if (ComponentToPush)
	{
		ComponentToPush->SetSimulatePhysics(true);
		ComponentToPush->SetEnableGravity(false);
		FVector Force = EndPosition - StartPosition;
		Force.Normalize();
		Force *= TelekinesisStrenght;
		ComponentToPush->AddForceAtLocation(Force, TraceResult->ImpactPoint);

	}
}

void UExamTelekinesisComponent::TelekineticPull(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel)
{
	FVector EndPosition = StartPosition + (Direction * TelekinesisRange);
	FHitResult* TraceResult = TelekinesisRay(World, StartPosition, EndPosition, TelekinesisChannel);
	UPrimitiveComponent* ComponentToPush = TraceResult->GetComponent();

	if (ComponentToPush)
	{
		ComponentToPush->SetSimulatePhysics(true);
		ComponentToPush->SetEnableGravity(false);
		FVector Force = StartPosition - EndPosition;
		Force.Normalize();
		Force *= TelekinesisStrenght;
		ComponentToPush->AddForceAtLocation(Force, TraceResult->ImpactPoint);

	}
}


// Called when the game starts
void UExamTelekinesisComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FHitResult* UExamTelekinesisComponent::TelekinesisRay(UWorld* World, FVector StartPosition, FVector EndPosition, ECollisionChannel TelekinesisChannel)
{
	FHitResult Result;
	FCollisionQueryParams Params;
	FCollisionResponseParams ResponseParams;
	if (World != nullptr)
	{
		DrawDebugLine(World, StartPosition, EndPosition, FColor::Blue, true, 2.f, false, 4.f);

		bool bHasHit = World->LineTraceSingleByChannel(Result, StartPosition, EndPosition, ECollisionChannel::ECC_WorldStatic, Params);

		if (bHasHit) 
		{
			return &Result;
		}
		else 
		{
			return nullptr;
		}
	}
	return nullptr;
}


// Called every frame
void UExamTelekinesisComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
