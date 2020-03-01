// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/Vector.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

class UStaticMeshComponent;

UCLASS()
class CPP_PROJECT_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();

	UPROPERTY(EditAnywhere, Category = "StaticMesh")
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere, Category = "Floating")
	bool bShouldFloat;

	UPROPERTY(EditAnywhere, Category = "Floating")
	FVector InitialDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
