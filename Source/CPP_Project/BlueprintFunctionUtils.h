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
	
	static class AMainWarrior* PlayerOwner;

	// Called on MainWarrior_BP's event graph(Begin Play), the ptr wasn't being updated properly in these 2 functions below
	UFUNCTION(BlueprintCallable, Category = "Helper Functions", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void InitPlayerOwner(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Helper Functions")
	static float GetPlayerHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "Helper Functions")
	static float GetPlayerStaminaPercent();
};
