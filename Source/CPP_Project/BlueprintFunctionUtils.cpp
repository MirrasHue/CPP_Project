// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunctionUtils.h"
#include "Kismet/GameplayStatics.h"
#include "MainWarrior.h"


AMainWarrior* UBlueprintFunctionUtils::PlayerOwner = nullptr;

/* Unfortunately it doesn't work here (also tried typedef), 
   so I'll have to fully specify the player pointer...*/
//using Player = UBlueprintFunctionUtils::PlayerOwner;

/* ... or I can do this, but I'd prefer the solution with 'using' as
   an alias rather than a new variable (a global one to be worse)*/
auto Player = UBlueprintFunctionUtils::PlayerOwner;

void UBlueprintFunctionUtils::InitPlayerOwner(UObject* WorldContextObject)
{
    Player = Cast<AMainWarrior>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0));
}

float UBlueprintFunctionUtils::GetPlayerHealthPercent()
{
    if(! Player)
        return 0.f;

    return Player->Health / Player->MaxHealth;
}

float UBlueprintFunctionUtils::GetPlayerStaminaPercent()
{
    if(! Player)
        return 0.f;

    return Player->Stamina / Player->MaxStamina;
}
