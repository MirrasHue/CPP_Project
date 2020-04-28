// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainWarrior.generated.h"

class USpringArmComponent;
class UCameraComponent;

enum class EMovementState : uint8
{
	NotSprinting,
	Sprinting
};

enum class EStaminaState : uint8
{
	Normal,
	Exhausted
};

UCLASS()
class CPP_PROJECT_API AMainWarrior : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainWarrior();

	// Spring Arm for positioning the camera behind the character
	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere,  Category = "Camera")
	UCameraComponent* CameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called for Forward/Backward movement
	void MoveForward(float Input);
	// Called for Left/Right movement
	void MoveRight(float Input);

	inline void SprintKey(); // Used for both sprint key pressed and released

	void SetMovementState(EMovementState State); // Also sets the movement speed based on the state
	void SetStaminaState(EStaminaState State) { StaminaState = State; }

public:

//////////////////  Player's Properties  //////////////////

	UPROPERTY(EditAnywhere, Category = "Player | Health")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Stamina")
	float Stamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Stamina")
	float StaminaDrainRate = 10.f; // units / s

	UPROPERTY(EditAnywhere, Category = "Player | Stamina")
	float StaminaFillRate = 10.f; // units / s

	UPROPERTY(EditAnywhere, Category = "Player | Stamina")
	float MinSprintStamina = 20.f; // Minimum stamina to be able to sprint again

	UPROPERTY(EditAnywhere, Category = "Player | Movement")
	float WalkSpeed = 200.f; // cm / s

	UPROPERTY(EditAnywhere, Category = "Player | Movement")
	float SprintSpeed = 600.f; // cm / s

	bool bSprintKeyDown = false;

	EMovementState MovementState = EMovementState::NotSprinting;
	EStaminaState StaminaState = EStaminaState::Normal;
};
