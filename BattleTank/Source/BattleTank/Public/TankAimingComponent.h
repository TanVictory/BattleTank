// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward Declaration
class UTankBarrel; 
class UTankTurret;

UENUM()
enum class EFiringStatus : uint8 
{	Locked,
	Aiming,
	Reloading
};

//Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector& HitLocation,float LaunchSpeed);

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void SetTurretReference(UTankTurret* TurretToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly,Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;
private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
	
	float ProjectileLaunchSpeed = 0.f;

	void MoveBarrelTowards(FVector AimDirection);

	
};
