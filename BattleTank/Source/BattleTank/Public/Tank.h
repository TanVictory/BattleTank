// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector& HitLocation);

	UFUNCTION(BlueprintCallable,Category="Tank Setup")
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Tank Setup")
	void SetTurretReference(UTankTurret* TurretToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Setup Input")
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Setup Input")
	UTankMovementComponent* TankMovementComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 6000.f; //TODO find sensible default
	
	

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;//Alternative TSubclassof

	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float FireCooldown = 3.f;

	float LastFireTime = 0;
};
