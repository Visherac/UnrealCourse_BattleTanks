// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankProjectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANKS_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void Launch(float);

private:
	UProjectileMovementComponent* MovementComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* LaunchParticle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* ImpactParticle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	URadialForceComponent* ImpactForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float DestroyDelay = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float DamageAmount = 25.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherHitComponent, FVector NormalImpulse, const FHitResult &HitResult);

	void OnHitTimerEnd();

};
