// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Components/PrimitiveComponent.h"



void UTankTrackComponent::SetThrottle(float Throttle)
{
	
	
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto ForceAmount = RootComponent->GetMass() * DrivingSpeed * 100 * Throttle;
	auto ForceVector = ForceAmount * GetForwardVector();
	auto ForceLocation = GetComponentLocation();
	
	
	RootComponent->AddForceAtLocation(ForceVector, ForceLocation);
}