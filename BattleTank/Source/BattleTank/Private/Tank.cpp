// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	UE_LOG(LogTemp, Warning, TEXT("Donkey :c++ Construct"));
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	UE_LOG(LogTemp, Warning, TEXT("Donkey :c++ beginplay"));
}



void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool IsReadyToFire = (GetWorld()->GetTimeSeconds() - LastFireTime) > FireCooldown;
	if (IsReadyToFire) {  
	auto SpawnLocation = Barrel->GetSocketLocation(FName("FirePoint"));
	auto SpawnRotation = Barrel->GetSocketRotation(FName("FirePoint"));
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		return;
	}
}

void ATank::AimAt(FVector& HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
}
