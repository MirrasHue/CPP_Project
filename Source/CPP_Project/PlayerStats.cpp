// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStats.h"
#include "Kismet/GameplayStatics.h"
#include "MainWarrior.h"


using PS = UPlayerStats; // Just for short

const AMainWarrior* PS::Player = nullptr;

void UPlayerStats::InitPlayerRef(UObject* WorldContextObject)
{
    PS::Player = Cast<AMainWarrior>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0));
}

float UPlayerStats::GetPlayerHealthPercent()
{
    if(!PS::Player)
        return 0.f;

    return PS::Player->Health / PS::Player->MaxHealth;
}

float UPlayerStats::GetPlayerStaminaPercent()
{
    if(!PS::Player)
        return 0.f;

    return PS::Player->Stamina / PS::Player->MaxStamina;
}
