// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePlayerGameMode.h"

#include "SinglePlayerHud.h"
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

    AHUD* Hud =	UGameplayStatics::GetPlayerController(this,0)->GetHUD();
	ASinglePlayerHud* SinglePlayerHud = Cast<ASinglePlayerHud>(Hud);
	if (IsValid(SinglePlayerHud))
	{
		SinglePlayerHud->ShowWinScreen(0,0,0);
	}
}

void ASinglePlayerGameMode::LoadNextLevel()
{
	FString CurrentLevelName = GetWorld()->GetPathName();
	size_t CurrentLevelIndex = 999999;
	for (size_t i = 0; i < LevelList->LevelList.Num(); i++)
	{
		TSoftObjectPtr<UWorld> Level = LevelList->LevelList[i];
		FString LevelName = Level->GetPathName();
		if (LevelName == CurrentLevelName)
		{
			CurrentLevelIndex = i;
			break;
		}
	}
	
	if (CurrentLevelIndex + 1 >= LevelList->LevelList.Num())
	{
		return;
	}
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelList->LevelList[CurrentLevelIndex + 1]);
}


