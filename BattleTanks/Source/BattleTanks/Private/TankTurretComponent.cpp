// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"


void UTankTurretComponent::Swivel(float RelativeDirection)
{
	RelativeDirection = FMath::Clamp<float>(RelativeDirection, -1.0f, 1.0f);
	auto DeltaRotation = RelativeDirection * SwivelSpeed * GetWorld()->DeltaTimeSeconds;
	auto NewRotationRaw = RelativeRotation.Yaw + DeltaRotation;
	//auto NewRotationClamped = FMath::Clamp<float>(NewRotationRaw, MinElevation, MaxElevation);
	UE_LOG(LogTemp, Warning, TEXT("INSIDE Swivel %f"), NewRotationRaw)
	SetRelativeRotation(FRotator(0, NewRotationRaw, 0));
}