// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePlayerHud.h"

#include "SinglePlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

void ASinglePlayerHud::OnWinScreenContinue()
{
    Cast<ASinglePlayerGameMode>(UGameplayStatics::GetGameMode(this))->LoadNextLevel();
}
