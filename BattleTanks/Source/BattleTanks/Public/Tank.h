// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declarationss
class UTankAimingComponent;
class UTankBarrelComponent;
class ATankProjectile;
class UTankMovementComponent;
class UTankTurretComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	void AimAt(FVector HitLocation);

protected:
	UPROPERTY(BlueprintReadOnly, Category = Setup)
	UTankAimingComponent* TankAimingComponent = nullptr;
	
	//UPROPERTY(BlueprintReadOnly)
	//UTankMovementComponent* TankMovementComponent = nullptr;

	virtual void BeginPlay() override;

public:	
	//fire speed in cm.
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileVelocity = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<ATankProjectile> ProjectileBlueprint;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.0f;

private:
	UTankBarrelComponent* Barrel = nullptr;

	double LastFiredTime = 0;

};


