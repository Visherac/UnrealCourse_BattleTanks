// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"


void UTankTurretComponent::Swivel(float RelativeDirection)
{
	RelativeDirection = FMath::Clamp<float>(RelativeDirection, -1.0f, 1.0f);
	auto DeltaRotation = RelativeDirection * SwivelSpeed * GetWorld()->DeltaTimeSeconds;
	auto NewRotationRaw = RelativeRotation.Yaw + DeltaRotation;

	SetRelativeRotation(FRotator(0, NewRotationRaw, 0));
}