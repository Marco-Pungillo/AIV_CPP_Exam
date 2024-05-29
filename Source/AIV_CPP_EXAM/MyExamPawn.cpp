// Fill out your copyright notice in the Description page of Project Settings.


#include "MyExamPawn.h"


// Input Includes
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AMyExamPawn::AMyExamPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Istantiating and initializing root component
	this->Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule_Root"));
	this->Capsule->InitCapsuleSize(30, 80);
	this->Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->Capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	RootComponent = Capsule;

	// Istantiate other components
	this->MovementComponentInstance = CreateDefaultSubobject<UMyExamMovementComponent>(TEXT("EXAM_MovementComponent"));
	this->TelekinesisComponentInstance = CreateDefaultSubobject<UExamTelekinesisComponent>(TEXT("Telekinesis Component"));

	this->SkeletalMeshComponentInstance = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EXAM_SkeletalMesh"));
	FString SkeletalMeshPath = "/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny";
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
	if (Mesh) 
	{
		this->SkeletalMeshComponentInstance->SetSkeletalMesh(Mesh);
		this->SkeletalMeshComponentInstance->SetupAttachment(RootComponent);
		this->SkeletalMeshComponentInstance->SetRelativeLocation(FVector(0,0,-80));
		this->SkeletalMeshComponentInstance->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0, 0, -90)));
	}

	this->PawnCameraInstance = CreateDefaultSubobject<UCameraComponent>(TEXT("Pawn Camera"));
	this->PawnCameraInstance->bUsePawnControlRotation = true;

	this->CameraBoomInstance = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	this->CameraBoomInstance->SetupAttachment(RootComponent);
	this->PawnCameraInstance->SetupAttachment(this->CameraBoomInstance);

	// Initialize World for raytrace porpouse
	FWorldContext* world = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
	CurrentWorld = world->World();
}

// Called when the game starts or when spawned
void AMyExamPawn::BeginPlay()
{
	Super::BeginPlay();


	// I take the controller to get enhanced Input System and add mapping context
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(ExamMappingContext, 0);
		}
	}
	
}

#pragma region InputCallbacks

	void AMyExamPawn::Move(const FInputActionValue& Value)
	{
		FVector2D currentMappedDirection = Value.Get<FVector2D>();
		this->MovementComponentInstance->MoveForwardRight(currentMappedDirection);
	
	}
	
	void AMyExamPawn::Look(const FInputActionValue& Value)
	{
		FVector2D currentMappedDirection = Value.Get<FVector2D>();
		FString mappedInputs = currentMappedDirection.ToString();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, mappedInputs);
	}
	
	void AMyExamPawn::ApplyPushForce(const FInputActionValue& Value)
	{
		// I pass vectors instead of pointers because i don't need to modify the vectors and we did it during lessons
	
		FVector ForceApplicationPosition = this->GetActorLocation() + this->GetActorForwardVector() * Capsule->GetScaledCapsuleRadius() * 1.1;
		//FVector* ForceApplicationPosPtr = &ForceApplicationPosition;
	
		TelekinesisComponentInstance->TelekineticPush(CurrentWorld, ForceApplicationPosition, this->GetActorForwardVector(),ECollisionChannel::ECC_WorldDynamic);
	}

	void AMyExamPawn::ApplyPullForce(const FInputActionValue& Value)
	{
		FVector ForceApplicationPosition = this->GetActorLocation() + this->GetActorForwardVector() * Capsule->GetScaledCapsuleRadius() * 1.1;
		//FVector* ForceApplicationPosPtr = &ForceApplicationPosition;

		TelekinesisComponentInstance->TelekineticPull(CurrentWorld, ForceApplicationPosition, this->GetActorForwardVector(), ECollisionChannel::ECC_WorldDynamic);
	}

	void AMyExamPawn::StopForce()
	{
	}

	
#pragma endregion




// Called every frame
void AMyExamPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyExamPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set Up Binding using a safe Cast to Obtain the enhancedInputSystem
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this, &AMyExamPawn::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyExamPawn::Look);
		EnhancedInputComponent->BindAction(PushForceAction, ETriggerEvent::Triggered, this, &AMyExamPawn::ApplyPushForce);
		EnhancedInputComponent->BindAction(PushForceAction, ETriggerEvent::Completed, this, &AMyExamPawn::StopForce);
		EnhancedInputComponent->BindAction(PullForceAction, ETriggerEvent::Triggered, this, &AMyExamPawn::ApplyPullForce);
	}

}

