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
}

void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NormalizedTimer += DeltaTime / ExpansionTime;
	
	CurrentScale = FMath::Lerp(StartScale, EndScale, FMath::Min(NormalizedTimer, 1.0f));
	
	ExplosionMesh->SetRelativeScale3D(FVector::One() * CurrentScale);

	TArray<AActor*> OverlappingActors;
	ExplosionMesh->GetOverlappingActors(OverlappingActors, ATarget::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		Cast<ATarget>(Actor)->Kill();
	}
	
	if (NormalizedTimer >= 1.0)
	{
		Destroy();
	}
}

