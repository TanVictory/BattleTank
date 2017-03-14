// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible from driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "Setup Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup Input")
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup Input")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
		
private:
	/** path following: request new velocity Called from the pathfinding logic by the AI controllers*/
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
