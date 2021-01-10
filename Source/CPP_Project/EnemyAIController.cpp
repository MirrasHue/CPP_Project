// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "MainWarrior.h"
#include "Enemy.h"


AEnemyAIController::AEnemyAIController()
{
    AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // Bind the member functions to the necessary delegates

    if(AIPerception)
        AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPlayerPerceived);

    GetWorldTimerManager().SetTimer(CheckIntervalTimer, this, &AEnemyAIController::CheckChangesWithinAISight, CheckInterval, true/*loop*/);

    OwnedEnemy = Cast<AEnemy>(InPawn);
}

void AEnemyAIController::OnPlayerPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    //UE_LOG(LogTemp, Warning, TEXT("OnPlayerPerceived being called"));
    Player = Cast<AMainWarrior>(Actor);

    if(Player && Stimulus.IsActive())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Player Perceived"));
        SetFocus(Player); // So that the enemy faces the player
        bPlayerPerceived = true;
        PlayerInfo = AIPerception->GetActorInfo(*Player);
    }
    else
    if(Player && PlayerInfo && !Stimulus.IsActive()) // Check Player again so that other perceived pawns don't make these instructions execute
    {
        //UE_LOG(LogTemp, Warning, TEXT("Losing sight of Player"));
        ClearFocus(EAIFocusPriority::Gameplay);
        bPlayerPerceived = false;
        MoveToLocation(PlayerInfo->GetLastStimulusLocation()); // Move to the player's last known location instead of just stop
    }
    /*else
    if(Stimulus.IsActive()) // At this point we know that the Actor isn't the player, so just ignore it
    {
        UE_LOG(LogTemp, Warning, TEXT("Forgotten Actor still triggering this event, no bueno"));

        /** Kind of a bug here, when the Actor is forgotten it is still perceived if it keeps
            within sight, or walks in/out of this AIPerception, not the desirable behavior.
        AIPerception->ForgetActor(Actor);

        /*EnemyInfo = AIPerception->GetActorInfo(*Actor);
        FVector EnemyLocation = EnemyInfo->GetLastStimulusLocation();
        UE_LOG(LogTemp, Warning, TEXT("Enemy position: X = %f | Y = %f | Z = %f"), EnemyLocation.X, EnemyLocation.Y, EnemyLocation.Z);
    }*/

    // Make sure that the reference to the player isn't lost when another pawn walks into this AIPerception and the player is
    // still within it, this happens because the cast at the top fails when the Actor is something other than a AMainWarrior
    if(!Player && bPlayerPerceived)
        Player = Cast<AMainWarrior>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void AEnemyAIController::MoveToTarget(APawn* Target)
{
    //UE_LOG(LogTemp, Warning, TEXT("Move To Target"));
    if(!Target)
        return;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);

	/*FNavPathSharedPtr NavPath;
	MoveTo(MoveRequest, &NavPath);*/
	MoveTo(MoveRequest);
}

void AEnemyAIController::CheckChangesWithinAISight()
{
    if(!bPlayerPerceived || !OwnedEnemy) // If bPlayerPerceived is true, Player must be automatically non null
        return;

    float DistanceEnemyToPlayer = OwnedEnemy->GetDistanceTo(Player);
    float EnemyCapsuleRadius  = OwnedEnemy->GetCapsuleComponent()->GetScaledCapsuleRadius();

    // Also takes into consideration both capsules involved and the AcceptanceRadius, giving a little bit of extra room,
    // so that the enemy doesn't jiggle a lot with small adjustments by the player
    float AcceptableDistance = EnemyCapsuleRadius + 50.f /*Player's capsule radius(40) + 10*/ + 2 * AcceptanceRadius;

    if(DistanceEnemyToPlayer > AcceptableDistance) // Out of range
    {
        OwnedEnemy->bShouldAttack = false;
        if(Player->IsAlive())
            MoveToTarget(Player);
    }
    else // In range, the enemy can attack if the player isn't dead
    {
        OwnedEnemy->bShouldAttack = Player->IsAlive() ? true : false;
    }

    /*if(PlayerInfo) 
    {
        FVector PlayerLocation = PlayerInfo->GetLastStimulusLocation();
        UE_LOG(LogTemp, Warning, TEXT("Player position: X = %f | Y = %f | Z = %f"), PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
    }*/

    /*FVector FocalPoint = GetFocalPoint();
    UE_LOG(LogTemp, Warning, TEXT("AI's focal point: X = %f | Y = %f | Z = %f"), FocalPoint.X, FocalPoint.Y, FocalPoint.Z);*/
}
