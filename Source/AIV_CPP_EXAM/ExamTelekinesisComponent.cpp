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
			ControlledBody = TraceResult->GetActor()->GetRootComponent();
			AActor* ControlledActor = ControlledBody->GetOwner();

			if (ControlledActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Actor valid"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Telekinetic not Valid"));
			}

			ControlledBodyOffset = ((ControlledActor->GetActorLocation()) - (GetOwner()->GetActorLocation())).Length();
		}
	}
}

void UExamTelekinesisComponent::StopTelekineticHold()
{
	if (ControlledBody) 
	{
		ControlledBody = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Controlled body is now null"));
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

	if (ControlledBody) 
	{
		ControlledBodyOffset += TelekinesisStrenght;
		ControlledBodyOffset = UKismetMathLibrary::Clamp(ControlledBodyOffset, MinControlledBodyOffset, MaxControlledBodyOffset);
		UE_LOG(LogTemp, Warning, TEXT("Sto pushando via "));
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

	if (ControlledBody)
	{
		ControlledBodyOffset -= TelekinesisStrenght;
		ControlledBodyOffset = UKismetMathLibrary::Clamp(ControlledBodyOffset, MinControlledBodyOffset, MaxControlledBodyOffset);
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
			DrawDebugLine(World, StartPosition, EndPosition, FColor::Green, true, 2.f, false, 4.f);
			return &Result;
		}
		else 
		{
			DrawDebugLine(World, StartPosition, EndPosition, FColor::Blue, true, 2.f, false, 4.f);
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
