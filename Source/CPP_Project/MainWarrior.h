// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainWarrior.generated.h"

class USpringArmComponent;
class UCameraComponent;

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
	// Called for Side to Side movement
	void MoveRight(float Input);

public:

//////////////////  Player's Attributes  //////////////////

	UPROPERTY(EditAnywhere, Category = "Player | Health")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Stamina")
	float Stamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Player | Stamina")
	float MaxStamina = 100.f;
};
