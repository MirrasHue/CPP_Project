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

	// Don't rotate the character when the controller rotates. Let that just affect the camera
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	if(SkeletalMesh.Succeeded())
	{
		// Set the skeletal mesh we had find with FObjectFinder 
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
		
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetupAttachment(RootComponent);
		
		// Create a Spring Arm (pulls in towards the player if there is a collision)
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
		SpringArmComponent->TargetArmLength = 500.f; // The camera follows at this distance behind the character
		SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller
		SpringArmComponent->SetupAttachment(RootComponent);

		// Create a Camera
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
		// Attach the camera to the end of the Spring Arm and let the arm adjust to match the controller orientation
		CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
		CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

		// Configure character movement
		GetCharacterMovement()->bOrientRotationToMovement = true; // Character turns
		GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);// at this velocity
		GetCharacterMovement()->JumpZVelocity = 400.f;
		GetCharacterMovement()->AirControl = 0.2f;

		AutoPossessPlayer = EAutoReceiveInput::Player0;
	}
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
	// Look up/down with the camera
	PlayerInputComponent->BindAxis("CameraPitch", this, &AMainWarrior::AddControllerPitchInput);
	// Turn the camera around the character
	PlayerInputComponent->BindAxis("CameraYaw", this, &AMainWarrior::AddControllerYawInput);

	
	// ACTION BINDINGS

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainWarrior::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainWarrior::StopJumping);
}

void AMainWarrior::MoveForward(float Input)
{
	if(Controller && Input)
	{
		// Find out which way is forward

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Input);
	}
}

void AMainWarrior::MoveRight(float Input)
{
	if(Controller && Input)
	{
		// Find out which way is right

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Input);
	}
}