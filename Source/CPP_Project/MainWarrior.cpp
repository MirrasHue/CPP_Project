// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWarrior.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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
		Anim_BP(TEXT("AnimBlueprint'/Game/Character/Animation/MainAnim_BP.MainAnim_BP_C'"));

	// Don't rotate the capsule using the controller orientation. Let that just affect the camera
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

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

	if(!SkeletalMesh.Succeeded() || !Anim_BP.Succeeded())
		return;

	// Set the skeletal mesh we had find with FObjectFinder
	GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);

	// Set the Anim_BP we had find with FObjectFinder
	GetMesh()->SetAnimInstanceClass(Anim_BP.Object);
	
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetupAttachment(RootComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainWarrior::BeginPlay()
{
	Super::BeginPlay();
	
	LandedDelegate.AddDynamic(this, &AMainWarrior::OnWarriorLanded);
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
				SetMovementState(EMovementState::Sprint);
			else
				SetStaminaState(EStaminaState::Exhausted);

			// Decrease the stamina based on a minimum speed
			FVector Vel = GetVelocity();
			Stamina -= FVector(Vel.X, Vel.Y, 0.f).Size() > WalkSpeed ? dtStaminaDrain : -dtStaminaFill;
		}
		else
		{
			SetMovementState(EMovementState::Walk);
			Stamina += dtStaminaFill;
		}
		break;
	
	case EStaminaState::Exhausted
			:
		SetMovementState(EMovementState::Walk);
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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainWarrior::Jump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainWarrior::SprintKey);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainWarrior::SprintKey);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainWarrior::Attack);
}

void AMainWarrior::MoveForward(float Input)
{
	// Find out which way is forward
	if(GetController() && Input)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Input);
	}
}

void AMainWarrior::MoveRight(float Input)
{
	// Find out which way is right
	if(GetController() && Input)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Input);
	}
}

void AMainWarrior::Jump()
{
	if(bCanJump)
	{
		Super::Jump();
		bCanJump = false; // It's set back to true on this character's AnimInstance
		// Plays better with the jump animation, without adjustment the feet was way higher than the capsule's bottom
		GetCapsuleComponent()->SetCapsuleHalfHeight(55.f, false);
	}
}

void AMainWarrior::OnWarriorLanded(const FHitResult& Hit)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(88.f, false); // Set it back to the normal half height when landing
	ResetJumpState();
}

void AMainWarrior::SprintKey()
{
	bSprintKeyDown = !bSprintKeyDown;
}

void AMainWarrior::SetMovementState(EMovementState State)
{
	MovementState = State;

	if(State == EMovementState::Sprint)
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	else
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMainWarrior::Attack()
{
	APlayerController* Controller = Cast<APlayerController>(GetController());

	if(!Controller || !CombatMontage || bIsAttacking || !CurrentWeapon) // The player can only attack with a weapon
		return;
	
	bIsAttacking = true; // It's set back to false on this character's AnimInstance

	FString AttackSection;

	if(Controller->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		AttackSection = "LightAttack";
		Stamina -= 10.f;
	}
	else
	if(Controller->WasInputKeyJustPressed(EKeys::RightMouseButton))
	{
		AttackSection = "HeavyAttack";
		Stamina -= 15.f;
	}
	
	PlayAnimMontage(CombatMontage, 1.f, FName(*AttackSection));
}

float AMainWarrior::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if(Health <= 0.f)
	{
		bIsAlive = false;
		DisableInput(nullptr);
	}

	return DamageAmount;
}