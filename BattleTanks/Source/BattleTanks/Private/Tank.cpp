// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "TankProjectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("TANK TRIED FIRED"))

	bool IsReloaded = (FPlatformTime::Seconds() - LastFiredTime) >= ReloadTime;

	if (ensure(Barrel && ProjectileBlueprint) && IsReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, Barrel->GetBarrelEndLocation(), Barrel->GetForwardVector().Rotation());
		Projectile->Launch(ProjectileVelocity);
		LastFiredTime = FPlatformTime::Seconds();
	}
}


void ATank::AimAt(FVector HitLocation)
{
	if (ensure(TankAimingComponent))
	{
		TankAimingComponent->AimAt(HitLocation, ProjectileVelocity);
	}	
}

