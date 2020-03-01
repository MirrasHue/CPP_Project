// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Critter.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class CPP_PROJECT_API ACritter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACritter();

	UPROPERTY(EditAnywhere, Category = "Critter")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Critter")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Critter")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Critter")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Critter")
	float MoveSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector ForwardVelocity;
	FVector RightVelocity;
	FVector2D MouseInput;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Input);
	
	void MoveRight(float Input);

	void CameraPitch(float AxisValue);
	
	void CameraYaw(float AxisValue);

};
