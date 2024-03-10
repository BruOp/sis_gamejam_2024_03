// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

UCLASS()
class NOT_ROCKET_SCIENCE_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	AExplosion();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> ExplosionMesh;

	UPROPERTY(EditAnywhere)
	float StartScale;
	
	UPROPERTY(EditAnywhere)
	float EndScale;

	// Once scale exceeds this parameter, the explosion no longer causes damage.
	UPROPERTY(EditAnywhere)
	float DamageMaxScale;

	UPROPERTY(EditAnywhere)
	float ExpansionTime;

	float CurrentScale;

	UPROPERTY(BlueprintReadOnly)
	float NormalizedTimer;
public:	
	virtual void Tick(float DeltaTime) override;

private:
	void DealDamage();

	UPROPERTY(Transient)
	bool bDamaging = true;
};
