// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the barrel the right amount this frame
	//Given a max elevation speed , and the frame time
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = ClampedRelativeSpeed*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto RawRotation = RelativeRotation.Pitch + ElevationChange;
	auto ClampRotation = FMath::Clamp<float>(RawRotation, Minelevation, Maxelevation);
	SetRelativeRotation(FRotator(ClampRotation, 0, 0));
}


