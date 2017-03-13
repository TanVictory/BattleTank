// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATankAIController::Tick(float DeltaTime)//TODO 想AITank等3秒再FIRE （现在是立即开火）
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
	auto PlayerTankLocation = GetPlayerTank()->GetActorLocation();
	if (GetPossessedTank())
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
	if (GetPawn()){ UE_LOG(LogTemp, Warning, TEXT(" %f AIPawn found!"), GetWorld()->GetTimeSeconds()); return Cast<ATank>(GetPawn());}
	else 
	{
		//UE_LOG(LogTemp, Warning, TEXT(" %f NoAIPawn found!"),GetWorld()->GetTimeSeconds());
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


