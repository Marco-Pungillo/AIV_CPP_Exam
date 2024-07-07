// Fill out your copyright notice in the Description page of Project Settings.


#include "TelekineticConstraintComponent.h"

UTelekineticConstraintComponent::UTelekineticConstraintComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTelekineticConstraintComponent::SetTelekinesisOwner(UPrimitiveComponent* Owner)
{
	TelekinesisOwner = Owner;
}

void UTelekineticConstraintComponent::TelekineticHold(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel)
{
	FVector EndPosition = StartPosition + (Direction * TelekinesisRange);
	FHitResult* TraceResult = TelekinesisRay(World, StartPosition, EndPosition, TelekinesisChannel);

	if (TraceResult)
	{
		UPrimitiveComponent* ComponentToHold = TraceResult->GetComponent();

		if (ComponentToHold->Mobility == EComponentMobility::Movable) 
		{
			ComponentToHold->SetSimulatePhysics(true);
			ComponentToHold->SetEnableGravity(false);

			SetConstrainedComponents(TelekinesisOwner, NAME_None, ComponentToHold, NAME_None);
		}

	}
}

void UTelekineticConstraintComponent::TelekineticPush(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel)
{
}

void UTelekineticConstraintComponent::TelekineticPull(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel)
{
}

void UTelekineticConstraintComponent::BeginPlay()
{
}

FHitResult* UTelekineticConstraintComponent::TelekinesisRay(UWorld* World, FVector StartPosition, FVector EndPosition, ECollisionChannel TelekinesisChannel)
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

void UTelekineticConstraintComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}
