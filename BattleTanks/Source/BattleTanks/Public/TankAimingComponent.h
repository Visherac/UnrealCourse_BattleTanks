// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};


//forward declarations
class UTankBarrelComponent;
class UTankTurretComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrelComponent*);
	void SetTurretReference(UTankTurretComponent*);
	void SetAimLow(bool);
	void AimAt(FVector, float);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState AimingStatus = EFiringState::Reloading;


private:
	UTankBarrelComponent* Barrel = nullptr;
	UTankTurretComponent* Turret = nullptr;

	
	//Will use the lower arc for firing projecile, else use the higher arc.
	bool UseLowArc = true;
	
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
};
