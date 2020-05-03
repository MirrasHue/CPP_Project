// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainWarrior.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if(!Player)
        Player = Cast<AMainWarrior>(TryGetPawnOwner());
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if(!Player)
        return;

    FVector Vel = Player->GetVelocity();
    
    MovementSpeed = FVector(Vel.X, Vel.Y, 0.f).Size(); // Get the magnitude of horizontal velocity

    bInAir = Player->GetMovementComponent()->IsFalling();

    bIsArmed = (Player->GetCurrentWeapon() != nullptr);
}

void UMyAnimInstance::AnimNotify_AttackEnd()
{
    if(Player)
        Player->IsAttacking(false);
}