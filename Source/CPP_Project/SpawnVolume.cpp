// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ASpawnVolume::GetPointToSpawn() const
{
	FVector BoxOrigin = SpawningBox->GetComponentLocation();
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();

	return UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);
}
