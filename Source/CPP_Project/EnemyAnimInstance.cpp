// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "Enemy.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if(!Enemy)
        Enemy = Cast<AEnemy>(TryGetPawnOwner());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if(!Enemy)
        return;

    FVector Vel = Enemy->GetVelocity();
    
    MovementSpeed = FVector(Vel.X, Vel.Y, 0.f).Size(); // Get the magnitude of horizontal velocity
}

void UEnemyAnimInstance::AnimNotify_AttackEnd()
{
    if(Enemy)
        Enemy->IsAttacking(false);
}
