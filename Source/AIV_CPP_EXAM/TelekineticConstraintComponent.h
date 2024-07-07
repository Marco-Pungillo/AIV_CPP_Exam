// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "TelekineticConstraintComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AIV_CPP_EXAM_API UTelekineticConstraintComponent : public UPhysicsConstraintComponent
{
	GENERATED_BODY()
	
	UTelekineticConstraintComponent();

public:
	UPROPERTY(EditAnywhere, Category = "Telekinesis Parameters")
	float TelekinesisRange = 200;
	UPROPERTY(EditAnywhere, Category = "Telekinesis Parameters")
	float TelekinesisStrenght = 25;


	void SetTelekinesisOwner(UPrimitiveComponent* Owner);


	UFUNCTION(BlueprintCallable)
	void TelekineticHold(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel);
	UFUNCTION(BlueprintCallable)
	void TelekineticPush(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel);
	UFUNCTION(BlueprintCallable)
	void TelekineticPull(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel);

protected:
	UPrimitiveComponent* TelekinesisOwner;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FHitResult* TelekinesisRay(UWorld* World, FVector StartPosition, FVector EndPosition, ECollisionChannel TelekinesisChannel);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
