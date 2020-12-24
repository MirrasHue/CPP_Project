// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ProjectGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"


ACPP_ProjectGameModeBase::ACPP_ProjectGameModeBase()
{
    // Find and set MainWarrior_BP as the default pawn class

    static ConstructorHelpers::FClassFinder<APawn> 
        PawnFinder(TEXT("Blueprint'/Game/Character/MainWarrior_BP.MainWarrior_BP_C'"));
        
    DefaultPawnClass = PawnFinder.Class;
}

void ACPP_ProjectGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if(!HUDWidget)
        return;

    // Create the widget and make it visible on screen

    HUD = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);

    HUD->AddToViewport();
    HUD->SetVisibility(ESlateVisibility::Visible);
}