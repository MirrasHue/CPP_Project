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

	UPROPERTY(EditAnywhere, Category = "Entrance Switch")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Entrance Switch")
	UStaticMeshComponent* Switch;

	UPROPERTY(EditAnywhere, Category = "Entrance Switch")
	UStaticMeshComponent* Entrance;

	/** The direction which the Entrance should move in order to open */
	UPROPERTY(EditAnywhere, Category = "Entrance Switch")
	FVector EntranceMoveDirection;

	/** The maximum distance from the initial position that the Entrance could reach */
	UPROPERTY(EditAnywhere, Category = "Entrance Switch")
	float MaxEntranceDisplacement;

	/** To keep track where in the opening/closing process the Entrance is */
	float CurrentEntranceDisplacement;

	UPROPERTY(EditAnywhere, Category = "Entrance Switch")
	float EntranceOpeningSpeed;

	UPROPERTY(EditAnywhere, Category = "Entrance Switch")
	float EntranceClosingSpeed;

	FVector InitialEntranceLocation;

	bool bSwitchPressed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
