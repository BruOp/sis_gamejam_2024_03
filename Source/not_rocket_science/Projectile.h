// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GravitationalBody.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class NOT_ROCKET_SCIENCE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

	void UpdatePosition(float DeltaTime);
	
	void UpdateVelocity(float DeltaTime);
	
	UPROPERTY()
	TArray<TObjectPtr<AGravitationalBody>> GravitationalBodies;

	UPROPERTY(EditAnywhere)
	FVector Velocity;
public:	
	virtual void Tick(float DeltaTime) override;

};
