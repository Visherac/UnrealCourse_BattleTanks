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

void UTankMovementComponent::IntendRotateClockwise(float Magnitude)
{
	if (RightTrack && LeftTrack)
	{
		RightTrack->SetThrottle(-Magnitude);
		LeftTrack->SetThrottle(Magnitude);
	}
}