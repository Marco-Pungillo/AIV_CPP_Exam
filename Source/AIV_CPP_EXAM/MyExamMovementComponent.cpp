// Fill out your copyright notice in the Description page of Project Settings.


#include "MyExamMovementComponent.h"

//NOT USED
void UMyExamMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction)
{
	Super::TickComponent(DeltaTime, TickType, TickFunction);
	//Checking if there's need to calculate gravity
	if (!this->bIsGrounded) {
		Velocity += GravityOverride;
	}
	if (this->bCannotMoveForward && Velocity.X < 0) {
		this->bCannotMoveForward = false;
	}
	if (this->bCannotMoveBackward && Velocity.X > 0) {
		this->bCannotMoveBackward = false;
	}
	if (this->bCannotMoveRight && Velocity.Y < 0) {
		this->bCannotMoveRight = false;
	}
	if (this->bCannotMoveLeft && Velocity.Y > 0) {
		this->bCannotMoveLeft = false;
	}
	FHitResult Hit;

	// Casting collision trace and check on viable movement
	if (!SafeMoveUpdatedComponent(Velocity, FRotator::ZeroRotator, true, Hit)) {
		FVector CompenetrationCorrection = GetPenetrationAdjustment(Hit);
		ResolvePenetration(CompenetrationCorrection, Hit, UpdatedComponent->GetComponentQuat());
		if (Hit.Normal.Z > 0) {
			Velocity.Z = 0;
			this->bIsGrounded = true;
		}
		if (Hit.Normal.X < 0) {
			//Velocity.X = 0;
			bCannotMoveForward = true;
		}
		if (Hit.Normal.X > 0) {
			//Velocity.X = 0;
			bCannotMoveBackward = true;
		}
		if (Hit.Normal.Y < 0) {
			//Velocity.Y = 0;
			bCannotMoveRight = true;
		}
		if (Hit.Normal.Y > 0) {
			//Velocity.Y = 0;
			bCannotMoveLeft = true;
		}
	} else {
		bIsGrounded = false;
		bCannotMoveForward	= false;
		bCannotMoveBackward	= false;
		bCannotMoveRight	= false;
		bCannotMoveLeft		= false;
	}
	Velocity.X = 0;
	Velocity.Y = 0;
	/*CurrentAccelleration = { 0,0,0 };*/
}

void UMyExamMovementComponent::MoveForwardRight(const FVector2D InputAxis)
{
	MoveForward(InputAxis.X);
	MoveRight(InputAxis.Y);
}

void UMyExamMovementComponent::MoveForward(const float Input)
{
	FVector MoveDirection = UpdatedComponent->GetForwardVector() * Input * movementSpeed;
	MoveDirection.Z = Velocity.Z;
	if ((this->bCannotMoveForward && MoveDirection.X > 0))
	{
		MoveDirection.X = 0;
	}
	if ((this->bCannotMoveBackward && MoveDirection.X < 0))
	{
		MoveDirection.X = 0;
	}
	this->CurrentAccelleration = Velocity - MoveDirection;
	this->Velocity += MoveDirection;
	this->Velocity.X = FMath::Clamp(this->Velocity.X, -movementMaxSpeed, movementMaxSpeed);
}

void UMyExamMovementComponent::MoveRight(const float Input)
{
	FVector MoveDirection = UpdatedComponent->GetRightVector() * Input * movementSpeed;
	MoveDirection.Z = Velocity.Z;
	if ((this->bCannotMoveRight && MoveDirection.Y > 0))
	{
		MoveDirection.Y = 0;
	}
	if ((this->bCannotMoveLeft && MoveDirection.Y < 0))
	{
		MoveDirection.Y = 0;
	}
	this->CurrentAccelleration = Velocity - MoveDirection;
	this->Velocity += MoveDirection;
	this->Velocity.Y = FMath::Clamp(this->Velocity.Y, -movementMaxSpeed, movementMaxSpeed);

}

const bool UMyExamMovementComponent::IsFalling()
{
	return !(this->bIsGrounded);
}

void UMyExamMovementComponent::Rotate(FVector2D RotationAxis)
{
	UpdatedComponent->SetRelativeRotation(FRotator(0, RotationAxis.X, 0));
}


