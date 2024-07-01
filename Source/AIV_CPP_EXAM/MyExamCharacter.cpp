// Fill out your copyright notice in the Description page of Project Settings.


#include "MyExamCharacter.h"

// Input Includes
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AMyExamCharacter::AMyExamCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->TelekinesisComponentInstance = CreateDefaultSubobject<UExamTelekinesisComponent>(TEXT("Telekinesis Component"));

	this->SetUpCharacterMesh();
	
	this->SetUpCharacterCamera();

	this->SetUpMovementParams();
}


void AMyExamCharacter::SetUpCharacterMesh()
{
	USkeletalMeshComponent* characterMesh = this->GetMesh();
	FString SkeletalMeshPath = "/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'";
	USkeletalMesh* charMesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);

	if (characterMesh)
	{
		characterMesh->SetSkeletalMeshAsset(charMesh);
		characterMesh->SetRelativeLocation(FVector(0, 0, -80));
		characterMesh->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0, 0, -90)));
	}
}

void AMyExamCharacter::SetUpCharacterCamera()
{
	this->CharacterCameraInstance = CreateDefaultSubobject<UCameraComponent>(TEXT("Pawn Camera"));
	this->CharacterCameraInstance->bUsePawnControlRotation = true;

	this->CameraBoomInstance = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	this->CameraBoomInstance->SetupAttachment(RootComponent);
	this->CharacterCameraInstance->SetupAttachment(this->CameraBoomInstance);

	this->CameraBoomInstance->TargetArmLength = 50;
	this->CameraBoomInstance->SocketOffset = FVector(-25, 59, 100);

}

void AMyExamCharacter::SetUpMovementParams()
{
	this->GetCharacterMovement()->JumpZVelocity = 650;
}

// Called when the game starts or when spawned
void AMyExamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize World for raytrace porpouse
	FWorldContext* world = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
	CurrentWorld = world->World();

	// I take the controller to get enhanced Input System and add mapping context
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(ExamMappingContext, 0);
		}

		// Limit Camera Pitch Rotation
		PlayerController->PlayerCameraManager->ViewPitchMax = CameraPitchLimit;
		PlayerController->PlayerCameraManager->ViewPitchMin = -CameraPitchLimit;

	}

}

// Called every frame
void AMyExamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region InputCallbacks

#pragma region Movement
void AMyExamCharacter::Move(const FInputActionValue& Value)
{
	// To move to controller
	FRotator currentControlRotation = this->GetControlRotation();
	currentControlRotation.Pitch = 0;
	
	FVector leftRight = UKismetMathLibrary::GetRightVector(currentControlRotation);
	
	// To keep here
	this->AddMovementInput(leftRight, Value.Get<FVector2D>().X, false);

	// To move to controller
	currentControlRotation.Roll = 0;
	FVector forwardBackward = UKismetMathLibrary::GetForwardVector(currentControlRotation);

	// To keep here
	this->AddMovementInput(forwardBackward, Value.Get<FVector2D>().Y, false);
}

void AMyExamCharacter::Look(const FInputActionValue& Value)
{
	FVector2D CurrentMappedDirection = Value.Get<FVector2D>();
	FString MappedInputs = CurrentMappedDirection.ToString();

	this->AddControllerPitchInput(CurrentMappedDirection.Y);

	
	this->AddControllerYawInput(CurrentMappedDirection.X);

	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FString::Printf(TEXT("Controller Pitch: %s"), this->GetControlRotation().Pitch));

}

void AMyExamCharacter::Jump(const FInputActionValue& Value)
{
	UCharacterMovementComponent* charMov = this->GetCharacterMovement();
	charMov->DoJump(false);
}

#pragma endregion




#pragma region Telekinesis
// I pass vectors instead of pointers because i don't need to modify the vectors (and because we did it during lessons)
void AMyExamCharacter::ApplyPushForce(const FInputActionValue& Value)
{
	FVector ForceApplicationPosition = this->CharacterCameraInstance->GetComponentLocation() + this->CharacterCameraInstance->GetForwardVector() * this->GetCapsuleComponent()->GetScaledCapsuleRadius() * 1.1;
	FVector* ForceApplicationPosPtr = &ForceApplicationPosition;

	TelekinesisComponentInstance->TelekineticPush(CurrentWorld, ForceApplicationPosition, this->CharacterCameraInstance->GetForwardVector(), ECollisionChannel::ECC_GameTraceChannel1);
}
//
void AMyExamCharacter::ApplyPullForce(const FInputActionValue& Value)
{
	FVector ForceApplicationPosition = this->CharacterCameraInstance->GetComponentLocation() + this->CharacterCameraInstance->GetForwardVector() * this->GetCapsuleComponent()->GetScaledCapsuleRadius() * 1.1;
	FVector* ForceApplicationPosPtr = &ForceApplicationPosition;

	TelekinesisComponentInstance->TelekineticPull(CurrentWorld, ForceApplicationPosition, this->CharacterCameraInstance->GetForwardVector(), ECollisionChannel::ECC_GameTraceChannel1);
}

void AMyExamCharacter::StopForce(const FInputActionValue& Value)
{
}

#pragma endregion



#pragma endregion


// Called to bind functionality to input
void AMyExamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set Up Binding using a safe Cast to Obtain the enhancedInputSystem
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::Jump);
		EnhancedInputComponent->BindAction(PushForceAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::ApplyPushForce);
		EnhancedInputComponent->BindAction(PushForceAction, ETriggerEvent::Completed, this, &AMyExamCharacter::StopForce);
		EnhancedInputComponent->BindAction(PullForceAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::ApplyPullForce);

	}
}

