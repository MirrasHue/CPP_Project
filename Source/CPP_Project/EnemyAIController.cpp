// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "TimerManager.h"
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
    GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AEnemyAIController::OnMoveCompleted);

    if(AIPerception)
        AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPlayerPerceived);

    GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIController::CheckChangesWithinAISight, CheckInterval, true/*loop*/);

    OwnedEnemy = Cast<AEnemy>(InPawn);
}

void AEnemyAIController::OnPlayerPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    UE_LOG(LogTemp, Warning, TEXT("OnPlayerPerceived being called"));
    Player = Cast<AMainWarrior>(Actor);

    if(Player && Stimulus.IsActive())
    {
        bPlayerPerceived = true;
        PlayerInfo = AIPerception->GetActorInfo(*Player);
    }
    else
    if(Player && !Stimulus.IsActive() && OwnedEnemy && PlayerInfo) // So that other enemies don't make these instructions happen
    {
        //UE_LOG(LogTemp, Warning, TEXT("Losing sight of Player"));
        //StopMovement();
        ClearFocus(EAIFocusPriority::Gameplay);
        OwnedEnemy->bShouldAttack = false;
        bPlayerPerceived = false;
        MoveToLocation(PlayerInfo->GetLastStimulusLocation()); // Move to the player's last known location instead of just stop
    }
    /*else
    if(Stimulus.IsActive()) // At this point we know that the Actor isn't the player, so just ignore it
    {
        UE_LOG(LogTemp, Warning, TEXT("Forgotten Actor still triggering this event, no bueno"));

        /** Kind of a bug here, when the Actor is forgotten it still triggers this event
        if it keeps within the sight of this AIPerception, not the desirable behavior.
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
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);

	/*FNavPathSharedPtr NavPath;
	MoveTo(MoveRequest, &NavPath);*/
	MoveTo(MoveRequest);
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if(!Result.IsSuccess() || !OwnedEnemy || !bPlayerPerceived)
        return;

    //UE_LOG(LogTemp, Warning, TEXT("OnMoveCompleted"));

    // If the movement to the player is successful, the enemy can now attack him
    SetFocus(Player);
    OwnedEnemy->bShouldAttack = true;
}

void AEnemyAIController::CheckChangesWithinAISight()
{
    if(!bPlayerPerceived || !OwnedEnemy) // If bPlayerPerceived is true, Player must be automatically non null
        return;

    float DistanceEnemyToPlayer = OwnedEnemy->GetDistanceTo(Player);
    float EnemyCapsuleRadius  = OwnedEnemy->GetCapsuleComponent()->GetScaledCapsuleRadius();

    // Also takes into consideration both capsules involved and the AcceptanceRadius, giving a little bit of extra room,
    // so that the enemy doesn't jiggle a lot with small adjustments by the player
    if(DistanceEnemyToPlayer > EnemyCapsuleRadius + 50.f /*Player's capsule radius(40) + 10*/ + 2 * AcceptanceRadius)
    {
        OwnedEnemy->bShouldAttack = false;
        MoveToTarget(Player);
    }

    /*if(PlayerInfo) 
    {
        FVector PlayerLocation = PlayerInfo->GetLastStimulusLocation();
        UE_LOG(LogTemp, Warning, TEXT("Player position: X = %f | Y = %f | Z = %f"), PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
    }*/

    /*FVector FocalPoint = GetFocalPoint();
    UE_LOG(LogTemp, Warning, TEXT("AI's focal point: X = %f | Y = %f | Z = %f"), FocalPoint.X, FocalPoint.Y, FocalPoint.Z);*/
}
