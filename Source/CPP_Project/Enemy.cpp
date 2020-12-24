// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
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

	if(CombatMontage && bShouldAttack && !bIsAttacking)
	{
		bIsAttacking = true;

		FString AttackSection = "Attack_" + FString::FromInt(FMath::RandRange(1, 2));

		PlayAnimMontage(CombatMontage, 1.f, FName(*AttackSection));
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
