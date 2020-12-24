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

	void EquipOn(class AMainWarrior* Player);

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMeshComponent* Weapon;
};
