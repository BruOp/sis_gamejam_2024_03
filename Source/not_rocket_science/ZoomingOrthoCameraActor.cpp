// Fill out your copyright notice in the Description page of Project Settings.

#include "ZoomingOrthoCameraActor.h"
#include "Camera/CameraComponent.h"

AZoomingOrthoCameraActor::AZoomingOrthoCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	UCameraComponent* Camera = GetCameraComponent();
	if (IsValid(Camera))
	{
		Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
		Camera->OrthoWidth = 3000.0f;
	}
}

void AZoomingOrthoCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCameraComponent* Camera = GetCameraComponent();
	if (IsValid(Camera))
	{
		float NewWidth = CalculateRequiredWidth();

		if (NewWidth < Camera->OrthoWidth)
		{
			NewWidth = FMath::Max(NewWidth, Camera->OrthoWidth - (ZoomInSpeed * DeltaTime));
		}

		Camera->SetOrthoWidth(NewWidth);
	}
}
void AZoomingOrthoCameraActor::SetTargetActor(AActor* NewTarget)
{
	TargetActor = NewTarget;
}

void AZoomingOrthoCameraActor::BeginPlay()
{
	Super::BeginPlay();

	UCameraComponent* Camera = GetCameraComponent();
	if (IsValid(Camera))
	{
		InitialWidth = Camera->OrthoWidth;
	}
}

float AZoomingOrthoCameraActor::CalculateRequiredWidth() const
{
	const UCameraComponent* const Camera = GetCameraComponent();
	if (!IsValid(Camera) || !IsValid(TargetActor))
	{
		return InitialWidth;
	}

	const FVector MyLocation = GetActorLocation();
	const FVector TargetLocation = TargetActor->GetActorLocation();
	const FVector RelativeLocation = TargetLocation - MyLocation;
	
	const float MinWidthFromX = 2.0f * FMath::Abs(RelativeLocation.X);
	const float MinWidthFromY = 2.0f * FMath::Abs(RelativeLocation.Y) * Camera->AspectRatio;
	const float MinWidth = FMath::Max(MinWidthFromX, MinWidthFromY);
	const float MinWidthWithMargin = MinWidth * (1.0f + MarginSize);

	return FMath::Max(InitialWidth, MinWidthWithMargin);
}
