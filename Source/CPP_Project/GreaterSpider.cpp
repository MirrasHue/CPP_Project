// Fill out your copyright notice in the Description page of Project Settings.


#include "GreaterSpider.h"
#include "Components/BoxComponent.h"
#include "MainWarrior.h"


AGreaterSpider::AGreaterSpider()
{
    LeftClawHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftClawHitbox"));
    LeftClawHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("LeftClawSocket"));

    LeftClawHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LeftClawHitbox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftClawHitbox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftClawHitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

    RightClawHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightClawHitbox"));
    RightClawHitbox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightClawSocket"));

    RightClawHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RightClawHitbox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightClawHitbox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightClawHitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AGreaterSpider::BeginPlay()
{
	Super::BeginPlay();
	
	LeftClawHitbox->OnComponentBeginOverlap.AddDynamic(this, &AGreaterSpider::OnLeftClawHit);
    RightClawHitbox->OnComponentBeginOverlap.AddDynamic(this, &AGreaterSpider::OnRightClawHit);
}

// Called every frame
void AGreaterSpider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Attack logic
	if(CombatMontage && bShouldAttack && !bIsAttacking)
	{
		bIsAttacking = true;

		FString AttackSection = "Attack_" + FString::FromInt(FMath::RandRange(1, 2));

		PlayAnimMontage(CombatMontage, 1.f, FName(*AttackSection));
	}
}

void AGreaterSpider::OnLeftClawHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AMainWarrior* Player = Cast<AMainWarrior>(OtherActor);

    if(!Player || bHitCounted)
        return;

    bHitCounted = true;

    ApplyDamageTo(Player);

    UE_LOG(LogTemp, Warning, TEXT("PLAYER HEALTH = %f"), Player->Health);
}

void AGreaterSpider::OnRightClawHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AMainWarrior* Player = Cast<AMainWarrior>(OtherActor);

    if(!Player || bHitCounted)
        return;

    bHitCounted = true;

    ApplyDamageTo(Player);

    UE_LOG(LogTemp, Warning, TEXT("PLAYER HEALTH = %f"), Player->Health);
}

void AGreaterSpider::EnableClawHitbox()
{
    FName SpiderAnimSection = GetMesh()->GetAnimInstance()->Montage_GetCurrentSection();

    if(SpiderAnimSection == FName("Attack_1"))
        LeftClawHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    else
        RightClawHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AGreaterSpider::DisableClawHitbox()
{
    // No need to worry which one is active, the one already disabled will suffer no changes
    LeftClawHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RightClawHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    bHitCounted = false;
}
