// Copyright Epic Games, Inc. All Rights Reserved.

#include "SplineUtilities.h"
#include "Engine/World.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

TArray<AActor*> UOPM_SplineUtilities::PlaceActorsAlongSpline(
	UClass* ActorClass,
	USplineComponent* SplineComponent,
	const FSplinePlacementSettings& Settings,
	UWorld* World)
{
	TArray<AActor*> SpawnedActors;

	if (!ActorClass || !SplineComponent || !World)
	{
		return SpawnedActors;
	}

	// Generate transforms along spline
	TArray<FTransform> Transforms = GenerateTransformsAlongSpline(SplineComponent, Settings);

	// Spawn actors at each transform
	for (const FTransform& Transform : Transforms)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* SpawnedActor = World->SpawnActor<AActor>(
			ActorClass,
			Transform.GetLocation(),
			Transform.GetRotation().Rotator(),
			SpawnParams
		);

		if (SpawnedActor)
		{
			SpawnedActor->SetActorScale3D(Transform.GetScale3D());
			SpawnedActors.Add(SpawnedActor);
		}
	}

	return SpawnedActors;
}

TArray<FTransform> UOPM_SplineUtilities::GenerateTransformsAlongSpline(
	USplineComponent* SplineComponent,
	const FSplinePlacementSettings& Settings)
{
	TArray<FTransform> Transforms;

	if (!SplineComponent)
	{
		return Transforms;
	}

	float SplineLength = GetSplineLength(SplineComponent);
	TArray<float> Distances;

	// Get distances based on placement mode
	switch (Settings.PlacementMode)
	{
		case ESplinePlacementMode::Uniform:
			Distances = GetUniformDistances(SplineLength, Settings.Spacing, Settings.StartOffset, Settings.EndOffset);
			break;
		case ESplinePlacementMode::ByDistance:
			Distances = GetUniformDistances(SplineLength, Settings.Spacing, Settings.StartOffset, Settings.EndOffset);
			break;
		case ESplinePlacementMode::BySplinePoints:
			Distances = GetSplinePointDistances(SplineComponent);
			break;
		case ESplinePlacementMode::Adaptive:
			Distances = GetAdaptiveDistances(SplineComponent, Settings.Spacing * 0.5f, Settings.Spacing * 2.0f);
			break;
		default:
			Distances = GetUniformDistances(SplineLength, Settings.Spacing, Settings.StartOffset, Settings.EndOffset);
			break;
	}

	// Generate transforms at each distance
	for (float Distance : Distances)
	{
		FTransform Transform = GetTransformAtDistance(SplineComponent, Distance, Settings.Alignment);
		
		// Apply offset
		Transform = ApplyOffsetToTransform(Transform, Settings.Offset);

		// Apply scale
		if (Settings.bScaleBySpline)
		{
			float Alpha = Distance / FMath::Max(SplineLength, 1.0f);
			FVector Scale = SplineComponent->GetScaleAtDistanceAlongSpline(Distance);
			Transform.SetScale3D(Scale);
		}

		Transforms.Add(Transform);
	}

	return Transforms;
}

TArray<AActor*> UOPM_SplineUtilities::GenerateRoadAlongSpline(
	USplineComponent* SplineComponent,
	UClass* RoadActorClass,
	const TArray<UClass*>& PropActorClasses,
	float PropSpacing,
	UWorld* World)
{
	TArray<AActor*> AllActors;

	if (!SplineComponent || !RoadActorClass || !World)
	{
		return AllActors;
	}

	// Place road segments
	FSplinePlacementSettings RoadSettings;
	RoadSettings.PlacementMode = ESplinePlacementMode::Uniform;
	RoadSettings.Spacing = 200.0f; // Standard road segment length
	RoadSettings.Alignment = ESplineAlignment::Tangent;

	TArray<AActor*> RoadActors = PlaceActorsAlongSpline(RoadActorClass, SplineComponent, RoadSettings, World);
	AllActors.Append(RoadActors);

	// Place props along both sides if provided
	if (PropActorClasses.Num() > 0)
	{
		FSplinePlacementSettings PropSettings;
		PropSettings.PlacementMode = ESplinePlacementMode::Uniform;
		PropSettings.Spacing = PropSpacing;
		PropSettings.Alignment = ESplineAlignment::Tangent;

		// Right side props
		PropSettings.Offset = FVector(0, 300.0f, 0); // Offset to the right
		for (UClass* PropClass : PropActorClasses)
		{
			if (PropClass)
			{
				TArray<AActor*> Props = PlaceActorsAlongSpline(PropClass, SplineComponent, PropSettings, World);
				AllActors.Append(Props);
			}
		}

		// Left side props
		PropSettings.Offset = FVector(0, -300.0f, 0); // Offset to the left
		for (UClass* PropClass : PropActorClasses)
		{
			if (PropClass)
			{
				TArray<AActor*> Props = PlaceActorsAlongSpline(PropClass, SplineComponent, PropSettings, World);
				AllActors.Append(Props);
			}
		}
	}

	return AllActors;
}

