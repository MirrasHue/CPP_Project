// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunctionUtils.h"
#include "Kismet/GameplayStatics.h"
#include "MainWarrior.h"

using BFU = UBlueprintFunctionUtils; // Just for short

AMainWarrior* BFU::Player = nullptr;

void UBlueprintFunctionUtils::InitPlayerRef(UObject* WorldContextObject)
{
    BFU::Player = Cast<AMainWarrior>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0));
}

float UBlueprintFunctionUtils::GetPlayerHealthPercent()
{
    if(! BFU::Player)
        return 0.f;

    return BFU::Player->Health / BFU::Player->MaxHealth;
}

float UBlueprintFunctionUtils::GetPlayerStaminaPercent()
{
    if(! BFU::Player)
        return 0.f;

    return BFU::Player->Stamina / BFU::Player->MaxStamina;
}
