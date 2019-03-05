// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Components/PrimitiveComponent.h"
#include "SprungWheel.h"
#include "SpawnComponent.h"


UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrackComponent::BeginPlay()
{
	Super::BeginPlay();
}


TArray<ASprungWheel*> UTankTrackComponent::GetWheels() const
{
	auto Wheels = TArray<ASprungWheel*>();
	auto Children = TArray<USceneComponent*>();
	GetChildrenComponents(true, Children);
	for (auto Child : Children)
	{
		auto SpawnChild = Cast<USpawnComponent>(Child);
		if (SpawnChild)
		{
			AActor* SpawnedActor = SpawnChild->GetSpawnedActor();
			if (SpawnedActor)
			{
				auto SprungWheelActor = Cast<ASprungWheel>(SpawnedActor);
				if (SprungWheelActor)
				{
					Wheels.Add(SprungWheelActor);
				}
			}
		}
	}
	return Wheels;
}

void UTankTrackComponent::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	DriveTrack(CurrentThrottle);
}

void UTankTrackComponent::DriveTrack(float CurrentThrottle)
{
	auto Force = DrivingForce * CurrentThrottle;
	auto Wheels = GetWheels();
	if (Wheels.Num() > 0)
	{
		auto ForcePerWheel = Force / Wheels.Num();
		for (auto Wheel : Wheels)
		{
			Wheel->AddDrivingForce(ForcePerWheel);
		}
	}
}
