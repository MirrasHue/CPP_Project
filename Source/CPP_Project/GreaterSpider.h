// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "GreaterSpider.generated.h"

class UBoxComponent;

UCLASS()
class CPP_PROJECT_API AGreaterSpider : public AEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGreaterSpider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnLeftClawHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnRightClawHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Enables/disables the left/right claw's collision
	
	UFUNCTION(BlueprintCallable)
	void EnableClawHitbox();

	UFUNCTION(BlueprintCallable)
	void DisableClawHitbox();

protected:

	UPROPERTY(EditAnywhere, Category = "Combat | Collision")
	UBoxComponent* LeftClawHitbox;

	UPROPERTY(EditAnywhere, Category = "Combat | Collision")
	UBoxComponent* RightClawHitbox;

	bool bHitCounted = false; // Used to avoid the same claw swing being counted 2 or more times

};
