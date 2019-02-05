// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	auto playerTank = GetPlayerTank();
	
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI controlled, has no tank pawn."), *controlledTank->GetName())
	}
	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank %s , can't find player tank"), *this->GetName())
	}

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetControlledTank() && GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerTank)
	{
		return nullptr;
	}
	return Cast<ATank>(playerTank);
}
