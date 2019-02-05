// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

class UStaticMeshSocket;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 means down, 1 means up. 0 means don't elevate ...etc
	void Elevate(float RelativeDirection);

	FVector GetBarrelEndLocation() const;
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = Barrel)
	float ElevationSpeed = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = Barrel)
	float MinElevation = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = Barrel)
	float MaxElevation = 40.0f;

	UPROPERTY(EditDefaultsOnly, Category = Barrel)
	FName BarrelEndSocket = "";

};
