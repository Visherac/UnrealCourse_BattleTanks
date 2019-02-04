// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto tankPawn = GetControlledTank();
	if (!tankPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller is not controlling a ATank Pawn"))
	}
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {return;}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("hit location: %s"), *HitLocation.ToString())
	}


}

//True if hits landscape, location of position hit
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	
	FVector LookDirection;
	if (GetLookDirection(LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("look direction : %s"), *LookDirection.ToString())
	}
	

	return true;
}

//world direction as looking out crosshair
bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const
{
	///find location of crosshair in screen pixels
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ViewportCrosshairPosition(ViewportSizeX *CrosshairPercentageX, ViewportSizeY * CrosshairPercentageY);

	//deproject to world direction
	FVector WorldPosition;
	FVector WorldDirection;
	return DeprojectScreenPositionToWorld(ViewportCrosshairPosition.X, ViewportCrosshairPosition.Y, WorldPosition, LookDirection);
}