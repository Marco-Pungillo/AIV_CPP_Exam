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
	this->TelekinesisComponentInstance = CreateDefaultSubobject<UExamTelekinesisComponent>(TEXT("TelekinesisComponent"));
	this->Tags.Add("Player");

	this->SetUpCharacterMesh();

	this->SetUpCharacterCamera();

	this->SetUpMovementParams();

	this->SetUpTelekinesis();
}


#pragma region ComponentInitializing

void AMyExamCharacter::SetUpCharacterMesh()
{
	// I initialize the mesh as the default Unreal Engine Manny, through the blueprint i change it to the Skeletal i want to use
	USkeletalMeshComponent* characterMesh = this->GetMesh();
	FString SkeletalMeshPath = "/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'";
	USkeletalMesh* charMesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);

	if (characterMesh && charMesh)
	{
		characterMesh->SetSkeletalMeshAsset(charMesh);
		characterMesh->SetRelativeLocation(FVector(0, 0, -80));
		characterMesh->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0, 0, -90)));
	}


}

void AMyExamCharacter::SetUpCharacterCamera()
{

	this->CharacterCameraInstance = CreateDefaultSubobject<UCameraComponent>(TEXT("Pawn Camera"));
	this->CameraBoomInstance = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));

	this->CameraBoomInstance->SetupAttachment(RootComponent);
	this->CharacterCameraInstance->SetupAttachment(this->CameraBoomInstance);

	this->CharacterCameraInstance->bUsePawnControlRotation = true;

	this->CameraBoomInstance->TargetArmLength = 50;
	this->CameraBoomInstance->SocketOffset = FVector(-25, 59, 100);

}

void AMyExamCharacter::SetUpTelekinesis()
{
	this->TelekinesisOriginInstance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TelekinesisOrigin"));
	FString MeshPath = "/Script/Engine.StaticMesh'/Game/Custom/MainCharacter/Materials/TelekinesisOriginCube.TelekinesisOriginCube'";
	UStaticMesh* telekinesisOriginMesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);
	this->TelekinesisOriginInstance->SetStaticMesh(telekinesisOriginMesh);
	this->TelekinesisOriginInstance->SetRelativeLocation(FVector(210, -40, -50));
	this->TelekinesisOriginInstance->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));

	this->TelekinesisComponentInstance->SetTelekinesisOrigin(this->TelekinesisOriginInstance);
	this->TelekinesisOriginInstance->SetupAttachment(CharacterCameraInstance);
	this->TelekinesisComponentInstance->TelekinesisCamera = CharacterCameraInstance;

	this->TelekinesisComponentInstance->SetStandardTelekinesisChannel(ECollisionChannel::ECC_GameTraceChannel1);

}

void AMyExamCharacter::SetUpMovementParams()
{
	this->GetCharacterMovement()->JumpZVelocity = 650;
}

#pragma endregion


// Called when the game starts or when spawned
void AMyExamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize World for raytrace porpouse
	FWorldContext* world = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
	CurrentWorld = world->World();
	this->TelekinesisComponentInstance->SetTelekinesisWorld(CurrentWorld);

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

	// Remember to setup the pitch limits in the character details
	this->AddControllerYawInput(CurrentMappedDirection.X);

}

void AMyExamCharacter::StartJump(const FInputActionValue& Value)
{
	UCharacterMovementComponent* charMov = this->GetCharacterMovement();
	charMov->DoJump(false);
}

#pragma endregion

#pragma region Telekinesis
// I pass vectors instead of pointers because i don't need to modify the vectors (and because we did it during lessons)
void AMyExamCharacter::ApplyTelekineticHold(const FInputActionValue& Value)
{
	FVector ForceApplicationPosition = this->TelekinesisOriginInstance->GetComponentLocation() + this->TelekinesisOriginInstance->GetForwardVector() * this->GetCapsuleComponent()->GetScaledCapsuleRadius() * 1.1;
	FVector* ForceApplicationPosPtr = &ForceApplicationPosition;

	//ECC_GameTraceChannel1 is the Telekinetic Trace Channel
	TelekinesisComponentInstance->ApplyTelekineticHold(CurrentWorld, ForceApplicationPosition, this->TelekinesisOriginInstance->GetForwardVector(), ECollisionChannel::ECC_GameTraceChannel1);
	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance) 
	{
		float animTime = 0.1f;		//Default value in case the animation can't be played.
		animTime = AnimInstance->Montage_Play(SkillMontage, 1.f);
		if (animTime < 0.1f)
		{
			//The function returns 0 if the animation can't be played.
			animTime = 0.1f;
		}
	}

	if (TelekinesisComponentInstance->ControlledBody) 
	{
		TelekinesisOriginInstance->SetMaterial(0, TargetMaterial);
	}
}

void AMyExamCharacter::StopTelekineticHold(const FInputActionValue& Value)
{
	TelekinesisComponentInstance->StopTelekineticHold();
	if (!TelekinesisComponentInstance->ControlledBody)
	{
		TelekinesisOriginInstance->SetMaterial(0, NoTargetMaterial);
	}
}


void AMyExamCharacter::ApplyPushForce(const FInputActionValue& Value)
{
	if (TelekinesisComponentInstance->ControlledBody) 
	{
		TelekinesisComponentInstance->TelekineticPush();
	}
}

void AMyExamCharacter::ApplyPullForce(const FInputActionValue& Value)
{
	if (TelekinesisComponentInstance->ControlledBody)
	{
		TelekinesisComponentInstance->TelekineticPull();
	}
}

void AMyExamCharacter::ApplyTelekineticImpulse(const FInputActionValue& Value)
{
	FVector ForceApplicationPosition = this->TelekinesisOriginInstance->GetComponentLocation() + this->TelekinesisOriginInstance->GetForwardVector() * this->GetCapsuleComponent()->GetScaledCapsuleRadius() * 1.1;
	FVector* ForceApplicationPosPtr = &ForceApplicationPosition;

	//ECC_GameTraceChannel1 is the Telekinetic Trace Channel
	TelekinesisComponentInstance->TelekineticImpulse(CurrentWorld, ForceApplicationPosition, this->TelekinesisOriginInstance->GetForwardVector(), ECollisionChannel::ECC_GameTraceChannel1);
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::StartJump);

		EnhancedInputComponent->BindAction(TelekinesisHoldAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::ApplyTelekineticHold);
		EnhancedInputComponent->BindAction(TelekinesisStopAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::StopTelekineticHold);
		EnhancedInputComponent->BindAction(PushForceAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::ApplyPushForce);
		EnhancedInputComponent->BindAction(PullForceAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::ApplyPullForce);

		EnhancedInputComponent->BindAction(ImpulseAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::ApplyTelekineticImpulse);
		//EnhancedInputComponent->BindAction(TelekinesisStopAction, ETriggerEvent::Triggered, this, &AMyExamCharacter::StopTelekineticHold);

	}
}

