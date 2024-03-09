// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GravitationalBody.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
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
	SetActorTransform(Transform);
}

void AProjectile::UpdateVelocity(float DeltaTime)
{
	const FVector ProjectileLocation = GetTransform().GetLocation();

	for (const auto Body : GravitationalBodies)
	{
		const float Mass = Body->Mass;
		FVector BodyLocation = Body->GetTransform().GetLocation();
		FVector R = BodyLocation - ProjectileLocation;
		const float R2= FMath::Max(FVector::DistSquared(BodyLocation, ProjectileLocation), 0.000001f);
		Velocity += DeltaTime * R.GetUnsafeNormal() * Mass / R2;
	}
}

void AProjectile::Tick(float DeltaTime)
{
	constexpr size_t NumIter = 10;
	for (int i = 0; i < NumIter; ++i)
	{
		UpdatePosition(DeltaTime);
		UpdateVelocity(DeltaTime);
	}
}
