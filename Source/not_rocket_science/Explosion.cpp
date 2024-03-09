// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion.h"

AExplosion::AExplosion()
{
	PrimaryActorTick.bCanEverTick = true;
	ExplosionMesh = CreateDefaultSubobject<UStaticMeshComponent>("ExplosionMesh");
	RootComponent = ExplosionMesh; 
}

void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	CurrentScale = StartScale;

	ExplosionMesh->SetRelativeScale3D(FVector::One() * CurrentScale);
}

void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentScale = CurrentScale + (EndScale - StartScale) * DeltaTime / ExpansionTime;
	
	ExplosionMesh->SetRelativeScale3D(FVector::One() * FMath::Min(CurrentScale, EndScale));

	if (CurrentScale >= EndScale)
	{
		Destroy();
	}
}

