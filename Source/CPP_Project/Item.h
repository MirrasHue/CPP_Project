// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UParticleSystem;
class USoundCue;

UCLASS()
class CPP_PROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Item | Collision")
	UBoxComponent* CollisionVolume;

	UPROPERTY(EditAnywhere, Category = "Item | Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Item | Particle")
	UParticleSystemComponent* IdleParticle;

	UPROPERTY(EditAnywhere, Category = "Item | Particle")
	UParticleSystem* ContactParticle;

	UPROPERTY(EditAnywhere, Category = "Item | Sound")
	USoundCue* ContactSound;
};
