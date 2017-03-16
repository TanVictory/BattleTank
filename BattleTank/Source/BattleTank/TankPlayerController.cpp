// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("No Aiming component founded"))
	}
}

void ATankPlayerController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{

	}
	//Get World location of linetrace through crosshair
		//If it hits the landscape
			//Tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation)const
{
	//Find the crosshhair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	float CrossXLocation = ViewportSizeX*CrossHairXLocation;
	float CrossYLocation = ViewportSizeY*CrossHairYLocation;
	auto ScreenLocation=FVector2D(CrossXLocation, CrossYLocation);	

	//De-project the screen position of the crosshair to a world direction
	FVector WorldDirection, WorldLocation;
	if (DeprojectScreenPositionToWorld(CrossXLocation, CrossYLocation, WorldLocation, WorldDirection))
	{
		
	}

	
	//line-trace along that look direction , and see what we hit(up to max range)
	if (GetLookVectorHitLocation(WorldDirection, HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & LookDirection, FVector & HitLocation)const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}


