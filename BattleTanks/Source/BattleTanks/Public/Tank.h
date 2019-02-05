// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrelComponent;
class UTankTurretComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrelComponent* Barrel);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurretComponent* Turret);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void SetUseLowerArc(bool UseLowerArc);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);
	
	//fire speed in cm.
	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileVelocity = 10000.0f;

	UPROPERTY(EditAnywhere, Category = Firing)
	bool UseLowerArc = true;
	
};


