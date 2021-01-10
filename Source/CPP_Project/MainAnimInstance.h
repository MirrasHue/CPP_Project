// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"


UCLASS()
class CPP_PROJECT_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	/**
	 * Functions called by the engine whenever those notifiers are reached in our CombatMontage	
	 */
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_EnableWeaponHitbox();

	UFUNCTION()
	void AnimNotify_DisableWeaponHitbox();

	UFUNCTION()
	void AnimNotify_JumpEnd();
	// end notifiers

protected:

	UPROPERTY(BlueprintReadOnly)
	class AMainWarrior* Player;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bInAir;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsArmed;
};
