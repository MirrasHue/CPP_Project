// Fill out your copyright notice in the Description page of Project Settings.


#include "EntranceSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEntranceSwitch::AEntranceSwitch()
		:
	MaxEntranceDisplacement(500.f),
	CurrentEntranceDisplacement(0.f),
	EntranceOpeningSpeed(10.f),
	EntranceClosingSpeed(10.f),
	bSwitchPressed(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->InitBoxExtent(FVector(60.f, 60.f, 30.f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = TriggerBox;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEntranceSwitch::OverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AEntranceSwitch::OverlapEnd);

	Switch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch"));
	Switch->SetupAttachment(RootComponent);

	Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entrance"));
	Entrance->AddLocalOffset(GetActorLocation() + FVector(200.f, 0.f, 0.f));
	Entrance->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEntranceSwitch::BeginPlay()
{
	Super::BeginPlay();

	InitialEntranceLocation = Entrance->GetComponentLocation();
	EntranceMoveDirection = EntranceMoveDirection.GetClampedToSize(-1.f, 1.f);
}

// Called every frame
void AEntranceSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bSwitchPressed)
	{
		if(CurrentEntranceDisplacement <= MaxEntranceDisplacement)
		{
			Entrance->AddLocalOffset(EntranceMoveDirection * EntranceOpeningSpeed * DeltaTime);
			CurrentEntranceDisplacement += EntranceMoveDirection.Size() * EntranceOpeningSpeed * DeltaTime;
			FMath::Clamp(CurrentEntranceDisplacement, 0.f, MaxEntranceDisplacement);
			UE_LOG(LogTemp, Warning, TEXT("Opening Entrance"));
		}
	}

	if(!bSwitchPressed)
	{
		if(CurrentEntranceDisplacement > 0.f)
		{
			Entrance->AddLocalOffset(-(EntranceMoveDirection * EntranceClosingSpeed * DeltaTime));
			CurrentEntranceDisplacement -= EntranceMoveDirection.Size() * EntranceClosingSpeed * DeltaTime;
			FMath::Clamp(CurrentEntranceDisplacement, 0.f, MaxEntranceDisplacement);
			UE_LOG(LogTemp, Warning, TEXT("Closing Entrance"));
		}
	}
}


void AEntranceSwitch::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlaping"));
	bSwitchPressed = true;
}

void AEntranceSwitch::OverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Not Overlaping"));
	bSwitchPressed = false;
}
