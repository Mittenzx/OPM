// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIPlacementUtilities.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

EAIPatternType UOPM_AIPlacementUtilities::DetectPlacementPattern(const TArray<AActor*>& Actors)
{
	if (Actors.Num() < 3)
	{
		return EAIPatternType::Scattered;
	}

	// Check for linear pattern first
	if (DetectLinearPattern(Actors))
	{
		return EAIPatternType::Linear;
	}

	// Check for radial pattern
	if (DetectRadialPattern(Actors))
	{
		return EAIPatternType::Radial;
	}

	// Calculate clustering density
	float Density = CalculateClusteringDensity(Actors);
	if (Density > 0.7f)
	{
		return EAIPatternType::Clustered;
	}

	// Check for grid pattern by analyzing spacing variance
	float Variance = CalculateSpacingVariance(Actors);
	if (Variance < 0.2f)
	{
		return EAIPatternType::Grid;
	}

	// Check if placement looks organic
	if (Variance > 0.5f && Density < 0.5f)
	{
		return EAIPatternType::Organic;
	}

	return EAIPatternType::Scattered;
}

int32 UOPM_AIPlacementUtilities::GenerateSmartSuggestions(
	const TArray<AActor*>& ExistingActors,
	const FAIPlacementSettings& Settings,
	TArray<FTransform>& SuggestedTransforms)
{
	SuggestedTransforms.Empty();

	if (ExistingActors.Num() == 0)
	{
		return 0;
	}

	// Detect the pattern
	EAIPatternType Pattern = DetectPlacementPattern(ExistingActors);

	// Calculate average spacing
	TArray<FBox> ActorBounds;
	for (AActor* Actor : ExistingActors)
	{
		if (Actor)
		{
			ActorBounds.Add(Actor->GetComponentsBoundingBox(true));
		}
	}

	float OptimalSpacing = CalculateOptimalSpacing(ActorBounds, 0.5f);
	FVector Centroid = CalculateCentroid(ExistingActors);

	// Generate suggestions based on detected pattern
	int32 NumSuggestions = FMath::Min(Settings.MaxSuggestions, 10);
	
	for (int32 i = 0; i < NumSuggestions; ++i)
	{
		FVector SuggestedLocation = Centroid;
		
		switch (Pattern)
		{
			case EAIPatternType::Linear:
			{
				// Extend the line
				if (ExistingActors.Num() >= 2)
				{
					FVector Dir = (ExistingActors.Last()->GetActorLocation() - ExistingActors[0]->GetActorLocation()).GetSafeNormal();
					SuggestedLocation = ExistingActors.Last()->GetActorLocation() + Dir * OptimalSpacing * (i + 1);
				}
				break;
			}
			case EAIPatternType::Radial:
			{
				// Add points on the circle
				float Angle = (360.0f / NumSuggestions) * i;
				float Radius = (ExistingActors[0]->GetActorLocation() - Centroid).Size();
				SuggestedLocation = Centroid + FVector(
					FMath::Cos(FMath::DegreesToRadians(Angle)) * Radius,
					FMath::Sin(FMath::DegreesToRadians(Angle)) * Radius,
					0.0f
				);
				break;
			}
			case EAIPatternType::Grid:
			{
				// Extend the grid
				SuggestedLocation = Centroid + FVector(OptimalSpacing * i, 0, 0);
				break;
			}
			case EAIPatternType::Organic:
			case EAIPatternType::Scattered:
			default:
			{
				// Random placement near existing actors
				float RandomAngle = FMath::FRandRange(0.0f, 360.0f);
				float RandomRadius = FMath::FRandRange(OptimalSpacing, OptimalSpacing * 2.0f);
				SuggestedLocation = Centroid + FVector(
					FMath::Cos(FMath::DegreesToRadians(RandomAngle)) * RandomRadius,
					FMath::Sin(FMath::DegreesToRadians(RandomAngle)) * RandomRadius,
					0.0f
				);
				break;
			}
		}

		FTransform SuggestedTransform(FRotator::ZeroRotator, SuggestedLocation, FVector::OneVector);
		SuggestedTransforms.Add(SuggestedTransform);
	}

	return SuggestedTransforms.Num();
}

