// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Components/PrimitiveComponent.h"


UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrackComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrackComponent::OnHit);
}

void UTankTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherHitComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}

void UTankTrackComponent::ApplySidewaysForce()
{
	//remove strafe slipping.
	//F = MA
	float SlippageAmount = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector SlippageCorrectionAcceleration = -SlippageAmount / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto SlippageCorrectionForce = TankRoot->GetMass() * SlippageCorrectionAcceleration / 2; // divide because 2 tank tracks
	TankRoot->AddForce(SlippageCorrectionForce);
}



void UTankTrackComponent::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, 1.0f);
}

void UTankTrackComponent::DriveTrack()
{
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto Force = DrivingForce * CurrentThrottle * GetForwardVector();
	auto ForceLocation = GetComponentLocation();

	RootComponent->AddForceAtLocation(Force, ForceLocation);
}
