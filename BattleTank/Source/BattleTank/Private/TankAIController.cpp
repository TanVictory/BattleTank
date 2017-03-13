// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
	auto PlayerTankLocation = GetPlayerTank()->GetActorLocation();
	GetPossessedTank()->AimAt(PlayerTankLocation);
	}
	GetPossessedTank()->Fire();
}

ATank* ATankAIController::GetPossessedTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		return Cast<ATank>(PlayerPawn);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NoPlayerPawn found!"));
		return nullptr;
	}
}


