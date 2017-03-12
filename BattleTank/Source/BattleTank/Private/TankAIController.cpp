// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PossessedPawn = GetPossessedTank();
	if (PossessedPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is possessed : %s"), *PossessedPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is  not possessed "));
	}
	

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank is : %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank is  not found "));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
	auto PlayerTankLocation = GetPlayerTank()->GetActorLocation();
	GetPossessedTank()->AimAt(PlayerTankLocation);
	}
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

bool ATankAIController::AimatPlayer() const
{
	return false;
}