TArray<AActor*> UOPM_SplineUtilities::GenerateFenceAlongSpline(
	USplineComponent* SplineComponent,
	UClass* PostActorClass,
	UClass* PanelActorClass,
	float PostSpacing,
	UWorld* World)
{
	TArray<AActor*> FenceActors;

	if (!SplineComponent || !PostActorClass || !World)
	{
		return FenceActors;
	}

	// Place fence posts
	FSplinePlacementSettings PostSettings;
	PostSettings.PlacementMode = ESplinePlacementMode::Uniform;
	PostSettings.Spacing = PostSpacing;
	PostSettings.Alignment = ESplineAlignment::Tangent;

	TArray<AActor*> Posts = PlaceActorsAlongSpline(PostActorClass, SplineComponent, PostSettings, World);
	FenceActors.Append(Posts);

	// Place fence panels between posts if provided
	if (PanelActorClass && Posts.Num() > 1)
	{
		for (int32 i = 0; i < Posts.Num() - 1; ++i)
		{
			FVector Start = Posts[i]->GetActorLocation();
			FVector End = Posts[i + 1]->GetActorLocation();
			FVector MidPoint = (Start + End) * 0.5f;
			FRotator Rotation = (End - Start).Rotation();

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AActor* Panel = World->SpawnActor<AActor>(PanelActorClass, MidPoint, Rotation, SpawnParams);
			if (Panel)
			{
				// Scale panel to fit between posts
				float Distance = FVector::Dist(Start, End);
				FVector Scale = Panel->GetActorScale3D();
				Scale.X = Distance / 100.0f; // Assume default panel is 100 units
				Panel->SetActorScale3D(Scale);

				FenceActors.Add(Panel);
			}
		}
	}

	return FenceActors;
}

TArray<AActor*> UOPM_SplineUtilities::GenerateCableRoutingAlongSpline(
	USplineComponent* SplineComponent,
	UClass* CableActorClass,
	UClass* SupportsActorClass,
	float SupportSpacing,
	float SagAmount,
	UWorld* World)
{
	TArray<AActor*> CableActors;

	if (!SplineComponent || !World)
	{
		return CableActors;
	}

	// Place support structures
	if (SupportsActorClass)
	{
		FSplinePlacementSettings SupportSettings;
		SupportSettings.PlacementMode = ESplinePlacementMode::Uniform;
		SupportSettings.Spacing = SupportSpacing;
		SupportSettings.Alignment = ESplineAlignment::Up;

		TArray<AActor*> Supports = PlaceActorsAlongSpline(SupportsActorClass, SplineComponent, SupportSettings, World);
		CableActors.Append(Supports);
	}

	// Place cable segments with sag
	if (CableActorClass)
	{
		float SplineLength = GetSplineLength(SplineComponent);
		int32 NumSegments = FMath::CeilToInt(SplineLength / SupportSpacing);
		
		for (int32 i = 0; i < NumSegments; ++i)
		{
			float StartDist = i * SupportSpacing;
			float EndDist = FMath::Min((i + 1) * SupportSpacing, SplineLength);
			
			FTransform StartTransform = GetTransformAtDistance(SplineComponent, StartDist, ESplineAlignment::None);
			FTransform EndTransform = GetTransformAtDistance(SplineComponent, EndDist, ESplineAlignment::None);

			// Create cable segment at midpoint with sag
			FVector MidPoint = CalculateCableSag(
				StartTransform.GetLocation(),
				EndTransform.GetLocation(),
				0.5f,
				SagAmount
			);

			FRotator Rotation = (EndTransform.GetLocation() - StartTransform.GetLocation()).Rotation();

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AActor* Cable = World->SpawnActor<AActor>(CableActorClass, MidPoint, Rotation, SpawnParams);
			if (Cable)
			{
				CableActors.Add(Cable);
			}
		}
	}

	return CableActors;
}

