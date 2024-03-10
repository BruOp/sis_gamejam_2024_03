// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "GameFramework/GameModeBase.h"
#include "SinglePlayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NOT_ROCKET_SCIENCE_API ASinglePlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ASinglePlayerGameMode();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

protected:
	void Win();

	bool bGameEnded;
};
