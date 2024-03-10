// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "ZoomingOrthoCameraActor.generated.h"

/**
 * Camera that does not move, just zooms out to keep an actor in sight.
 */
UCLASS()
class NOT_ROCKET_SCIENCE_API AZoomingOrthoCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	AZoomingOrthoCameraActor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetTargetActor(AActor* TargetActor);

protected:
	virtual void BeginPlay() override;

	float CalculateRequiredWidth() const;

	UPROPERTY(Transient)
	float InitialWidth;
	
	UPROPERTY(Transient)
	AActor* TargetActor;

	UPROPERTY(EditAnywhere, Meta=(Category="Zooming Camera", ClampMin="0.0", ClampMax="1.0"))
	float MarginSize = 0.1f;

	UPROPERTY(EditAnywhere, Meta = (Category = "Zooming Camera", ClampMin = "0.0", ClampMax = "2000.0"))
	float ZoomInSpeed = 1000.0f;
};
