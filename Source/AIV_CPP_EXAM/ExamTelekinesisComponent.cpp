// Fill out your copyright notice in the Description page of Project Settings.


#include "ExamTelekinesisComponent.h"


UExamTelekinesisComponent::UExamTelekinesisComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UExamTelekinesisComponent::SetTelekinesisOrigin(UPrimitiveComponent* origin)
{
	this->TelekinesisOrigin = origin;
}

void UExamTelekinesisComponent::SetStandardTelekinesisChannel(const ECollisionChannel TelekinChannel)
{
	this->StandardTelekinesisChannel = TelekinChannel;
}

void UExamTelekinesisComponent::SetTelekinesisWorld(UWorld* WorldToUse)
{
	this->CurrentWorld = WorldToUse;
}

void UExamTelekinesisComponent::ApplyTelekineticHold(const UWorld* World, const FVector StartPosition, const FVector Direction, const ECollisionChannel TelekinesisChannel)
{
	if (!ControlledBody)
	{
		FVector EndPosition = StartPosition + (Direction * TelekinesisRange);
		FHitResult* TraceResult = TelekinesisRay(World, StartPosition, EndPosition, TelekinesisChannel);

		if (TraceResult)
		{
			UE_LOG(LogTemp, Warning, TEXT("Telekinetic Object Hit"));
			AActor* ControlledActor = TraceResult->GetActor();
			if (ControlledActor)
			{
				ControlledBody = ControlledActor->GetRootComponent();
				ControlledTelekineticActor = Cast<IITelekineticObject>(ControlledActor);
				if (ControlledTelekineticActor)
				{
					ControlledTelekineticActor->OnObjectHold();
				}
				UE_LOG(LogTemp, Warning, TEXT("Actor valid"));
				ControlledBodyOffset = ((ControlledActor->GetActorLocation()) - (GetOwner()->GetActorLocation())).Length();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Telekinetic not Valid"));
			}

		}
	}
}

void UExamTelekinesisComponent::StopTelekineticHold()
{
	if (ControlledBody && ControlledTelekineticActor)
	{
		ControlledTelekineticActor->OnObjectHoldStop();
		ControlledTelekineticActor = nullptr;
		ControlledBody = nullptr;
	}
}

void UExamTelekinesisComponent::TelekineticPush()
{

	if (ControlledBody && ControlledTelekineticActor)
	{
		ControlledBodyOffset += TelekinesisStrenght;
		ControlledBodyOffset = UKismetMathLibrary::Clamp(ControlledBodyOffset, MinControlledBodyOffset, MaxControlledBodyOffset);
		ControlledTelekineticActor->OnObjectPush();
	}
}

void UExamTelekinesisComponent::TelekineticPull()
{
	if (ControlledBody && ControlledTelekineticActor)
	{
		ControlledBodyOffset -= TelekinesisStrenght;
		ControlledBodyOffset = UKismetMathLibrary::Clamp(ControlledBodyOffset, MinControlledBodyOffset, MaxControlledBodyOffset);
		ControlledTelekineticActor->OnObjectPull();
	}
}

void UExamTelekinesisComponent::TelekineticImpulse(const UWorld* World, const FVector StartPosition, const FVector Direction, const ECollisionChannel TelekinesisChannel)
{
	FVector EndPosition = StartPosition + (Direction * TelekinesisRange);
	FHitResult* TraceResult = TelekinesisRay(World, StartPosition, EndPosition, TelekinesisChannel);

	if (TraceResult) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Telekinetic Object Hit"));
		AActor* ControlledActor = TraceResult->GetActor();
		if (ControlledActor)
		{

			IImpulsable* ImpulsedActor = Cast<IImpulsable>(ControlledActor);
			if (ImpulsedActor)
			{

				UPrimitiveComponent* ComponentToPush = TraceResult->GetComponent();
				if (ComponentToPush && (ComponentToPush->Mobility == EComponentMobility::Movable))
				{
					ComponentToPush->SetSimulatePhysics(true);
					ComponentToPush->SetEnableGravity(false);

					// Force Impulse
					FVector Impulse = EndPosition - StartPosition;
					Impulse.Normalize();
					Impulse *= TelekinesisStrenght*TelekinesisStrenght;
					ComponentToPush->AddImpulseAtLocation(Impulse, TraceResult->ImpactPoint);
					ImpulsedActor->OnReceiveImpulse();
					UE_LOG(LogTemp, Warning, TEXT("Impulse made"));

				}

			}

		}
	}
}

//// TO-DO: INSERT GRAPPLING HOOK MECHANIC USING LAUNCH CHARACTER
//void UExamTelekinesisComponent::TelekineticLaunch()
//{
//}


// Called when the game starts
void UExamTelekinesisComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FHitResult* UExamTelekinesisComponent::TelekinesisRay(const UWorld* World, const FVector StartPosition, const FVector EndPosition, const ECollisionChannel TelekinesisChannel)
{
	FHitResult Result;
	FCollisionQueryParams Params;
	FCollisionResponseParams ResponseParams;
	UE_LOG(LogTemp, Warning, TEXT("Ray of telekinesis"));
	if (World != nullptr)
	{

		bool bHasHit = World->LineTraceSingleByChannel(Result, StartPosition, EndPosition, TelekinesisChannel, Params);

		if (bHasHit) 
		{
			DrawDebugLine(World, StartPosition, EndPosition, FColor::Green, false, 2.f, false, 4.f);
			return &Result;
		}
		else 
		{
			DrawDebugLine(World, StartPosition, EndPosition, FColor::Blue, false, 2.f, false, 4.f);
			return nullptr;
		}
	}
	return nullptr;
}


// Called every frame
void UExamTelekinesisComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ControlledBody && TelekinesisCamera)
	{
		FVector locationToReach = UKismetMathLibrary::VLerp(ControlledBody->GetOwner()->GetActorLocation(), TelekinesisOrigin->GetComponentLocation() + TelekinesisCamera->GetForwardVector() * ControlledBodyOffset, DeltaTime);
		ControlledBody->GetOwner()->SetActorLocation(locationToReach);

		FHitResult* TraceResult = TelekinesisRay(CurrentWorld, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() - FVector(0,0,100), StandardTelekinesisChannel);
		if (TraceResult)
		{
			AActor* ControlledActor = TraceResult->GetActor();
			if (ControlledActor && ControlledActor->GetRootComponent() == ControlledBody)
			{
				this->StopTelekineticHold();
			}
		}
	}
}
