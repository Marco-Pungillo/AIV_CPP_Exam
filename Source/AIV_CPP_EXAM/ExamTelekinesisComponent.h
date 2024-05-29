// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "ExamTelekinesisComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIV_CPP_EXAM_API UExamTelekinesisComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExamTelekinesisComponent();

	UPROPERTY(EditAnywhere, Category = "Telekinesis Parameters")
	float TelekinesisRange = 200;
	UPROPERTY(EditAnywhere, Category = "Telekinesis Parameters")
	float TelekinesisStrenght = 25;

	UFUNCTION(BlueprintCallable)
	void TelekineticPush(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel);
	UFUNCTION(BlueprintCallable)
	void TelekineticPull(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FHitResult* TelekinesisRay(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
