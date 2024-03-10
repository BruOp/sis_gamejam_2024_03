// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePlayerGameMode.h"

#include "Kismet/GameplayStatics.h"

ASinglePlayerGameMode::ASinglePlayerGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	bGameEnded = false;
}

void ASinglePlayerGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ASinglePlayerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bGameEnded)
	{
		return;
	}
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, ATarget::StaticClass(), Actors);

	if (Actors.IsEmpty())
	{
		Win();
	}
}

void ASinglePlayerGameMode::Win()
{
	bGameEnded = true;
	// Show win screen.
}


