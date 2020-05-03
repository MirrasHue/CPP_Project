// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntranceSwitch.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class CPP_PROJECT_API AEntranceSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntranceSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Switch")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Switch")
	UStaticMeshComponent* Switch;

	UPROPERTY(EditAnywhere, Category = "Entrance")
	UStaticMeshComponent* Entrance;

	// The direction which the Entrance should move in order to open
	UPROPERTY(EditAnywhere, Category = "Entrance")
	FVector EntranceOpenDirection = FVector::UpVector;

	// The maximum distance from the initial position that the Entrance could reach
	UPROPERTY(EditAnywhere, Category = "Entrance")
	float MaxEntranceDisplacement = 300.f;

	UPROPERTY(EditAnywhere, Category = "Entrance")
	float EntranceOpeningSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Entrance")
	float EntranceClosingSpeed = 200.f;

	bool bSwitchPressed = false;

	// To keep track where in the opening/closing process the Entrance is
	float CurrentEntranceDisplacement;
};
