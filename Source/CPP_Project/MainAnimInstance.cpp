// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainWarrior.h"
#include "Weapon.h"


void UMainAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if(!Player)
        Player = Cast<AMainWarrior>(TryGetPawnOwner());
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if(!Player)
        return;

    FVector Vel = Player->GetVelocity();
    
    MovementSpeed = FVector(Vel.X, Vel.Y, 0.f).Size(); // Get the magnitude of horizontal velocity

    bInAir = Player->GetMovementComponent()->IsFalling();

    bIsWeaponEquipped = Player->IsWeaponEquipped();
}

void UMainAnimInstance::AnimNotify_AttackEnd()
{
    if(Player)
        Player->SetIsAttacking(false);
}

void UMainAnimInstance::AnimNotify_EnableWeaponHitbox()
{
    if(!Player)
        return;

    if(Player->GetCurrentWeapon())
        Player->GetCurrentWeapon()->EnableHitbox();
}

void UMainAnimInstance::AnimNotify_DisableWeaponHitbox()
{
    if(!Player)
        return;

    if(Player->GetCurrentWeapon())
        Player->GetCurrentWeapon()->DisableHitbox();
}

void UMainAnimInstance::AnimNotify_JumpEnd()
{
    if(!Player)
        return;

    Player->SetCanJump(true);
}
