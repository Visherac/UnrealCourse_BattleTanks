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
class ATankProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrelComponent* BarrelToSet, UTankTurretComponent* TurretToSet);

	void SetAimLow(bool);

	void AimAt(FVector);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();


	
protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState AimingStatus = EFiringState::Locked;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	UTankBarrelComponent* Barrel = nullptr;
	UTankTurretComponent* Turret = nullptr;


	//Will use the lower arc for firing projecile, else use the higher arc.
	UPROPERTY(EditDefaultsOnly = True, Category = Firing)
	bool UseLowArc = true;

	//fire speed in cm.
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileVelocity = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<ATankProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.0f;

	double LastFiredTime = 0;

	void MoveBarrelTowards(FVector);

	void MoveTurretTowards(FVector AimDirection);

	bool IsBarrelMoving();

	FVector AimDirection;

};