TArray<FTransform> UOPM_AIPlacementUtilities::OptimizeActorPlacement(
	const TArray<AActor*>& Actors,
	const FAIPlacementSettings& Settings)
{
	TArray<FTransform> OptimizedTransforms;

	if (Actors.Num() == 0)
	{
		return OptimizedTransforms;
	}

	// Get current transforms
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			OptimizedTransforms.Add(Actor->GetActorTransform());
		}
	}

	// Optimize based on goal
	switch (Settings.OptimizationGoal)
	{
		case EAIOptimizationGoal::Performance:
		{
			// Increase spacing to reduce overdraw and collision checks
			FVector Centroid = CalculateCentroid(Actors);
			for (int32 i = 0; i < OptimizedTransforms.Num(); ++i)
			{
				FVector Direction = (OptimizedTransforms[i].GetLocation() - Centroid).GetSafeNormal();
				float Distance = (OptimizedTransforms[i].GetLocation() - Centroid).Size();
				OptimizedTransforms[i].SetLocation(Centroid + Direction * Distance * 1.2f);
			}
			break;
		}
		case EAIOptimizationGoal::VisualQuality:
		{
			// Apply organic distribution
			ApplyOrganicJitter(OptimizedTransforms, 20.0f);
			break;
		}
		case EAIOptimizationGoal::Memory:
		{
			// Group similar positions to enable instancing
			// Keep transforms more uniform
			break;
		}
		case EAIOptimizationGoal::Balanced:
		default:
		{
			// Slight organic variation while maintaining structure
			ApplyOrganicJitter(OptimizedTransforms, 10.0f);
			break;
		}
	}

	return OptimizedTransforms;
}

float UOPM_AIPlacementUtilities::CalculateClusteringDensity(const TArray<AActor*>& Actors)
{
	if (Actors.Num() < 2)
	{
		return 0.0f;
	}

	FVector Centroid = CalculateCentroid(Actors);
	float TotalDistance = 0.0f;
	float MaxDistance = 0.0f;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			float Distance = FVector::Dist(Actor->GetActorLocation(), Centroid);
			TotalDistance += Distance;
			MaxDistance = FMath::Max(MaxDistance, Distance);
		}
	}

	if (MaxDistance < KINDA_SMALL_NUMBER)
	{
		return 1.0f;
	}

	float AverageDistance = TotalDistance / Actors.Num();
	return 1.0f - FMath::Clamp(AverageDistance / MaxDistance, 0.0f, 1.0f);
}

float UOPM_AIPlacementUtilities::CalculateOptimalSpacing(
	const TArray<FBox>& ActorBounds,
	float DesiredDensity)
{
	if (ActorBounds.Num() == 0)
	{
		return 100.0f;
	}

	// Calculate average size
	float TotalSize = 0.0f;
	for (const FBox& Bounds : ActorBounds)
	{
		TotalSize += Bounds.GetSize().Size();
	}

	float AverageSize = TotalSize / ActorBounds.Num();
	
	// Spacing is based on size and desired density
	// Higher density = smaller spacing multiplier
	float SpacingMultiplier = FMath::Lerp(3.0f, 1.2f, DesiredDensity);
	
	return AverageSize * SpacingMultiplier;
}

int32 UOPM_AIPlacementUtilities::DetectAndCorrectOverlaps(
	const TArray<AActor*>& Actors,
	TArray<FTransform>& CorrectedTransforms)
{
	CorrectedTransforms.Empty();
	int32 OverlapCount = 0;

	if (Actors.Num() == 0)
	{
		return 0;
	}

	// Get initial transforms
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			CorrectedTransforms.Add(Actor->GetActorTransform());
		}
	}

	// Check for overlaps and correct
	for (int32 i = 0; i < Actors.Num(); ++i)
	{
		if (!Actors[i])
		{
			continue;
		}

		FBox BoundsI = Actors[i]->GetComponentsBoundingBox(true);

		for (int32 j = i + 1; j < Actors.Num(); ++j)
		{
			if (!Actors[j])
			{
				continue;
			}

			FBox BoundsJ = Actors[j]->GetComponentsBoundingBox(true);

			if (BoundsI.Intersect(BoundsJ))
			{
				OverlapCount++;

				// Push apart
				FVector Direction = (CorrectedTransforms[j].GetLocation() - CorrectedTransforms[i].GetLocation()).GetSafeNormal();
				if (Direction.IsNearlyZero())
				{
					Direction = FVector(1, 0, 0);
				}

				float SeparationDistance = (BoundsI.GetSize() + BoundsJ.GetSize()).Size() * 0.6f;
				CorrectedTransforms[j].SetLocation(
					CorrectedTransforms[i].GetLocation() + Direction * SeparationDistance
				);
			}
		}
	}

	return OverlapCount;
}

