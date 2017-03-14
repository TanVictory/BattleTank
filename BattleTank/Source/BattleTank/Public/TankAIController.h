// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
private:
	ATank* GetPossessedTank() const;

	ATank* GetPlayerTank() const;

	ATank* PossessedTank;

	//How close can AITank Get
	float AcceptanceRadius = 3000.f;
};
