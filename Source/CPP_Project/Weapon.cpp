// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MainWarrior.h"
#include "Enemy.h"


AWeapon::AWeapon()
{
    Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
    Weapon->SetupAttachment(RootComponent);

    Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
    Hitbox->SetupAttachment(Weapon);

    Hitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Hitbox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Hitbox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Hitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponHit);
}

void AWeapon::EquipOn(AMainWarrior* Player)
{
    if(!Player)
        return;
    
    // So that the weapon doesn't cause the camera to zoom in when it passes through the spring arm
    Weapon->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
    Weapon->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); // Ignore collision with the player as well

    Weapon->SetSimulatePhysics(false); // For when it is being attached to player

    const USkeletalMeshSocket* RightHandSocket = Player->GetMesh()->GetSocketByName("RightHandSocket");

    if(RightHandSocket)
        RightHandSocket->AttachActor(this, Player->GetMesh());
}

void AWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if(AMainWarrior* Player = Cast<AMainWarrior>(OtherActor))
    {
        EquipOn(Player);
        Player->SetCurrentWeapon(this);
    }
}

void AWeapon::OnWeaponHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AEnemy* Enemy = Cast<AEnemy>(OtherActor);

    if(!Enemy || bHitCounted)
        return;

    bHitCounted = true;

    ApplyDamageTo(Enemy);
}

void AWeapon::ApplyDamageTo(APawn* Pawn)
{
    ACharacter* Player = GetWorld()->GetFirstPlayerController()->GetCharacter();

    if(!Player)
        return;

    // See which attack animation is playing, so that we can determine the appropriate damage 

    FName PlayerAnimSection = Player->GetMesh()->GetAnimInstance()->Montage_GetCurrentSection();

    if(PlayerAnimSection == FName("LightAttack"))
    {
        Pawn->TakeDamage(LightAttackDamage, FDamageEvent(), Player->GetController(), this);
    }
    else
    if(PlayerAnimSection == FName("HeavyAttack"))
    {
        Pawn->TakeDamage(HeavyAttackDamage, FDamageEvent(), Player->GetController(), this);
    }
}

void AWeapon::EnableHitbox() 
{
    Hitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AWeapon::DisableHitbox()
{
    Hitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    bHitCounted = false;
}
