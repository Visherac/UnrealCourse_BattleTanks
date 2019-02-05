// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrelComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurretComponent * TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::SetAimLow(bool AimLow)
{
	UseLowArc = AimLow;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float ProjectileVelocity)
{
	if (Barrel)  //ToDo barrel and turret
	{
		FVector StartLocation = Barrel->GetSocketLocation(FName("BarrelEnd"));//TODO remove dependency on socket name.
		FVector OutVelocity(0);

		bool bHasAim = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutVelocity,
			StartLocation,
			HitLocation,
			ProjectileVelocity,
			!UseLowArc,
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace);
		if( bHasAim)
		{
			auto AimDirection = OutVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
			MoveTurretTowards(AimDirection);
		}
		
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (Barrel)
	{
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimRotator = AimDirection.Rotation();
		auto DeltaRotator = AimRotator - BarrelRotator;

		Barrel->Elevate(DeltaRotator.Pitch);


	}
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (Turret)
	{
	}
}