// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	//UE_LOG(LogTemp,Warning,TEXT("Donkey :Component Construct"))
	// ...
}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	//Super::BeginPlay();

	// ...
	//UE_LOG(LogTemp, Warning, TEXT("Donkey :Component BeginPlay"))
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tick Tick"))
	if (RoundsLeft <= 0)
	{
		RoundsLeft = 0;
		FiringStatus = EFiringStatus::Reloading;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) > FireCooldown)
	{
		FiringStatus = EFiringStatus::Aiming;
				
	}
}

void UTankAimingComponent::AimAt(FVector & HitLocation,float LaunchSpeed)
{
	
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FirePoint"));
	
	//Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
		this, 
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)
		)
	{
		auto AimAtSpeed = OutLaunchVelocity.GetSafeNormal();
		
		MoveBarrelTowards(AimAtSpeed);
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f AimSolution found"), Time);
	}
	else
	{
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f AimSolution not found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!ensure(Turret&&Barrel)){ return; }//if (!ensure(Turret)||!ensure(Barrel))
	//Work-out different between current barrel rotation,and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("%s AimDirection  is : %s"), *GetOwner()->GetName(), *AimAsRotator.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s DeltaRotator.Pitch  is : %f"), *GetOwner()->GetName(), DeltaRotator.Yaw);
	
	if (FMath::Abs<float>(DeltaRotator.Yaw) < 180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
	else if(DeltaRotator.Yaw>180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw-360.f);
	}
	else if (DeltaRotator.Yaw < -180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw + 360.f);
	}
	
	Barrel->Elevate(DeltaRotator.Pitch); 

}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	

	
	//bool IsReadyToFire = (GetWorld()->GetTimeSeconds() - LastFireTime) > FireCooldown;
	if (FiringStatus == EFiringStatus::Locked|| FiringStatus == EFiringStatus::Aiming)
	{
		auto SpawnLocation = Barrel->GetSocketLocation(FName("FirePoint"));
		auto SpawnRotation = Barrel->GetSocketRotation(FName("FirePoint"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		FiringStatus = EFiringStatus::Reloading;
		RoundsLeft--;
	}
	else
	{
		return;
	}
	
}