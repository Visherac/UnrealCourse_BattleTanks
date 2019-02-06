// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackComponent;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float Magnitude);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrackComponent * RightTrackToSet, UTankTrackComponent * LeftTrackToSet);
	
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendRotateClockwise(float Magnitude);

private:
	UTankTrackComponent* RightTrack = nullptr;
	UTankTrackComponent* LeftTrack = nullptr;


};
