// Fill out your copyright notice in the Description page of Project Settings.


#include "ExamTelekinesisComponent.h"


UExamTelekinesisComponent::UExamTelekinesisComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UExamTelekinesisComponent::SetTelekinesisOrigin(UPrimitiveComponent* origin)
{
	TelekinesisOrigin = origin;
}

void UExamTelekinesisComponent::ApplyTelekineticHold(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel)
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
#pragma region ExternalPush
	//FVector EndPosition = StartPosition + (Direction * TelekinesisRange);
//FHitResult* TraceResult = TelekinesisRay(World, StartPosition, EndPosition, TelekinesisChannel);

//if (TraceResult) 
//{
//	UPrimitiveComponent* ComponentToPush = TraceResult->GetComponent();

//	if (ComponentToPush && (ComponentToPush->Mobility == EComponentMobility::Movable))
//	{
//		/*if (GEngine)
//			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FString::Printf(TEXT("%s"), "TELEKINETICOBJECT FOUND"));*/
//		
//		ComponentToPush->SetSimulatePhysics(true);
//		ComponentToPush->SetEnableGravity(false);

//		// Force Impulse
//		FVector Force = EndPosition - StartPosition;
//		Force.Normalize();
//		Force *= TelekinesisStrenght;
//		ComponentToPush->AddForceAtLocation(Force, TraceResult->ImpactPoint);

//	}
//}  
#pragma endregion

	if (ControlledBody && ControlledTelekineticActor)
	{
		ControlledBodyOffset += TelekinesisStrenght;
		ControlledBodyOffset = UKismetMathLibrary::Clamp(ControlledBodyOffset, MinControlledBodyOffset, MaxControlledBodyOffset);
		ControlledTelekineticActor->OnObjectPush();
	}
}

void UExamTelekinesisComponent::TelekineticPull()
{
#pragma region ExternalPull

	//FVector EndPosition = StartPosition + (Direction * TelekinesisRange);
//FHitResult* TraceResult = TelekinesisRay(World, StartPosition, EndPosition, TelekinesisChannel);
//if (TraceResult)
//{
//	UPrimitiveComponent* ComponentToPush = TraceResult->GetComponent();

//	if (ComponentToPush && (ComponentToPush->Mobility == EComponentMobility::Movable))
//	{
//		ComponentToPush->SetSimulatePhysics(true);
//		ComponentToPush->SetEnableGravity(false);
//		FVector Force = StartPosition - EndPosition;
//		Force.Normalize();
//		Force *= TelekinesisStrenght;
//		ComponentToPush->AddForceAtLocation(Force, TraceResult->ImpactPoint);

//	}
//}  
#pragma endregion

	if (ControlledBody && ControlledTelekineticActor)
	{
		ControlledBodyOffset -= TelekinesisStrenght;
		ControlledBodyOffset = UKismetMathLibrary::Clamp(ControlledBodyOffset, MinControlledBodyOffset, MaxControlledBodyOffset);
		ControlledTelekineticActor->OnObjectPull();
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

	}
}
