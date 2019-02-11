// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto TankPawn = GetControlledTank();
	if (!TankPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller is not controlling a ATank Pawn"))
	}

	auto AimingComponent = TankPawn->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		AimingComponentFound(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller's Pawn doesn't have a Tank AimingComponent"))
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
	if (!ensure(GetControlledTank())) {return;}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

//True if hits landscape, location of position hit
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	
	FVector LookDirection;
	if (GetLookDirection(LookDirection))
	{
		FHitResult CrosshairHit;
		FVector StartLocation = PlayerCameraManager->GetCameraLocation();
		FVector EndLocation = StartLocation + (LookDirection * RayTraceDistance);
		auto HitParams = FCollisionQueryParams("TankCrosshairCollision", false, GetPawn());
		bool WasHit = GetWorld()->LineTraceSingleByChannel(CrosshairHit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, HitParams);
		if (WasHit)
		{
			HitLocation = CrosshairHit.Location;
		}
		else
		{
			HitLocation = FVector(0);
		}
		return WasHit;
	}
	return false;
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