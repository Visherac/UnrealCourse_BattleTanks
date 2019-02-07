// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"


void UTankMovementComponent::Initialize(UTankTrackComponent* RightTrackToSet, UTankTrackComponent* LeftTrackToSet)
{
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Magnitude)
{
	if (RightTrack && LeftTrack)
	{
		RightTrack->SetThrottle(Magnitude);
		LeftTrack->SetThrottle(Magnitude);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool ForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto TankRight = GetOwner()->GetActorRightVector().GetSafeNormal();
	auto IntendedMove = MoveVelocity.GetSafeNormal();
	float TankForwardAmount = FVector::DotProduct(TankForward, IntendedMove);
	float TankRightAmount = FVector::DotProduct(TankRight, IntendedMove);

	IntendMoveForward(TankForwardAmount);
	IntendRotateClockwise(TankRightAmount);

	//UE_LOG(LogTemp, Warning, TEXT("Moving AI, %s"), *MoveVelocity.ToString())
}

void UTankMovementComponent::IntendRotateClockwise(float Magnitude)
{
	if (RightTrack && LeftTrack)
	{
		RightTrack->SetThrottle(-Magnitude);
		LeftTrack->SetThrottle(Magnitude);
	}
}