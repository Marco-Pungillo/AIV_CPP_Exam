// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ITelekineticObject.h"

#include "TelekineticActor.generated.h"
UCLASS()
class AIV_CPP_EXAM_API ATelekineticActor : public AActor, public IITelekineticObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATelekineticActor();

#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshInstance;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TelekinesisMaterials)
	UMaterialInterface* NoTargetMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TelekinesisMaterials)
	UMaterialInterface* TargetMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnObjectHold() override;
	void OnObjectHoldStop() override;
	void OnObjectPush() override;
	void OnObjectPull() override;


};