float UOPM_SplineUtilities::GetSplineLength(USplineComponent* SplineComponent)
{
	if (!SplineComponent)
	{
		return 0.0f;
	}

	return SplineComponent->GetSplineLength();
}

FTransform UOPM_SplineUtilities::GetTransformAtDistance(
	USplineComponent* SplineComponent,
	float Distance,
	ESplineAlignment Alignment)
{
	if (!SplineComponent)
	{
		return FTransform::Identity;
	}

	FVector Location = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FRotator Rotation;

	switch (Alignment)
	{
		case ESplineAlignment::Tangent:
			Rotation = GetTangentRotation(SplineComponent, Distance);
			break;
		case ESplineAlignment::Normal:
			Rotation = GetNormalRotation(SplineComponent, Distance);
			break;
		case ESplineAlignment::Up:
			Rotation = FRotator(0, SplineComponent->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World).Yaw, 0);
			break;
		case ESplineAlignment::None:
		default:
			Rotation = FRotator::ZeroRotator;
			break;
	}

	return FTransform(Rotation, Location, FVector::OneVector);
}

TArray<float> UOPM_SplineUtilities::GetUniformDistances(
	float SplineLength,
	float Spacing,
	float StartOffset,
	float EndOffset)
{
	TArray<float> Distances;

	if (SplineLength <= 0.0f || Spacing <= 0.0f)
	{
		return Distances;
	}

	float AvailableLength = SplineLength - StartOffset - EndOffset;
	if (AvailableLength <= 0.0f)
	{
		return Distances;
	}

	int32 NumPoints = FMath::FloorToInt(AvailableLength / Spacing) + 1;
	
	for (int32 i = 0; i < NumPoints; ++i)
	{
		float Distance = StartOffset + (i * Spacing);
		if (Distance <= SplineLength - EndOffset)
		{
			Distances.Add(Distance);
		}
	}

	return Distances;
}

TArray<float> UOPM_SplineUtilities::GetSplinePointDistances(USplineComponent* SplineComponent)
{
	TArray<float> Distances;

	if (!SplineComponent)
	{
		return Distances;
	}

	int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
	for (int32 i = 0; i < NumPoints; ++i)
	{
		float Distance = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i);
		Distances.Add(Distance);
	}

	return Distances;
}

TArray<float> UOPM_SplineUtilities::GetAdaptiveDistances(
	USplineComponent* SplineComponent,
	float MinSpacing,
	float MaxSpacing)
{
	TArray<float> Distances;

	if (!SplineComponent)
	{
		return Distances;
	}

	float SplineLength = GetSplineLength(SplineComponent);
	float CurrentDistance = 0.0f;

	while (CurrentDistance < SplineLength)
	{
		Distances.Add(CurrentDistance);

		// Calculate curvature at current point
		float Curvature = GetCurvatureAtDistance(SplineComponent, CurrentDistance);
		
		// More curvature = smaller spacing
		// Curvature typically ranges from 0 (straight) to 1+ (curved)
		float NormalizedCurvature = FMath::Clamp(Curvature, 0.0f, 1.0f);
		float Spacing = FMath::Lerp(MaxSpacing, MinSpacing, NormalizedCurvature);

		CurrentDistance += Spacing;
	}

	return Distances;
}

