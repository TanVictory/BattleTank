// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"
//Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Subscribe our local method to the tank gameover event
		PossessedTank->GameOver.AddUniqueDynamic(this,&ATankAIController::OnPossessedTankGameOver);
	}
}

void ATankAIController::OnPossessedTankGameOver()
{
	if (!(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)//TODO 想AITank等3秒再FIRE （现在是立即开火）
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

	auto PlayerTankLocation = PlayerTank->GetActorLocation();
	
	auto PossessedTank = GetPawn();
	if (ensure(PossessedTank))
	{
	auto AimComp = PossessedTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimComp))
	{
		//UE_LOG(LogTemp, Warning, TEXT(" %f No Fire!"), GetWorld()->GetTimeSeconds()); 
	}
	else
	{
		auto FireRadius = (PlayerTankLocation - PossessedTank->GetActorLocation()).Size();
		
		if(FMath::Abs<float>(FireRadius)<=AcceptanceRadius)
		{ 
		AimComp->AimAt(PlayerTankLocation,AimComp->ProjectileLaunchSpeed);
		AimComp->Fire();
	    }
	}
	 }
	}
}




