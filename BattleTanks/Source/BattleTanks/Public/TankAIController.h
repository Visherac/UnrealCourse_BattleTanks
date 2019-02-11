// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

private:
	
	//how clost can the tank get before it stops moving.
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float AcceptanceRadius = 3000; 

	UPROPERTY(EditDefaultsOnly, Category = Aiming)
	UTankAimingComponent* AimingComponent = nullptr;

};