float UOPM_SplineUtilities::GetCurvatureAtDistance(
	USplineComponent* SplineComponent,
	float Distance)
{
	if (!SplineComponent)
	{
		return 0.0f;
	}

	// Sample tangents at nearby points to estimate curvature
	const float SampleDistance = 10.0f;
	
	FVector Tangent1 = SplineComponent->GetTangentAtDistanceAlongSpline(
		FMath::Max(0.0f, Distance - SampleDistance),
		ESplineCoordinateSpace::World
	).GetSafeNormal();

	FVector Tangent2 = SplineComponent->GetTangentAtDistanceAlongSpline(
		FMath::Min(GetSplineLength(SplineComponent), Distance + SampleDistance),
		ESplineCoordinateSpace::World
	).GetSafeNormal();

	// Curvature is related to how much the tangent changes
	float AngleChange = FMath::Acos(FVector::DotProduct(Tangent1, Tangent2));
	
	// Normalize to a reasonable range
	return FMath::RadiansToDegrees(AngleChange) / 180.0f;
}

void UOPM_SplineUtilities::SmoothSpline(
	USplineComponent* SplineComponent,
	float SmoothingFactor)
{
	if (!SplineComponent || SmoothingFactor <= 0.0f)
	{
		return;
	}

	int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
	
	if (NumPoints < 3)
	{
		return;
	}

	// Smooth interior points
	for (int32 i = 1; i < NumPoints - 1; ++i)
	{
		FVector PrevLoc = SplineComponent->GetLocationAtSplinePoint(i - 1, ESplineCoordinateSpace::World);
		FVector CurrentLoc = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		FVector NextLoc = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

		// Calculate smoothed position
		FVector SmoothedLoc = (PrevLoc + CurrentLoc + NextLoc) / 3.0f;
		FVector NewLoc = FMath::Lerp(CurrentLoc, SmoothedLoc, SmoothingFactor);

		SplineComponent->SetLocationAtSplinePoint(i, NewLoc, ESplineCoordinateSpace::World, false);
	}

	SplineComponent->UpdateSpline();
}

TArray<AActor*> UOPM_SplineUtilities::PlaceActorsWithVariableDensity(
	UClass* ActorClass,
	USplineComponent* SplineComponent,
	float BaseDensity,
	float CurvatureFactor,
	UWorld* World)
{
	TArray<AActor*> SpawnedActors;

	if (!ActorClass || !SplineComponent || !World)
	{
		return SpawnedActors;
	}

	float SplineLength = GetSplineLength(SplineComponent);
	float CurrentDistance = 0.0f;

	while (CurrentDistance < SplineLength)
	{
		FTransform Transform = GetTransformAtDistance(SplineComponent, CurrentDistance, ESplineAlignment::Tangent);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* SpawnedActor = World->SpawnActor<AActor>(
			ActorClass,
			Transform.GetLocation(),
			Transform.GetRotation().Rotator(),
			SpawnParams
		);

		if (SpawnedActor)
		{
			SpawnedActors.Add(SpawnedActor);
		}

		// Calculate next distance based on curvature
		float Curvature = GetCurvatureAtDistance(SplineComponent, CurrentDistance);
		float DensityMultiplier = 1.0f + (Curvature * CurvatureFactor);
		float Spacing = (1.0f / BaseDensity) / DensityMultiplier;

		CurrentDistance += FMath::Max(Spacing, 10.0f); // Minimum 10 units
	}

	return SpawnedActors;
}

void UOPM_SplineUtilities::CreateParallelSpline(
	USplineComponent* SourceSpline,
	float Offset,
	USplineComponent* TargetSpline)
{
	if (!SourceSpline || !TargetSpline)
	{
		return;
	}

	TargetSpline->ClearSplinePoints();

	int32 NumPoints = SourceSpline->GetNumberOfSplinePoints();
	
	for (int32 i = 0; i < NumPoints; ++i)
	{
		FVector Location = SourceSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		FVector Right = SourceSpline->GetRightVectorAtSplinePoint(i, ESplineCoordinateSpace::World);
		
		FVector OffsetLocation = Location + (Right * Offset);
		
		TargetSpline->AddSplinePoint(OffsetLocation, ESplineCoordinateSpace::World, false);
	}

	TargetSpline->UpdateSpline();
}

