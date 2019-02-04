// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto tankPawn = GetControlledTank();
	
	if (tankPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller Created, controlling tank %s"), *(tankPawn->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller is not controlling a ATank Pawn"))
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


