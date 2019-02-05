// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

private:
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(FVector & LookDirection) const;
	
	UPROPERTY(EditDefaultsOnly)
	float CrosshairPercentageX = .5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairPercentageY = .332f;

	UPROPERTY(EditDefaultsOnly)
	float RayTraceDistance = 1000000.0f;
	
};
