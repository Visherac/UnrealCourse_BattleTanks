// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProjectile.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATankProjectile::ATankProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	MovementComponent->bAutoActivate = false;
	
	LaunchParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchParticle->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactParticle->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactParticle->bAutoActivate = false;

	ImpactForce = CreateDefaultSubobject<URadialForceComponent>(FName("Impact Force"));
	ImpactForce->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

}


// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &ATankProjectile::OnHit);
}

void ATankProjectile::Launch(float Velocity)
{
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Velocity);
	MovementComponent->Activate();
}

void ATankProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherHitComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	
	LaunchParticle->Deactivate();
	ImpactParticle->Activate();
	ImpactForce->FireImpulse();

	///remove collision mesh instantly to stop collision bugs
	SetRootComponent(ImpactForce);
	CollisionMesh->DestroyComponent();

	///apply Damage
	UGameplayStatics::ApplyRadialDamage(this, DamageAmount, GetActorLocation(), ImpactForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());

	///Remove the rest/particles after a destroy delay
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATankProjectile::OnHitTimerEnd, DestroyDelay);
}

void ATankProjectile::OnHitTimerEnd()
{
	Destroy();
}


