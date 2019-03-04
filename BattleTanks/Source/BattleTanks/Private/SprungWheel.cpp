// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint"));
	SetRootComponent(Constraint);

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));	
	Mass->AttachToComponent(Constraint, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Constraint, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

