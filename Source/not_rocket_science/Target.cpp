// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

ATarget::ATarget()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATarget::BeginPlay()
{
	Super::BeginPlay();
}

void ATarget::Kill()
{
	Destroy();
}
