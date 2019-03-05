// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Engine/World.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SprintConstraint"));
	SetRootComponent(SpringConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->AttachToComponent(SpringConstraint, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	WheelConstraint->AttachToComponent(Axle, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Axle, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if(GetAttachParentActor())
	{
		auto ParentRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		SpringConstraint->SetConstrainedComponents(ParentRoot, NAME_None, Axle, NAME_None);
		WheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
	}

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}



// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceThisFrame = 0;
	}
}

void ASprungWheel::AddDrivingForce(float ForwardMagnitude)
{
	UE_LOG(LogTemp, Warning, TEXT("AddForce %f"), ForwardMagnitude)
	TotalForceThisFrame += ForwardMagnitude;
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceThisFrame);
	UE_LOG(LogTemp, Warning, TEXT("Force Applied %f"), TotalForceThisFrame)
}
