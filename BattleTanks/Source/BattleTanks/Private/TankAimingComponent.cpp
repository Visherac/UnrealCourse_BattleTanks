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

void UTankAimingComponent::Initialize(UTankBarrelComponent * BarrelToSet, UTankTurretComponent* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFiredTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFiredTime) < ReloadTime)
	{
		AimingStatus = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		AimingStatus = EFiringState::Aiming;
	}
	else
	{
		AimingStatus = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01f);
}

void UTankAimingComponent::SetAimLow(bool AimLow)
{
	UseLowArc = AimLow;
}

void UTankAimingComponent::Fire()
{
	

	if (ensure(Barrel) && ensure(ProjectileBlueprint) && AimingStatus != EFiringState::Reloading)
	{
		auto Projectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, Barrel->GetBarrelEndLocation(), Barrel->GetForwardVector().Rotation());
		Projectile->Launch(ProjectileVelocity);
		LastFiredTime = FPlatformTime::Seconds();
	}
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
			AimDirection = OutVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
			MoveTurretTowards(AimDirection);
		}
		
	}
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

EFiringState UTankAimingComponent::GetAimingState() const
{
	return AimingStatus;
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (ensure(Turret))
	{
		
		auto TurretRotator = Turret->GetForwardVector().Rotation();
		auto AimRotator = AimDirection.Rotation();
		auto DeltaRotator = AimRotator - TurretRotator;
		

		if (DeltaRotator.Yaw)
		{
			Turret->Swivel(DeltaRotator.Yaw);
		}
		else
		{
			Turret->Swivel( - DeltaRotator.Yaw);
		}
	}
}