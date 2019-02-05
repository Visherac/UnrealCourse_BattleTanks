// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	//-1 means counterclockwise, 1 means clockwise. 0 means no movement ...etc
	void Swivel(float RelativeDirection);

private:

	UPROPERTY(EditAnywhere, Category = Turret)
	float SwivelSpeed = 50.0f;
};
