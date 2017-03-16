// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector& HitLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Setup Input")
	UTankAimingComponent* TankAimingComponent = nullptr;



public:	

    UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 6000.f; //TODO find sensible default
	
	

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;//Alternative TSubclassof

	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; //TODO Remove

	UPROPERTY(EditAnywhere, Category = "Firing")
	float FireCooldown = 3.f; //

	float LastFireTime = 0;
};
