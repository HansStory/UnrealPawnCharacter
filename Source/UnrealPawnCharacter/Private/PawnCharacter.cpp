#include "PawnCharacter.h"
#include "EnhancedInputComponent.h"
#include "PawnCharacterPlayerController.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APawnCharacter::APawnCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Capsule Coliision Component
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComp->SetupAttachment(RootComponent);
	CapsuleComp->SetSimulatePhysics(false);
	CapsuleComp->SetCapsuleHalfHeight(100.0f);

	// Set Skeletal Mesh Component
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletaMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);
	SkeletalMeshComp->SetSimulatePhysics(false);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/Tutorial/SubEditors/TutorialAssets/Character/TutorialTPP.TutorialTPP'"));
	if (MeshAsset.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(MeshAsset.Object);
	}
	SkeletalMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	SkeletalMeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Set Spring Arm Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	// Set Camera Component
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	// Set Speed
	MoveSpeed = 10.0f;
	RotateSpeed = 2.0f;
}

void APawnCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APawnCharacterPlayerController* PlayerController = Cast<APawnCharacterPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&APawnCharacter::Move);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&APawnCharacter::Look);
			}
		}
	}
}


void APawnCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		FVector forwardVector = GetActorForwardVector();
		SetActorLocation(GetActorLocation() + forwardVector * MoveInput.X * MoveSpeed);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector rightVector = GetActorRightVector();
		SetActorLocation(GetActorLocation() + rightVector * MoveInput.Y * MoveSpeed);
	}
}

void APawnCharacter::Look(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D LookInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(LookInput.X))
	{
		FRotator actorRotation = GetActorRotation();
		actorRotation.Yaw += LookInput.X;
		SetActorRotation(actorRotation);

		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Yaw += LookInput.X;
		ControlRotation.Pitch = FMath::Clamp(ControlRotation.Pitch - LookInput.Y, -89.0f, 89.0f);
		Controller->SetControlRotation(ControlRotation);
	}
}
