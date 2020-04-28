// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/Vector.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class CPP_PROJECT_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();

	UPROPERTY(EditAnywhere, Category = "Floater")
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere, Category = "Floater")
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere, Category = "Floater")
	bool bShouldFloat;

	UPROPERTY(EditAnywhere, Category = "Floater")
	FVector InitialDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};