// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"
//Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATankAIController::Tick(float DeltaTime)//TODO 想AITank等3秒再FIRE （现在是立即开火）
{
	Super::Tick(DeltaTime);
	if (ensure(GetPlayerTank()))
	{
		MoveToActor(GetPlayerTank(), AcceptanceRadius);

	auto PlayerTankLocation = GetPlayerTank()->GetActorLocation();
	if (ensure(GetPossessedTank()))
	{
	GetPossessedTank()->AimAt(PlayerTankLocation);
	GetPossessedTank()->Fire();
	}
	else
	{
	    //UE_LOG(LogTemp, Warning, TEXT(" %f No Fire!"), GetWorld()->GetTimeSeconds()); 
	}
	}
}

ATank* ATankAIController::GetPossessedTank() const
{
	if (GetPawn()){ return Cast<ATank>(GetPawn());}
	else 
	{
		
		return nullptr; 
	}
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
		//UE_LOG(LogTemp, Warning, TEXT("NoPlayerPawn found!"));
		return nullptr;
	}
}


