// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!IsFlying()) {

	
	if (!ensure(LeftTrack &&RightTrack)) { return; }
	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!IsFlying()) {

	
	if (!ensure(LeftTrack &&RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	}
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	//TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super as we're replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);

	auto TrunRightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(TrunRightThrow);
	IntendMoveForward(ForwardThrow);
	//UE_LOG(LogTemp, Warning, TEXT("Forward:%f,RightThrow:%f"), ForwardThrow,TrunRightThrow);
}