TArray<FTransform> UOPM_AIPlacementUtilities::GenerateOrganicPattern(
	const FBox& BoundsBox,
	int32 Count,
	const FAIPlacementSettings& Settings)
{
	TArray<FTransform> Transforms;
	FRandomStream RandomStream;
	RandomStream.Initialize(FMath::Rand());

	// Use Poisson disk sampling for organic distribution
	TArray<FVector> Points;
	float MinDistance = BoundsBox.GetSize().Size() / FMath::Sqrt(Count) * 0.8f;

	for (int32 Attempt = 0; Attempt < Count * 10 && Points.Num() < Count; ++Attempt)
	{
		FVector NewPoint = BoundsBox.Min + FVector(
			RandomStream.FRandRange(0.0f, BoundsBox.GetSize().X),
			RandomStream.FRandRange(0.0f, BoundsBox.GetSize().Y),
			RandomStream.FRandRange(0.0f, BoundsBox.GetSize().Z)
		);

		bool bTooClose = false;
		for (const FVector& ExistingPoint : Points)
		{
			if (FVector::Dist(NewPoint, ExistingPoint) < MinDistance)
			{
				bTooClose = true;
				break;
			}
		}

		if (!bTooClose)
		{
			Points.Add(NewPoint);
			
			FRotator RandomRotation(
				RandomStream.FRandRange(-5.0f, 5.0f),
				RandomStream.FRandRange(0.0f, 360.0f),
				RandomStream.FRandRange(-5.0f, 5.0f)
			);
			
			Transforms.Add(FTransform(RandomRotation, NewPoint, FVector::OneVector));
		}
	}

	return Transforms;
}

TArray<float> UOPM_AIPlacementUtilities::SuggestLODSettings(
	const TArray<AActor*>& Actors,
	EAIOptimizationGoal OptimizationGoal)
{
	TArray<float> LODDistances;

	if (Actors.Num() == 0)
	{
		return LODDistances;
	}

	float Density = CalculateClusteringDensity(Actors);

	// Base LOD distance
	float BaseLODDistance = 1000.0f;

	// Adjust based on optimization goal and density
	switch (OptimizationGoal)
	{
		case EAIOptimizationGoal::Performance:
			BaseLODDistance *= 0.7f; // More aggressive LOD
			break;
		case EAIOptimizationGoal::VisualQuality:
			BaseLODDistance *= 1.5f; // Keep high detail longer
			break;
		case EAIOptimizationGoal::Memory:
			BaseLODDistance *= 0.8f;
			break;
		case EAIOptimizationGoal::Balanced:
		default:
			break;
	}

	// In dense areas, use more aggressive LOD
	float DensityMultiplier = FMath::Lerp(1.0f, 0.6f, Density);
	BaseLODDistance *= DensityMultiplier;

	for (int32 i = 0; i < Actors.Num(); ++i)
	{
		LODDistances.Add(BaseLODDistance);
	}

	return LODDistances;
}

float UOPM_AIPlacementUtilities::EvaluatePlacementQuality(const TArray<AActor*>& Actors)
{
	if (Actors.Num() < 2)
	{
		return 0.5f;
	}

	float QualityScore = 1.0f;

	// Check for overlaps (negative impact)
	TArray<FTransform> Dummy;
	int32 OverlapCount = DetectAndCorrectOverlaps(Actors, Dummy);
	float OverlapPenalty = FMath::Min(OverlapCount / float(Actors.Num()), 0.5f);
	QualityScore -= OverlapPenalty;

	// Check spacing variance (too much variance is bad)
	float Variance = CalculateSpacingVariance(Actors);
	if (Variance > 0.8f)
	{
		QualityScore -= 0.2f;
	}

	// Check clustering (extreme clustering or scattering is bad)
	float Density = CalculateClusteringDensity(Actors);
	if (Density < 0.2f || Density > 0.9f)
	{
		QualityScore -= 0.1f;
	}

	return FMath::Clamp(QualityScore, 0.0f, 1.0f);
}

TArray<FTransform> UOPM_AIPlacementUtilities::AutoBalanceDistribution(
	const TArray<AActor*>& Actors,
	const FBox& BoundsBox)
{
	TArray<FTransform> BalancedTransforms;

	if (Actors.Num() == 0)
	{
		return BalancedTransforms;
	}

	FVector Centroid = CalculateCentroid(Actors);
	FVector TargetCentroid = BoundsBox.GetCenter();

	// Calculate offset to center the distribution
	FVector Offset = TargetCentroid - Centroid;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FTransform Transform = Actor->GetActorTransform();
			
			// Apply centering offset
			FVector NewLocation = Transform.GetLocation() + Offset;
			
			// Clamp to bounds
			NewLocation.X = FMath::Clamp(NewLocation.X, BoundsBox.Min.X, BoundsBox.Max.X);
			NewLocation.Y = FMath::Clamp(NewLocation.Y, BoundsBox.Min.Y, BoundsBox.Max.Y);
			NewLocation.Z = FMath::Clamp(NewLocation.Z, BoundsBox.Min.Z, BoundsBox.Max.Z);
			
			Transform.SetLocation(NewLocation);
			BalancedTransforms.Add(Transform);
		}
	}

	return BalancedTransforms;
}

