// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintFunctionUtils.generated.h"


UCLASS()
class CPP_PROJECT_API UBlueprintFunctionUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Called on MainWarrior_BP's event graph(Begin Play), given that there's no easy way to get a reference to the actual player from here
	UFUNCTION(BlueprintCallable, Category = "Helper Functions", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void InitPlayerRef(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Helper Functions")
	static float GetPlayerHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "Helper Functions")
	static float GetPlayerStaminaPercent();

public:

	static class AMainWarrior* Player;
};