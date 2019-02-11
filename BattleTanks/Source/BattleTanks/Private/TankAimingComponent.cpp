// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankProjectile.h"
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

void UTankAimingComponent::SetAimLow(bool AimLow)
{
	UseLowArc = AimLow;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (ensure(Barrel && Turret))
	{
		FVector StartLocation = Barrel->GetBarrelEndLocation();
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

void UTankAimingComponent::Initialize(UTankBarrelComponent * BarrelToSet, UTankTurretComponent* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (ensure(Barrel))
	{
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimRotator = AimDirection.Rotation();
		auto DeltaRotator = AimRotator - BarrelRotator;

		Barrel->Elevate(DeltaRotator.Pitch);
	}
}


void UTankAimingComponent::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFiredTime) >= ReloadTime;

	if (ensure(Barrel && ProjectileBlueprint) && IsReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, Barrel->GetBarrelEndLocation(), Barrel->GetForwardVector().Rotation());
		Projectile->Launch(ProjectileVelocity);
		LastFiredTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (ensure(Turret))
	{
		
		auto TurretRotator = Turret->GetForwardVector().Rotation();
		auto AimRotator = AimDirection.Rotation();
		auto DeltaRotator = AimRotator - TurretRotator;
		
		Turret->Swivel(DeltaRotator.Yaw);
	}
}