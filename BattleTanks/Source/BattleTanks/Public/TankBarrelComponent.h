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
	
	
private:
	
	UPROPERTY(EditAnywhere, Category = Barrel)
	float ElevationSpeed = 20.0f;

	UPROPERTY(EditAnywhere, Category = Barrel)
	float MinElevation = 0.0f;

	UPROPERTY(EditAnywhere, Category = Barrel)
	float MaxElevation = 40.0f;

	UPROPERTY(EditAnywhere, Category = Barrel)
	FName BarrelEndSocket = "";

};
