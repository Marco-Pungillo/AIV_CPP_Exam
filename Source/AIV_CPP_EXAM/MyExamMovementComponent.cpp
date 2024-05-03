// Fill out your copyright notice in the Description page of Project Settings.


#include "MyExamMovementComponent.h"


void UMyExamMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction)
{
	{
		Super::TickComponent(DeltaTime, TickType, TickFunction);
		//Checking if there's need to calculate gravity
		if (!this->bIsGrounded) {
			Velocity += GravityOverride;
		}

		bIsGrounded = false;
		FHitResult Hit;

		// Casting collision trace and check on viable movement
		if (!SafeMoveUpdatedComponent(Velocity, FRotator::ZeroRotator, true, Hit)) {
			FVector CompenetrationCorrection = GetPenetrationAdjustment(Hit);
			ResolvePenetration(CompenetrationCorrection, Hit, UpdatedComponent->GetComponentQuat());
			//Velocity.X = 0;
			//Velocity.Y = 0;
			if (Hit.Normal.Z > 0) {
				Velocity.Z = 0;
				this->bIsGrounded = true;
			}
		}
	}
}

void UMyExamMovementComponent::MoveForwardRight(FVector2D InputAxis)
{
	FVector MoveDirection = UpdatedComponent->GetForwardVector() * InputAxis.X * 500;
	MoveDirection += UpdatedComponent->GetRightVector() * InputAxis.Y * 500;
	MoveDirection.Z = Velocity.Z;
	Velocity = MoveDirection;
}

