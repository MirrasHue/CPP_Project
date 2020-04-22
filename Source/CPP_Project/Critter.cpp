// Fill out your copyright notice in the Description page of Project Settings.


#include "Critter.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACritter::ACritter()
		:
	MoveSpeed(100.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(52.f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->RelativeRotation = FRotator(-25.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 20.f;
	SpringArm->CameraRotationLagSpeed = 20.f;
	SpringArm->SetupAttachment(MeshComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACritter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACritter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MoveDirection = ForwardVelocity + RightVelocity;
	// Comment this line below if you want to move the Pawn in all directions
	MoveDirection.Z = 0.f;
	// Get the normalized vector so it will not cause faster movement in diagonal directions
	FVector NewLocation = GetActorLocation() + (MoveDirection.GetSafeNormal() * MoveSpeed * DeltaTime);
	SetActorLocation(NewLocation);

	FRotator SpringArmRotation = SpringArm->GetComponentRotation();
	SpringArmRotation.Yaw += MouseInput.X;
	SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch += MouseInput.Y, -85.f, 5.f);
	SpringArm->SetWorldRotation(SpringArmRotation);
}

// Called to bind functionality to input
void ACritter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACritter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACritter::MoveRight);
	// Look up/down with the camera
	PlayerInputComponent->BindAxis("CameraPitch", this, &ACritter::CameraPitch);
	// Turn the camera around the character
	PlayerInputComponent->BindAxis("CameraYaw", this, &ACritter::CameraYaw);
}

void ACritter::MoveForward(float Input)
{
	// Find out which way is forward

	const FRotator Rotation = SpringArm->GetComponentRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// Get forward vector
	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	ForwardVelocity = ForwardVector * Input;
}

void ACritter::MoveRight(float Input)
{
	// Find out which way is right

	const FRotator Rotation = SpringArm->GetComponentRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// Get right vector
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	RightVelocity = RightVector * Input;
}

void ACritter::CameraPitch(float AxisValue)
{
	MouseInput.Y = AxisValue;
}

void ACritter::CameraYaw(float AxisValue)
{
	MouseInput.X = AxisValue;
}