void UOPM_SplineUtilities::SnapSplineToTerrain(
	USplineComponent* SplineComponent,
	UWorld* World,
	float HeightOffset)
{
	if (!SplineComponent || !World)
	{
		return;
	}

	int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();

	for (int32 i = 0; i < NumPoints; ++i)
	{
		FVector Location = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		
		// Trace down to find terrain
		FVector Start = Location + FVector(0, 0, 10000.0f);
		FVector End = Location - FVector(0, 0, 10000.0f);

		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex = false;

		if (World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
		{
			FVector NewLocation = HitResult.Location;
			NewLocation.Z += HeightOffset;
			SplineComponent->SetLocationAtSplinePoint(i, NewLocation, ESplineCoordinateSpace::World, false);
		}
	}

	SplineComponent->UpdateSpline();
}

TArray<USplineComponent*> UOPM_SplineUtilities::CreateBranchingSplines(
	USplineComponent* MainSpline,
	const TArray<float>& BranchLocations,
	const TArray<float>& BranchAngles,
	const TArray<float>& BranchLengths)
{
	TArray<USplineComponent*> BranchSplines;

	if (!MainSpline || BranchLocations.Num() != BranchAngles.Num() || BranchLocations.Num() != BranchLengths.Num())
	{
		return BranchSplines;
	}

	for (int32 i = 0; i < BranchLocations.Num(); ++i)
	{
		FTransform BranchStart = GetTransformAtDistance(MainSpline, BranchLocations[i], ESplineAlignment::Tangent);
		
		// Create new spline component
		USplineComponent* BranchSpline = NewObject<USplineComponent>(MainSpline->GetOwner());
		if (BranchSpline)
		{
			BranchSpline->ClearSplinePoints();
			
			// Start point
			BranchSpline->AddSplinePoint(BranchStart.GetLocation(), ESplineCoordinateSpace::World, false);
			
			// Calculate branch direction
			FRotator BranchRotation = BranchStart.GetRotation().Rotator();
			BranchRotation.Yaw += BranchAngles[i];
			FVector BranchDirection = BranchRotation.Vector();
			
			// End point
			FVector EndLocation = BranchStart.GetLocation() + (BranchDirection * BranchLengths[i]);
			BranchSpline->AddSplinePoint(EndLocation, ESplineCoordinateSpace::World, false);
			
			BranchSpline->UpdateSpline();
			BranchSplines.Add(BranchSpline);
		}
	}

	return BranchSplines;
}

// Private helper methods

FRotator UOPM_SplineUtilities::GetTangentRotation(
	USplineComponent* SplineComponent,
	float Distance)
{
	if (!SplineComponent)
	{
		return FRotator::ZeroRotator;
	}

	FVector Tangent = SplineComponent->GetTangentAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	return Tangent.Rotation();
}

FRotator UOPM_SplineUtilities::GetNormalRotation(
	USplineComponent* SplineComponent,
	float Distance)
{
	if (!SplineComponent)
	{
		return FRotator::ZeroRotator;
	}

	FVector Up = SplineComponent->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector Tangent = SplineComponent->GetTangentAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector Right = FVector::CrossProduct(Up, Tangent).GetSafeNormal();
	
	return FRotationMatrix::MakeFromXZ(Tangent, Up).Rotator();
}

FTransform UOPM_SplineUtilities::ApplyOffsetToTransform(
	const FTransform& BaseTransform,
	const FVector& Offset)
{
	FTransform Result = BaseTransform;
	
	if (!Offset.IsNearlyZero())
	{
		FVector OffsetWorld = BaseTransform.GetRotation().RotateVector(Offset);
		Result.SetLocation(BaseTransform.GetLocation() + OffsetWorld);
	}

	return Result;
}

FVector UOPM_SplineUtilities::CalculateCableSag(
	const FVector& Start,
	const FVector& End,
	float Alpha,
	float SagAmount)
{
	// Interpolate between start and end
	FVector LinearPoint = FMath::Lerp(Start, End, Alpha);
	
	// Apply catenary curve approximation (parabola)
	float SagFactor = 4.0f * Alpha * (1.0f - Alpha); // Parabola: max sag at center
	FVector SagOffset = FVector(0, 0, -SagAmount * SagFactor);
	
	return LinearPoint + SagOffset;
}
