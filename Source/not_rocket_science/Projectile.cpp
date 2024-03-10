// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GravitationalBody.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsDestroyed = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGravitationalBody::StaticClass(), FoundActors);

	GravitationalBodies.Empty();
	for (AActor* Actor : FoundActors)
	{
		GravitationalBodies.Add(Cast<AGravitationalBody>(Actor));
	}
}

void AProjectile::SetVelocity(FVector NewVelocity)
{
	Velocity = NewVelocity;
}

void AProjectile::UpdatePosition(float DeltaTime)
{
	FTransform Transform = GetTransform();
	FVector Position = GetTransform().GetLocation();
	Position += Velocity * DeltaTime;
	Transform.SetLocation(Position);
	FHitResult HitResult;
	SetActorTransform(Transform, true, &HitResult);
	if (HitResult.bBlockingHit)
	{
		Explode();
	}
}

void AProjectile::UpdateVelocity(float DeltaTime)
{
	const FVector ProjectileLocation = GetTransform().GetLocation();

	for (const auto Body : GravitationalBodies)
	{
		const float Mass = Body->Mass;
		FVector BodyLocation = Body->GetTransform().GetLocation();
		FVector R = BodyLocation - ProjectileLocation;
		const float R2 = FMath::Max(FVector::DistSquared(BodyLocation, ProjectileLocation), 0.000001f);
		Velocity += DeltaTime * R.GetUnsafeNormal() * Mass / R2;
	}
}

void AProjectile::Tick(float DeltaTime)
{
	constexpr float FixedTimeStep = 0.001f;
	TimeToAdvance += DeltaTime * 10.0f;

	while (TimeToAdvance > FixedTimeStep && !bIsDestroyed)
	{
		UpdatePosition(FixedTimeStep);
		UpdateVelocity(FixedTimeStep);
		TimeToAdvance -= FixedTimeStep;
	}
}

void AProjectile::Explode()
{
	bIsDestroyed = true;
	Destroy();

	const FVector ProjectileLocation = GetTransform().GetLocation();
	const FRotator Rotator{90.0, 0.0, 0.0};
	GetWorld()->SpawnActor(ExplosionActor, &ProjectileLocation, &Rotator);
}
