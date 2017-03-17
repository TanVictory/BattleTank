// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

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

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

    UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ProjectileLaunchSpeed = 6000.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly,Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;
private:
	
	


	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;//Alternative TSubclassof

	UPROPERTY(EditAnywhere, Category = "Firing")
	float FireCooldown = 3.f; //

	float LastFireTime = 0;
	
};
