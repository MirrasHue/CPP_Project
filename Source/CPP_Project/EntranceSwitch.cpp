// Fill out your copyright notice in the Description page of Project Settings.


#include "EntranceSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEntranceSwitch::AEntranceSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->InitBoxExtent(FVector(40.f, 40.f, 20.f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = TriggerBox;

	Switch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch"));
	Switch->SetupAttachment(RootComponent);

	Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entrance"));
	Entrance->AddLocalOffset(GetActorLocation() + FVector(400.f, 0.f, 0.f));
	Entrance->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEntranceSwitch::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEntranceSwitch::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AEntranceSwitch::OnEndOverlap);

	EntranceOpenDirection = EntranceOpenDirection.GetSafeNormal();
}

// Called every frame
void AEntranceSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bSwitchPressed)
	{
		if(CurrentEntranceDisplacement < MaxEntranceDisplacement)
		{
			Entrance->AddWorldOffset(EntranceOpenDirection * EntranceOpeningSpeed * DeltaTime);
			CurrentEntranceDisplacement += EntranceOpeningSpeed * DeltaTime;
			//UE_LOG(LogTemp, Warning, TEXT("Opening Entrance"));
		}
	}
	else
	{
		if(CurrentEntranceDisplacement > 0.f)
		{
			Entrance->AddWorldOffset(-EntranceOpenDirection * EntranceClosingSpeed * DeltaTime);
			CurrentEntranceDisplacement -= EntranceClosingSpeed * DeltaTime;
			//UE_LOG(LogTemp, Warning, TEXT("Closing Entrance"));
		}
	}
}


void AEntranceSwitch::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlaping"));
	bSwitchPressed = true;
}

void AEntranceSwitch::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Not Overlaping"));
	bSwitchPressed = false;
}
