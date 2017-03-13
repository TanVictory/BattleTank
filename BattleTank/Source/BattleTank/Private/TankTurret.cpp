// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotateChange = ClampedRelativeSpeed*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto RawRotation = RelativeRotation.Yaw + RotateChange;
	SetRelativeRotation(FRotator(0, RawRotation, 0));
}

