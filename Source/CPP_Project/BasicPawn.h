// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasicPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class CPP_PROJECT_API ABasicPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Input);
	
	void MoveRight(float Input);

	void CameraPitch(float AxisValue);
	
	void CameraYaw(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Basic Pawn")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Basic Pawn")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Basic Pawn")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Basic Pawn")
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = "Basic Pawn")
	float MoveSpeed;

	FVector ForwardVelocity;
	FVector RightVelocity;
	FVector2D MouseInput;
};
