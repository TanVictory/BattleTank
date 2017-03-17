// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * Responsible for helping the player aim
 */

class ATankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float Deltatime) override;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.333333f;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	/*Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world*/
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	//bool GetLookDirection();

	bool GetLookVectorHitLocation(FVector& LookDirection,FVector& HitLocation) const;

	float LineTraceRange = 1000000.f;
};
