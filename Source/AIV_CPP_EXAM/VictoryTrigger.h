// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// My Interfaces
#include "Impulsable.h"

//My Components
#include "Components/BoxComponent.h"
#include <Components/TextRenderComponent.h>

#include "VictoryTrigger.generated.h"

UCLASS()
class AIV_CPP_EXAM_API AVictoryTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVictoryTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	UBoxComponent* TriggerVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	UTextRenderComponent* InfoText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	UTextRenderComponent* VictoryText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel")
	UStaticMeshComponent* Panel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetUpTexts();

	void SetUpTrigger();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
};
