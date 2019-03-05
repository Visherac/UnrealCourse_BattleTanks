// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
 * 
 */
class ASprungWheel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UTankTrackComponent();

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	
	// in meters per second
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float DrivingForce = 40000000.0;


protected:
	virtual void BeginPlay() override;

	TArray<ASprungWheel*> GetWheels() const;

private:
	
	void DriveTrack(float CurrentThrottle);

};
