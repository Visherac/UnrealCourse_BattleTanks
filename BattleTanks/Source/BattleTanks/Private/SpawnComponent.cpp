// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(SpawnClass)
	{
		SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
		if (SpawnedActor)
		{
			SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Spawn Component: unable to spawn object"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Spawn Component: doesn't have valid class to Spawn"));
	}
	

}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor * USpawnComponent::GetSpawnedActor() const
{
	return SpawnedActor;
}

