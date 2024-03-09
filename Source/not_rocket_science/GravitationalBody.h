// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GravitationalBody.generated.h"

UCLASS()
class NOT_ROCKET_SCIENCE_API AGravitationalBody : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGravitationalBody();

	UPROPERTY(EditAnywhere)
	float Mass;
};
