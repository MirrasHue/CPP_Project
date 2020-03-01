// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "UnrealMathUtility.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloater::AFloater()
		:
	bShouldFloat(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	if(SetRootComponent(MyMesh))
	{
		
	}

}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bShouldFloat)
	{
		FHitResult HitResult;

		/* This function will add a certain amount to this actor's location every Tick 
		   If bSweep is set to true, collision will be enable even though SimulatePhysics was turned off */
		AddActorLocalOffset(InitialDirection, true, &HitResult);

		/* Now, if we want to know the location of a collision, we can do this: */
		FVector HitLocation = HitResult.Location;

		UE_LOG(LogTemp, Warning, TEXT("Hit Location: X = %f | Y = %f | Z = %f"), 
				HitLocation.X, HitLocation.Y, HitLocation.Z);
	}
	

}

