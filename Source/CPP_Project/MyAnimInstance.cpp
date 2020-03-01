// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
    if(!Pawn)
        Pawn = TryGetPawnOwner();
}

void UMyAnimInstance::UpdateAnimations()
{
    if(Pawn)
    {
        FVector Speed = Pawn->GetVelocity();
        // Get the magnitude of horizontal velocity
        MovementSpeed = FVector(Speed.X, Speed.Y, 0.f).Size();

        bInAir = Pawn->GetMovementComponent()->IsFalling();
    }
    else
        Pawn = TryGetPawnOwner();
}