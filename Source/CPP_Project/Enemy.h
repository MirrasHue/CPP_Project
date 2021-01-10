// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class USphereComponent;

UCLASS()
class CPP_PROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ApplyDamageTo(class APawn* Pawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetIsAttacking(bool IsAttacking) { bIsAttacking = IsAttacking; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	UPROPERTY(EditAnywhere,  Category = "AI")
	UAnimMontage* CombatMontage;

	// Damage caused by this enemy when it successfully attacks
	UPROPERTY(EditAnywhere, Category = "Combat | Damage")
	float BaseDamage = 15.f;

	UPROPERTY(BlueprintReadOnly)
	bool bIsAlive = true;

public:

	bool bShouldAttack = false;
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, Category = "Combat | Health")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, Category = "Combat | Health")
	float MaxHealth = 100.f;
};
