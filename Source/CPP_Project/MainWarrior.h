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
	Walk,
	Sprint
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

	void MoveForward(float Input); // Bound to Forward/Backward input
	
	void MoveRight(float Input); // Bound to Left/Right input

	virtual void Jump() override; // For calling the base class Jump just when the jump animation has ended

	UFUNCTION()
	void OnWarriorLanded(const FHitResult& Hit);

	FORCEINLINE void SprintKey(); // Bound to both sprint key pressed and released

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

	FORCEINLINE void SetIsAttacking(bool IsAttacking) { bIsAttacking = IsAttacking; }

	FORCEINLINE void SetCanJump(bool CanJump) { bCanJump = CanJump; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	bool IsAlive() { return bIsAlive; }

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
	
	EMovementState MovementState = EMovementState::Walk;
	EStaminaState StaminaState = EStaminaState::Normal;

	bool bSprintKeyDown = false;

	bool bIsAttacking = false;

	bool bCanJump = true;

	UPROPERTY(BlueprintReadOnly)
	bool bIsAlive = true;

	//////////////////  Player's Properties  //////////////////

	UPROPERTY(EditAnywhere, Category = "Player | Health")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Stamina")
	float Stamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Stamina")
	float MaxStamina = 100.f;

	friend class UPlayerStats;

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
