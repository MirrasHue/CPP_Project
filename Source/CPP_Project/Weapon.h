// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class CPP_PROJECT_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:

	AWeapon();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EquipOn(class AMainWarrior* Player);

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	virtual void OnWeaponHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ApplyDamageTo(class APawn* Pawn);

public:

	// Enables/disables the Hitbox's collision
	FORCEINLINE void EnableHitbox();
	FORCEINLINE void DisableHitbox();

protected:

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, Category = "Weapon | Collision")
	UBoxComponent* Hitbox;

	UPROPERTY(EditAnywhere, Category = "Weapon | Damage")
	float LightAttackDamage = 15.f;

	UPROPERTY(EditAnywhere, Category = "Weapon | Damage")
	float HeavyAttackDamage = 25.f;

	bool bHitCounted = false; // Just to make sure that sword swing counts only once
};
