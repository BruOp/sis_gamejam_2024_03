// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SinglePlayerHud.generated.h"

/**
 *
 */
UCLASS()
class NOT_ROCKET_SCIENCE_API ASinglePlayerHud : public AHUD
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent)
    void ShowWinScreen(int level, int targetsHit, int shotsTaken);

    UFUNCTION(BlueprintCallable)
    void OnWinScreenContinue();
};
