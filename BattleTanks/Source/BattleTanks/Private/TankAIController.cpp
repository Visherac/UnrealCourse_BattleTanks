// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "tank.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();	

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(PlayerTank))
	{
		//movement
		MoveToActor(PlayerTank, AcceptanceRadius);

		//aiming
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetAimingState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
		
	}
	
}

void ATankAIController::SetPawn(APawn * NewPawn)
{
	Super::SetPawn(NewPawn);

	if (NewPawn)
	{
		auto TankPawn = Cast<ATank>(NewPawn);
		if (ensure(TankPawn))
		{
			TankPawn->OnDeath.AddUniqueDynamic(this, &ATankAIController::HandleTankDeath);
		}
	}
}

void ATankAIController::HandleTankDeath()
{
	if (GetPawn())
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}