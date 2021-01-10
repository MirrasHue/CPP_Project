// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"


UCLASS()
class CPP_PROJECT_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	// Called by the engine whenever this notifier is reached in our enemy combat montage
	UFUNCTION()
	void AnimNotify_AttackEnd();

protected:

	UPROPERTY(BlueprintReadOnly)
	class AEnemy* Enemy;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;
};
