// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPP_PROJECT_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UFUNCTION()
	void AnimNotify_AttackEnd(); // Called by the engine whenever this notifier is reached in our CombatMontage

protected:

	UPROPERTY()
	class AMainWarrior* Player;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bInAir;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsArmed;
};
