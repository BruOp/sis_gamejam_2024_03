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

	UFUNCTION(BlueprintCallable, Meta=(Category="Projectile"))
	void SetVelocity(FVector NewVelocity);

protected:
	virtual void BeginPlay() override;

	void UpdatePosition(float DeltaTime);
	
	void UpdateVelocity(float DeltaTime);

	
	UPROPERTY()
	TArray<TObjectPtr<AGravitationalBody>> GravitationalBodies;

	UPROPERTY(EditAnywhere)
	FVector Velocity;

	UPROPERTY()
	bool bIsDestroyed;
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Meta=(Category="Projectile"))
	void Explode();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ExplosionActor;
};
