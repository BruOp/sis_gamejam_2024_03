// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class NOT_ROCKET_SCIENCE_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	ATarget();

protected:
	virtual void BeginPlay() override;
	
public:
	void Kill();

};
