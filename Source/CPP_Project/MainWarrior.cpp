// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWarrior.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainWarrior::AMainWarrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 88.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		SkeletalMesh(TEXT("SkeletalMesh'/Game/Character/SkeletalMesh/paladin_j_nordstrom.paladin_j_nordstrom'"));

	static ConstructorHelpers::FObjectFinder<UClass>
		Anim_BP(TEXT("AnimBlueprint'/Game/Character/Animation/Anim_BP.Anim_BP_C'"));

	// Don't rotate the character when the controller rotates. Let that just affect the camera
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	if(!SkeletalMesh.Succeeded() || !Anim_BP.Succeeded())
		return;

	// Set the skeletal mesh we had find with FObjectFinder
	GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);

	// Set the Anim_BP we had find with FObjectFinder
	GetMesh()->SetAnimInstanceClass(Anim_BP.Object);
	
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetupAttachment(RootComponent);
	
	// Create a Spring Arm (pulls in towards the player if there is a collision)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 500.f; // The camera follows at this distance behind the character
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	SpringArm->SetupAttachment(RootComponent);

	// Create a Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// Attach the camera to the end of the Spring Arm and let the arm adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character turns
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);// at this velocity
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 0.2f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainWarrior::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float dtStaminaDrain = StaminaDrainRate * DeltaTime;
	float dtStaminaFill = StaminaFillRate * DeltaTime;

	switch(StaminaState)
	{
	case EStaminaState::Normal
			:
		if(bSprintKeyDown)
		{
			if(Stamina > 1.f)
				SetMovementState(EMovementState::Sprinting);
			else
				SetStaminaState(EStaminaState::Exhausted);

			// Decrease the stamina based on a minimum speed
			FVector Vel = GetVelocity();
			Stamina -= FVector(Vel.X, Vel.Y, 0.f).Size() > WalkSpeed ? dtStaminaDrain : -dtStaminaFill;
		}
		else
		{
			SetMovementState(EMovementState::Walking);
			Stamina += dtStaminaFill;
		}
		break;
	
	case EStaminaState::Exhausted
			:
		SetMovementState(EMovementState::Walking);
		Stamina += dtStaminaFill;

		if(Stamina > MinSprintStamina)
			SetStaminaState(EStaminaState::Normal);

		break;
	}

	Stamina = FMath::Clamp(Stamina, 0.f, MaxStamina);
}

// Called to bind functionality to input
void AMainWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Make sure that PlayerInputComponent is valid
	check(PlayerInputComponent);

	// AXIS BINDINGS

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainWarrior::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainWarrior::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &ACharacter::AddControllerPitchInput);// Look up/down with the camera
	PlayerInputComponent->BindAxis("CameraYaw", this, &ACharacter::AddControllerYawInput);// Move the camera around the character

	// ACTION BINDINGS

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainWarrior::SprintKey);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainWarrior::SprintKey);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainWarrior::Attack);
}

void AMainWarrior::MoveForward(float Input)
{
	// Find out which way is forward
	if(Controller && Input)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Input);
	}
}

void AMainWarrior::MoveRight(float Input)
{
	// Find out which way is right
	if(Controller && Input)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Input);
	}
}

void AMainWarrior::SprintKey()
{
	bSprintKeyDown = !bSprintKeyDown;
}

void AMainWarrior::SetMovementState(EMovementState State)
{
	MovementState = State;

	if(State == EMovementState::Sprinting)
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	else
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMainWarrior::Attack()
{
	if(CombatMontage && !bIsAttacking && CurrentWeapon) // For now the player can only attack with a weapon
	{
		bIsAttacking = true;

		// Currently there are 2 animations for attack
		FString AttackSection = "Attack_" + FString::FromInt(FMath::RandRange(1, 2));

		PlayAnimMontage(CombatMontage, 1.f, FName(*AttackSection));
	}
}
