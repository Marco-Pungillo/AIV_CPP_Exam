// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryTrigger.h"

// Sets default values
AVictoryTrigger::AVictoryTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Panel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel"));
    RootComponent = Panel;

    SetUpTrigger();

    SetUpTexts();

}


void AVictoryTrigger::SetUpTrigger()
{
    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    TriggerVolume->SetupAttachment(RootComponent);

    // Bind the overlap events
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AVictoryTrigger::OnOverlapBegin);
}

void AVictoryTrigger::SetUpTexts()
{
    //Text Activation status
    InfoText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Info Text"));
    VictoryText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Victory Text"));

    InfoText->SetupAttachment(RootComponent);
    VictoryText->SetupAttachment(RootComponent);

    VictoryText->SetVisibility(false);
}

// Called when the game starts or when spawned
void AVictoryTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVictoryTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVictoryTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    IImpulsable* ImpulsableActor = Cast<IImpulsable>(OtherActor);

    if (ImpulsableActor) 
    {
        VictoryText->SetVisibility(true);
        InfoText->SetVisibility(false);
    }
}

