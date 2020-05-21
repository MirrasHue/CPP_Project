// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainWarrior.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;
class AWeapon;

enum class EMovementState : uint8
{
	Walking,
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called for Forward/Backward movement
	void MoveForward(float Input);
	// Called for Left/Right movement
	void MoveRight(float Input);

	FORCEINLINE void SprintKey(); // Used for both sprint key pressed and released

	void SetMovementState(EMovementState State); // Also sets the movement speed based on the state
	FORCEINLINE void SetStaminaState(EStaminaState State) { StaminaState = State; }

	void Attack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetCurrentWeapon(AWeapon* Weapon) { CurrentWeapon = Weapon; }
	FORCEINLINE AWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	FORCEINLINE void IsAttacking(bool Attacking) { bIsAttacking = Attacking; }

protected:

	// Spring Arm for positioning the camera behind the character
	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere,  Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere,  Category = "Combat")
	UAnimMontage* CombatMontage;

	UPROPERTY()
	AWeapon* CurrentWeapon;
	
	EMovementState MovementState = EMovementState::Walking;
	EStaminaState StaminaState = EStaminaState::Normal;

	bool bSprintKeyDown = false;

	bool bIsAttacking = false;

public:

//////////////////  Player's Properties  //////////////////

	/*
		Add Getters and Setters
	*/

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
};
