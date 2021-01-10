// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "MainWarrior.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Attack logic goes here
	/*if(CombatMontage && bShouldAttack && !bIsAttacking)
	{
		bIsAttacking = true;

		FString AttackSection = "Attack_" + FString::FromInt(FMath::RandRange(1, 2));

		PlayAnimMontage(CombatMontage, 1.f, FName(*AttackSection));
	}*/
}

void AEnemy::ApplyDamageTo(APawn* Pawn)
{
	Pawn->TakeDamage(BaseDamage, FDamageEvent(), GetController(), this);
}

float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if(Health <= 0.f)
	{
		bIsAlive = false;
		DetachFromControllerPendingDestroy();
		SetActorEnableCollision(false); // Disable all collisions for this actor
		SetLifeSpan(5.f); // Destroy this object after 5 seconds
	}

	return DamageAmount;
}
