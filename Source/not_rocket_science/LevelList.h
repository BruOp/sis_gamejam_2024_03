// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelList.generated.h"

/**
 * 
 */
UCLASS()
class NOT_ROCKET_SCIENCE_API ULevelList : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UWorld>> LevelList;
};