// Private helper methods

float UOPM_AIPlacementUtilities::CalculateSpacingVariance(const TArray<AActor*>& Actors)
{
	if (Actors.Num() < 2)
	{
		return 0.0f;
	}

	TArray<float> Distances;
	for (int32 i = 0; i < Actors.Num() - 1; ++i)
	{
		if (Actors[i] && Actors[i + 1])
		{
			Distances.Add(FVector::Dist(Actors[i]->GetActorLocation(), Actors[i + 1]->GetActorLocation()));
		}
	}

	if (Distances.Num() == 0)
	{
		return 0.0f;
	}

	// Calculate mean
	float Mean = 0.0f;
	for (float Distance : Distances)
	{
		Mean += Distance;
	}
	Mean /= Distances.Num();

	// Calculate variance
	float Variance = 0.0f;
	for (float Distance : Distances)
	{
		Variance += FMath::Square(Distance - Mean);
	}
	Variance /= Distances.Num();

	// Normalize by mean to get coefficient of variation
	return (Mean > KINDA_SMALL_NUMBER) ? (FMath::Sqrt(Variance) / Mean) : 0.0f;
}

bool UOPM_AIPlacementUtilities::DetectLinearPattern(const TArray<AActor*>& Actors, float Tolerance)
{
	if (Actors.Num() < 3)
	{
		return false;
	}

	// Get first and last points to define a line
	FVector Start = Actors[0]->GetActorLocation();
	FVector End = Actors.Last()->GetActorLocation();
	FVector LineDir = (End - Start).GetSafeNormal();

	// Check if all points are close to this line
	int32 OnLineCount = 0;
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Point = Actor->GetActorLocation();
			FVector ToPoint = Point - Start;
			float DistanceAlongLine = FVector::DotProduct(ToPoint, LineDir);
			FVector ClosestPointOnLine = Start + LineDir * DistanceAlongLine;
			float DistanceToLine = FVector::Dist(Point, ClosestPointOnLine);

			if (DistanceToLine <= Tolerance)
			{
				OnLineCount++;
			}
		}
	}

	return (OnLineCount >= Actors.Num() * 0.8f);
}

bool UOPM_AIPlacementUtilities::DetectRadialPattern(const TArray<AActor*>& Actors, float Tolerance)
{
	if (Actors.Num() < 4)
	{
		return false;
	}

	FVector Centroid = CalculateCentroid(Actors);

	// Calculate average radius
	float TotalRadius = 0.0f;
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			TotalRadius += FVector::Dist(Actor->GetActorLocation(), Centroid);
		}
	}
	float AverageRadius = TotalRadius / Actors.Num();

	// Check if all actors are at similar distance from centroid
	int32 OnCircleCount = 0;
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			float Radius = FVector::Dist(Actor->GetActorLocation(), Centroid);
			if (FMath::Abs(Radius - AverageRadius) <= Tolerance)
			{
				OnCircleCount++;
			}
		}
	}

	return (OnCircleCount >= Actors.Num() * 0.8f);
}

FVector UOPM_AIPlacementUtilities::CalculateCentroid(const TArray<AActor*>& Actors)
{
	FVector Centroid = FVector::ZeroVector;
	int32 ValidCount = 0;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			Centroid += Actor->GetActorLocation();
			ValidCount++;
		}
	}

	return (ValidCount > 0) ? (Centroid / ValidCount) : FVector::ZeroVector;
}

void UOPM_AIPlacementUtilities::ApplyOrganicJitter(TArray<FTransform>& Transforms, float JitterAmount)
{
	FRandomStream RandomStream;
	RandomStream.Initialize(FMath::Rand());

	for (FTransform& Transform : Transforms)
	{
		FVector Jitter(
			RandomStream.FRandRange(-JitterAmount, JitterAmount),
			RandomStream.FRandRange(-JitterAmount, JitterAmount),
			RandomStream.FRandRange(-JitterAmount * 0.5f, JitterAmount * 0.5f)
		);

		Transform.SetLocation(Transform.GetLocation() + Jitter);

		// Add slight rotation variation
		FRotator CurrentRotation = Transform.GetRotation().Rotator();
		CurrentRotation.Yaw += RandomStream.FRandRange(-5.0f, 5.0f);
		Transform.SetRotation(FQuat(CurrentRotation));
	}
}
