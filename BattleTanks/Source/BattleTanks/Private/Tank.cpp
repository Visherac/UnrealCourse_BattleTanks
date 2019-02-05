// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "TankProjectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	TankAimingComponent->SetAimLow(UseLowerArc);
}

void ATank::SetBarrelReference(UTankBarrelComponent* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurretComponent* Turret)
{
	TankAimingComponent->SetTurretReference(Turret);
}

void ATank::SetUseLowerArc(bool value)
{
	TankAimingComponent->SetAimLow(value);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("TANK FIRED"))
	if (Barrel)
	{
		GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, Barrel->GetBarrelEndLocation(), Barrel->GetForwardVector().Rotation());
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, ProjectileVelocity);
}

