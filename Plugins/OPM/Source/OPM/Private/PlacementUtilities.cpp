// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlacementUtilities.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

TArray<FTransform> UOPM_PlacementUtilities::GenerateGridPattern(
	int32 Rows,
	int32 Columns,
	FVector Spacing,
	const FTransform& Origin)
{
	TArray<FTransform> Transforms;
	Transforms.Reserve(Rows * Columns);

	// Calculate offset to center the grid around the origin
	FVector Offset = FVector(
		-(Columns - 1) * Spacing.X * 0.5f,
		-(Rows - 1) * Spacing.Y * 0.5f,
		0.0f
	);

	for (int32 Row = 0; Row < Rows; ++Row)
	{
		for (int32 Col = 0; Col < Columns; ++Col)
		{
			FVector LocalPosition = FVector(
				Col * Spacing.X,
				Row * Spacing.Y,
				0.0f
			) + Offset;

			// Transform local position by origin
			FVector WorldPosition = Origin.TransformPosition(LocalPosition);
			
			FTransform Transform = Origin;
			Transform.SetLocation(WorldPosition);
			Transforms.Add(Transform);
		}
	}

	return Transforms;
}

TArray<FTransform> UOPM_PlacementUtilities::GenerateGridPattern(
	const FGridPatternSettings& Settings,
	const FTransform& Origin)
{
	return GenerateGridPattern(Settings.Rows, Settings.Columns, Settings.Spacing, Origin);
}

TArray<FTransform> UOPM_PlacementUtilities::GenerateCircularPattern(
	float Radius,
	int32 Count,
	float StartAngle,
	const FTransform& Center)
{
	TArray<FTransform> Transforms;
	Transforms.Reserve(Count);

	if (Count <= 0 || Radius < 0.0f)
	{
		return Transforms;
	}

	const float AngleStep = 360.0f / Count;
	const float StartAngleRad = FMath::DegreesToRadians(StartAngle);

	for (int32 i = 0; i < Count; ++i)
	{
		const float Angle = FMath::DegreesToRadians(StartAngle + i * AngleStep);
		
		// Calculate position on circle
		FVector LocalPosition = FVector(
			FMath::Cos(Angle) * Radius,
			FMath::Sin(Angle) * Radius,
			0.0f
		);

		// Transform by center
		FVector WorldPosition = Center.TransformPosition(LocalPosition);
		
		// Calculate rotation to face outward from center
		FRotator Rotation = Center.Rotator();
		Rotation.Yaw += StartAngle + i * AngleStep;
		
		FTransform Transform(Rotation, WorldPosition, Center.GetScale3D());
		Transforms.Add(Transform);
	}

	return Transforms;
}

TArray<FTransform> UOPM_PlacementUtilities::GenerateCircularPattern(
	const FCircularPatternSettings& Settings,
	const FTransform& Center)
{
	TArray<FTransform> Transforms = GenerateCircularPattern(
		Settings.Radius,
		Settings.Count,
		Settings.StartAngle,
		Center
	);

	// Apply height offset
	if (!FMath::IsNearlyZero(Settings.Height))
	{
		for (FTransform& Transform : Transforms)
		{
			FVector Location = Transform.GetLocation();
			Location.Z += Settings.Height;
			Transform.SetLocation(Location);
		}
	}

	return Transforms;
}

TArray<FTransform> UOPM_PlacementUtilities::GenerateLinePattern(
	const FVector& StartPoint,
	const FVector& EndPoint,
	int32 Count,
	const FTransform& BaseTransform)
{
	TArray<FTransform> Transforms;
	
	if (Count < 2)
	{
		return Transforms;
	}

	Transforms.Reserve(Count);

	// Calculate step vector
	const FVector Direction = EndPoint - StartPoint;
	const float TotalDistance = Direction.Size();
	const FVector Step = Direction / (Count - 1);

	// Calculate rotation to face along the line
	FRotator LineRotation = Direction.Rotation();

	for (int32 i = 0; i < Count; ++i)
	{
		FVector Position = StartPoint + Step * i;
		
		FTransform Transform(
			LineRotation,
			Position,
			BaseTransform.GetScale3D()
		);
		
		Transforms.Add(Transform);
	}

	return Transforms;
}

TArray<FTransform> UOPM_PlacementUtilities::GenerateLinePattern(
	const FLinePatternSettings& Settings,
	const FTransform& BaseTransform)
{
	return GenerateLinePattern(
		Settings.StartPoint,
		Settings.EndPoint,
		Settings.Count,
		BaseTransform
	);
}

TArray<FTransform> UOPM_PlacementUtilities::GenerateRandomPattern(
	const FBox& BoundsBox,
	int32 Count,
	int32 Seed,
	const FTransform& BaseTransform)
{
	TArray<FTransform> Transforms;
	Transforms.Reserve(Count);

	// Initialize random stream
	FRandomStream RandomStream;
	if (Seed == 0)
	{
		RandomStream.Initialize(FPlatformTime::Cycles());
	}
	else
	{
		RandomStream.Initialize(Seed);
	}

	for (int32 i = 0; i < Count; ++i)
	{
		// Generate random position within bounds
		FVector Position = FVector(
			RandomStream.FRandRange(BoundsBox.Min.X, BoundsBox.Max.X),
			RandomStream.FRandRange(BoundsBox.Min.Y, BoundsBox.Max.Y),
			RandomStream.FRandRange(BoundsBox.Min.Z, BoundsBox.Max.Z)
		);

		// Optional random rotation
		FRotator Rotation = BaseTransform.Rotator();
		Rotation.Yaw += RandomStream.FRandRange(0.0f, 360.0f);

		FTransform Transform(
			Rotation,
			Position,
			BaseTransform.GetScale3D()
		);

		Transforms.Add(Transform);
	}

	return Transforms;
}

TArray<FTransform> UOPM_PlacementUtilities::GenerateRandomPattern(
	const FRandomPatternSettings& Settings,
	const FTransform& BaseTransform)
{
	return GenerateRandomPattern(
		Settings.BoundsBox,
		Settings.Count,
		Settings.Seed,
		BaseTransform
	);
}

TArray<AActor*> UOPM_PlacementUtilities::PlaceActorsInPattern(
	UClass* ActorClass,
	const TArray<FTransform>& Transforms,
	UWorld* World)
{
	TArray<AActor*> SpawnedActors;

	if (!World || !ActorClass)
	{
		return SpawnedActors;
	}

	SpawnedActors.Reserve(Transforms.Num());

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (const FTransform& Transform : Transforms)
	{
		AActor* NewActor = World->SpawnActor<AActor>(
			ActorClass,
			Transform.GetLocation(),
			Transform.Rotator(),
			SpawnParams
		);

		if (NewActor)
		{
			NewActor->SetActorScale3D(Transform.GetScale3D());
			SpawnedActors.Add(NewActor);
		}
	}

	return SpawnedActors;
}
