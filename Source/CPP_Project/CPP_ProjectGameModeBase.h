// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "CPP_ProjectGameModeBase.generated.h"

class UUserWidget;

UCLASS()
class CPP_PROJECT_API ACPP_ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ACPP_ProjectGameModeBase();

protected:

	virtual void BeginPlay() override;

protected:

	// Reference to the UMG asset selected in the editor
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> HUDWidget;

	UPROPERTY()
	UUserWidget* HUD;
};
