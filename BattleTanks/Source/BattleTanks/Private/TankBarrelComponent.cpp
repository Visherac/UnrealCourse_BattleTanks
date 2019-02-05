// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"


void UTankBarrelComponent::Elevate(float RelativeDirection)
{
	RelativeDirection = FMath::Clamp<float>(RelativeDirection, -1.0f, 1.0f);
	auto DeltaRotation = RelativeDirection * ElevationSpeed * GetWorld()->DeltaTimeSeconds;
	auto NewRotationRaw = RelativeRotation.Pitch + DeltaRotation;
	auto NewRotationClamped = FMath::Clamp<float>(NewRotationRaw, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(NewRotationClamped, 0, 0));

}

FVector UTankBarrelComponent::GetBarrelEndLocation() const
{
	return GetSocketLocation(BarrelEndSocket);
}
