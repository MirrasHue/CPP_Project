// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

class UAIPerceptionComponent;
struct FActorPerceptionInfo;

UCLASS()
class CPP_PROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AEnemyAIController();

protected:
	// For when this controller possesses a pawn.
	virtual void OnPossess(APawn* InPawn) override;

	// Function that will be called when the AIPerception senses the player getting in or out.
	UFUNCTION()
	void OnPlayerPerceived(AActor* Actor, FAIStimulus Stimulus);

	void MoveToTarget(class APawn* Target);

	// Custom update function for checking changes within AI's sight, given that AIPerception doesn't have one.
	// It will be called every few seconds, specified by CheckInterval.
	UFUNCTION()
	void CheckChangesWithinAISight();

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, Category = "AI")
	float AcceptanceRadius = 10.f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.5"), Category = "AI")
	float CheckInterval = 1.f; // Amount of time (in seconds) between checking for changes within AI's sight.

	FTimerHandle CheckIntervalTimer;

	bool bPlayerPerceived = false;

	const FActorPerceptionInfo* PlayerInfo = nullptr;
	//const FActorPerceptionInfo* EnemyInfo = nullptr;

	class AMainWarrior* Player;
	class AEnemy* OwnedEnemy; // Enemy possessed by this controller.
};
