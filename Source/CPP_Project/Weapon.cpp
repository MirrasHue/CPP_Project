// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MainWarrior.h"

AWeapon::AWeapon()
{
    Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
    Weapon->SetupAttachment(RootComponent);
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

void AWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Super::OnEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	
}