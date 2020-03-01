// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ProjectGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

ACPP_ProjectGameModeBase::ACPP_ProjectGameModeBase()
{
    static ConstructorHelpers::FClassFinder<APawn> 
        PlayerClassPawnFinder(TEXT("Class'/Script/CPP_Project.MainWarrior'"));
        
    DefaultPawnClass = PlayerClassPawnFinder.Class;
}