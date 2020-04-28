// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if(!Pawn)
        Pawn = TryGetPawnOwner();
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if(!Pawn)
        return;

    FVector Vel = Pawn->GetVelocity();
    // Get the magnitude of horizontal velocity
    MovementSpeed = FVector(Vel.X, Vel.Y, 0.f).Size();

    bInAir = Pawn->GetMovementComponent()->IsFalling();
}