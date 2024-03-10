// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion.h"

#include "Target.h"

AExplosion::AExplosion()
{
	PrimaryActorTick.bCanEverTick = true;
	ExplosionMesh = CreateDefaultSubobject<UStaticMeshComponent>("ExplosionMesh");
	RootComponent = ExplosionMesh; 
}

void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	NormalizedTimer = 0.0;
	CurrentScale = FMath::Lerp(StartScale, EndScale, NormalizedTimer);

	ExplosionMesh->SetRelativeScale3D(FVector::One() * CurrentScale);
	bDamaging = true;
}

void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NormalizedTimer += DeltaTime / ExpansionTime;
	
	CurrentScale = FMath::Lerp(StartScale, EndScale, FMath::Min(NormalizedTimer, 1.0f));

	if (bDamaging && CurrentScale > DamageMaxScale)
	{
		ExplosionMesh->SetRelativeScale3D(FVector::One() * DamageMaxScale);
		DealDamage();

		bDamaging = false;
	}

	ExplosionMesh->SetRelativeScale3D(FVector::One() * CurrentScale);

	if (bDamaging)
	{
		DealDamage();
	}
	
	if (NormalizedTimer >= 1.0)
	{
		Destroy();
	}
}

void AExplosion::DealDamage()
{
	TArray<AActor*> OverlappingActors;
	ExplosionMesh->GetOverlappingActors(OverlappingActors, ATarget::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		Cast<ATarget>(Actor)->Kill();
	}
}
