// Copyright Epic Games, Inc. All Rights Reserved.

#include "LandscapeIntegrationUtilities.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Landscape.h"
#include "LandscapeComponent.h"
#include "LandscapeInfo.h"

TArray<AActor*> UOPM_LandscapeIntegrationUtilities::PlaceActorsOnLandscape(
	UClass* ActorClass,
	const TArray<FTransform>& Transforms,
	ALandscape* Landscape,
	const FLandscapePlacementSettings& Settings,
	UWorld* World)
{
	TArray<AActor*> SpawnedActors;

	if (!ActorClass || !World || !Landscape)
	{
		return SpawnedActors;
	}

	for (const FTransform& Transform : Transforms)
	{
		// Adjust transform to align with terrain
		FTransform AdjustedTransform = AlignToTerrain(Transform, Landscape, Settings);

		// Check if location is valid based on settings
		float Slope = CalculateSlopeAngle(Landscape, AdjustedTransform.GetLocation());
		float Height = AdjustedTransform.GetLocation().Z;

		if (MeetsSlopeRequirements(Slope, Settings) && MeetsHeightRequirements(Height, Settings))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AActor* SpawnedActor = World->SpawnActor<AActor>(
				ActorClass,
				AdjustedTransform.GetLocation(),
				AdjustedTransform.GetRotation().Rotator(),
				SpawnParams
			);

			if (SpawnedActor)
			{
				SpawnedActor->SetActorScale3D(AdjustedTransform.GetScale3D());
				SpawnedActors.Add(SpawnedActor);
			}
		}
	}

	return SpawnedActors;
}

bool UOPM_LandscapeIntegrationUtilities::SampleLandscapeHeight(
	ALandscape* Landscape,
	const FVector& Location,
	float& OutHeight)
{
	if (!Landscape)
	{
		return false;
	}

	ULandscapeInfo* LandscapeInfo = Landscape->GetLandscapeInfo();
	if (!LandscapeInfo)
	{
		return false;
	}

	// Query landscape height at location
	ALandscapeProxy* Proxy = LandscapeInfo->GetLandscapeProxy(Location, false);
	if (Proxy)
	{
		OutHeight = Proxy->GetHeightAtLocation(Location);
		return true;
	}

	return false;
}

bool UOPM_LandscapeIntegrationUtilities::SampleLandscapeNormal(
	ALandscape* Landscape,
	const FVector& Location,
	FVector& OutNormal)
{
	if (!Landscape)
	{
		return false;
	}

	// Sample nearby points to calculate normal
	float CenterHeight = 0.0f;
	float RightHeight = 0.0f;
	float ForwardHeight = 0.0f;
	
	const float SampleDistance = 10.0f;
	
	if (!SampleLandscapeHeight(Landscape, Location, CenterHeight))
	{
		return false;
	}

	SampleLandscapeHeight(Landscape, Location + FVector(SampleDistance, 0, 0), RightHeight);
	SampleLandscapeHeight(Landscape, Location + FVector(0, SampleDistance, 0), ForwardHeight);

	// Calculate normal from height differences
	FVector Right = FVector(SampleDistance, 0, RightHeight - CenterHeight);
	FVector Forward = FVector(0, SampleDistance, ForwardHeight - CenterHeight);
	
	OutNormal = FVector::CrossProduct(Forward, Right).GetSafeNormal();
	return true;
}

float UOPM_LandscapeIntegrationUtilities::CalculateSlopeAngle(
	ALandscape* Landscape,
	const FVector& Location)
{
	FVector Normal;
	if (SampleLandscapeNormal(Landscape, Location, Normal))
	{
		// Calculate angle between normal and up vector
		float DotProduct = FVector::DotProduct(Normal, FVector::UpVector);
		return FMath::RadiansToDegrees(FMath::Acos(DotProduct));
	}

	return 0.0f;
}

FTransform UOPM_LandscapeIntegrationUtilities::AlignToTerrain(
	const FTransform& Transform,
	ALandscape* Landscape,
	const FLandscapePlacementSettings& Settings)
{
	FTransform AdjustedTransform = Transform;

	if (!Landscape)
	{
		return AdjustedTransform;
	}

	FVector Location = Transform.GetLocation();

	// Sample landscape height
	float TerrainHeight = 0.0f;
	if (SampleLandscapeHeight(Landscape, Location, TerrainHeight))
	{
		Location.Z = TerrainHeight;
	}

	// Apply alignment based on settings
	FRotator Rotation = Transform.GetRotation().Rotator();

	switch (Settings.TerrainAlignment)
	{
		case ETerrainAlignment::AlignToNormal:
		{
			FVector Normal;
			if (SampleLandscapeNormal(Landscape, Location, Normal))
			{
				Rotation = Normal.Rotation();
				Rotation.Yaw = Transform.GetRotation().Rotator().Yaw; // Keep original yaw
			}
			break;
		}
		case ETerrainAlignment::AlignToSlope:
		{
			FVector Normal;
			if (SampleLandscapeNormal(Landscape, Location, Normal))
			{
				// Only align pitch and roll, keep yaw
				FVector Forward = Transform.GetRotation().GetForwardVector();
				Forward.Z = 0;
				Forward.Normalize();
				
				FVector Right = FVector::CrossProduct(Normal, Forward).GetSafeNormal();
				Forward = FVector::CrossProduct(Right, Normal).GetSafeNormal();
				
				Rotation = FRotationMatrix::MakeFromXZ(Forward, Normal).Rotator();
			}
			break;
		}
		case ETerrainAlignment::SnapToSurface:
		{
			// Just snap Z, keep original rotation
			break;
		}
		case ETerrainAlignment::None:
		default:
		{
			// Keep original transform but update height
			Location.Z = Transform.GetLocation().Z;
			break;
		}
	}

	AdjustedTransform.SetLocation(Location);
	AdjustedTransform.SetRotation(FQuat(Rotation));

	return AdjustedTransform;
}

TArray<FTransform> UOPM_LandscapeIntegrationUtilities::DistributeByBiome(
	const FBox& BoundsBox,
	int32 Count,
	EBiomeType BiomeType,
	ALandscape* Landscape)
{
	TArray<FTransform> Transforms;

	if (!Landscape || Count <= 0)
	{
		return Transforms;
	}

	float MinDistance, Clusteriness;
	GetBiomeParameters(BiomeType, MinDistance, Clusteriness);

	FRandomStream RandomStream;
	RandomStream.Initialize(FMath::Rand());

	// Generate points based on biome type
	TArray<FVector> Points;

	for (int32 Attempt = 0; Attempt < Count * 10 && Points.Num() < Count; ++Attempt)
	{
		FVector NewPoint = BoundsBox.Min + FVector(
			RandomStream.FRandRange(0.0f, BoundsBox.GetSize().X),
			RandomStream.FRandRange(0.0f, BoundsBox.GetSize().Y),
			0.0f
		);

		// Sample terrain height
		float Height = 0.0f;
		if (SampleLandscapeHeight(Landscape, NewPoint, Height))
		{
			NewPoint.Z = Height;

			// Apply biome-specific distribution logic
			bool bAccept = true;

			// Check minimum distance
			for (const FVector& ExistingPoint : Points)
			{
				if (FVector::Dist2D(NewPoint, ExistingPoint) < MinDistance)
				{
					bAccept = false;
					break;
				}
			}

			// Apply clustering based on biome
			if (bAccept && Clusteriness > 0.5f && Points.Num() > 0)
			{
				// For clustered biomes, prefer points near existing points
				float NearestDist = FLT_MAX;
				for (const FVector& ExistingPoint : Points)
				{
					float Dist = FVector::Dist2D(NewPoint, ExistingPoint);
					NearestDist = FMath::Min(NearestDist, Dist);
				}

				float ClusterRadius = BoundsBox.GetSize().Size2D() * 0.2f;
				if (NearestDist > ClusterRadius && RandomStream.FRand() > 0.3f)
				{
					bAccept = false;
				}
			}

			if (bAccept)
			{
				Points.Add(NewPoint);
			}
		}
	}

	// Convert points to transforms
	for (const FVector& Point : Points)
	{
		FRotator Rotation(0, RandomStream.FRandRange(0.0f, 360.0f), 0);
		Transforms.Add(FTransform(Rotation, Point, FVector::OneVector));
	}

	return Transforms;
}

TArray<FVector> UOPM_LandscapeIntegrationUtilities::FilterLocationsByTerrain(
	const TArray<FVector>& Locations,
	ALandscape* Landscape,
	const FLandscapePlacementSettings& Settings)
{
	TArray<FVector> FilteredLocations;

	if (!Landscape)
	{
		return FilteredLocations;
	}

	for (const FVector& Location : Locations)
	{
		float Height = 0.0f;
		if (SampleLandscapeHeight(Landscape, Location, Height))
		{
			float Slope = CalculateSlopeAngle(Landscape, Location);

			if (MeetsHeightRequirements(Height, Settings) && MeetsSlopeRequirements(Slope, Settings))
			{
				FVector AdjustedLocation = Location;
				AdjustedLocation.Z = Height;
				FilteredLocations.Add(AdjustedLocation);
			}
		}
	}

	return FilteredLocations;
}

TArray<FTransform> UOPM_LandscapeIntegrationUtilities::GenerateContourFollowingPattern(
	ALandscape* Landscape,
	const FVector& StartLocation,
	int32 Count,
	float Spacing,
	const FLandscapePlacementSettings& Settings)
{
	TArray<FTransform> Transforms;

	if (!Landscape || Count <= 0)
	{
		return Transforms;
	}

	FVector CurrentLocation = StartLocation;
	float CurrentHeight = 0.0f;
	
	if (!SampleLandscapeHeight(Landscape, CurrentLocation, CurrentHeight))
	{
		return Transforms;
	}

	// Add first point
	Transforms.Add(FTransform(FRotator::ZeroRotator, FVector(CurrentLocation.X, CurrentLocation.Y, CurrentHeight), FVector::OneVector));

	// Follow contour by finding points at similar height
	for (int32 i = 1; i < Count; ++i)
	{
		float BestScore = FLT_MAX;
		FVector BestLocation = CurrentLocation;

		// Sample points around current location
		const int32 NumSamples = 8;
		for (int32 j = 0; j < NumSamples; ++j)
		{
			float Angle = (360.0f / NumSamples) * j;
			FVector TestLocation = CurrentLocation + FVector(
				FMath::Cos(FMath::DegreesToRadians(Angle)) * Spacing,
				FMath::Sin(FMath::DegreesToRadians(Angle)) * Spacing,
				0.0f
			);

			float TestHeight = 0.0f;
			if (SampleLandscapeHeight(Landscape, TestLocation, TestHeight))
			{
				// Prefer points at similar height
				float HeightDiff = FMath::Abs(TestHeight - CurrentHeight);
				float Slope = CalculateSlopeAngle(Landscape, TestLocation);

				if (MeetsSlopeRequirements(Slope, Settings))
				{
					if (HeightDiff < BestScore)
					{
						BestScore = HeightDiff;
						BestLocation = FVector(TestLocation.X, TestLocation.Y, TestHeight);
					}
				}
			}
		}

		if (BestScore < FLT_MAX)
		{
			CurrentLocation = BestLocation;
			Transforms.Add(FTransform(FRotator::ZeroRotator, CurrentLocation, FVector::OneVector));
		}
		else
		{
			break; // Can't find valid next point
		}
	}

	return Transforms;
}

float UOPM_LandscapeIntegrationUtilities::GetFoliageDensityAtLocation(
	ALandscape* Landscape,
	const FVector& Location,
	float Radius)
{
	// Placeholder implementation
	// In a full implementation, this would query the foliage system
	// For now, return a simple value based on terrain complexity
	
	if (!Landscape)
	{
		return 0.0f;
	}

	float Complexity = CalculateTerrainComplexity(Landscape, Location, Radius);
	
	// Simple heuristic: more complex terrain tends to have more foliage
	return FMath::Clamp(Complexity * 0.7f, 0.0f, 1.0f);
}

TArray<FVector> UOPM_LandscapeIntegrationUtilities::FilterLocationsByFoliage(
	const TArray<FVector>& Locations,
	ALandscape* Landscape,
	float FoliageDensityThreshold)
{
	TArray<FVector> FilteredLocations;

	if (!Landscape)
	{
		return FilteredLocations;
	}

	for (const FVector& Location : Locations)
	{
		float Density = GetFoliageDensityAtLocation(Landscape, Location);
		
		if (Density <= FoliageDensityThreshold)
		{
			FilteredLocations.Add(Location);
		}
	}

	return FilteredLocations;
}

ALandscape* UOPM_LandscapeIntegrationUtilities::FindLandscapeInWorld(UWorld* World)
{
	if (!World)
	{
		return nullptr;
	}

	for (TActorIterator<ALandscape> It(World); It; ++It)
	{
		return *It;
	}

	return nullptr;
}

TArray<FVector> UOPM_LandscapeIntegrationUtilities::GetSuitablePlacementLocations(
	ALandscape* Landscape,
	const FBox& BoundsBox,
	const FLandscapePlacementSettings& Settings,
	int32 MaxLocations)
{
	TArray<FVector> SuitableLocations;

	if (!Landscape)
	{
		return SuitableLocations;
	}

	// Sample grid of points within bounds
	int32 GridSize = FMath::CeilToInt(FMath::Sqrt(MaxLocations * 2.0f));
	FVector BoundsSize = BoundsBox.GetSize();
	FVector StepSize = BoundsSize / GridSize;

	for (int32 x = 0; x < GridSize && SuitableLocations.Num() < MaxLocations; ++x)
	{
		for (int32 y = 0; y < GridSize && SuitableLocations.Num() < MaxLocations; ++y)
		{
			FVector TestLocation = BoundsBox.Min + FVector(
				x * StepSize.X + StepSize.X * 0.5f,
				y * StepSize.Y + StepSize.Y * 0.5f,
				0.0f
			);

			float Height = 0.0f;
			if (SampleLandscapeHeight(Landscape, TestLocation, Height))
			{
				float Slope = CalculateSlopeAngle(Landscape, TestLocation);

				if (MeetsHeightRequirements(Height, Settings) && MeetsSlopeRequirements(Slope, Settings))
				{
					TestLocation.Z = Height;

					// Check foliage if required
					if (Settings.bUseFoliageRules)
					{
						float FoliageDensity = GetFoliageDensityAtLocation(Landscape, TestLocation);
						if (FoliageDensity > 0.7f)
						{
							continue;
						}
					}

					SuitableLocations.Add(TestLocation);
				}
			}
		}
	}

	return SuitableLocations;
}

float UOPM_LandscapeIntegrationUtilities::CalculateTerrainComplexity(
	ALandscape* Landscape,
	const FVector& Location,
	float Radius)
{
	if (!Landscape)
	{
		return 0.0f;
	}

	// Sample heights in a grid around the location
	TArray<float> Heights;
	const int32 SampleCount = 5;
	float SampleSpacing = Radius / SampleCount;

	for (int32 x = -SampleCount / 2; x <= SampleCount / 2; ++x)
	{
		for (int32 y = -SampleCount / 2; y <= SampleCount / 2; ++y)
		{
			FVector SampleLocation = Location + FVector(x * SampleSpacing, y * SampleSpacing, 0);
			float Height = 0.0f;
			
			if (SampleLandscapeHeight(Landscape, SampleLocation, Height))
			{
				Heights.Add(Height);
			}
		}
	}

	if (Heights.Num() < 2)
	{
		return 0.0f;
	}

	// Calculate variance in heights
	float Mean = 0.0f;
	for (float Height : Heights)
	{
		Mean += Height;
	}
	Mean /= Heights.Num();

	float Variance = 0.0f;
	for (float Height : Heights)
	{
		Variance += FMath::Square(Height - Mean);
	}
	Variance /= Heights.Num();

	// Normalize to 0-1 range (assuming typical height variance is 0-10000)
	float Complexity = FMath::Clamp(FMath::Sqrt(Variance) / 100.0f, 0.0f, 1.0f);

	return Complexity;
}

// Private helper methods

FVector2D UOPM_LandscapeIntegrationUtilities::WorldToLandscapeCoords(
	ALandscape* Landscape,
	const FVector& WorldLocation)
{
	if (!Landscape)
	{
		return FVector2D::ZeroVector;
	}

	FVector LocalLocation = Landscape->GetTransform().InverseTransformPosition(WorldLocation);
	return FVector2D(LocalLocation.X, LocalLocation.Y);
}

FVector UOPM_LandscapeIntegrationUtilities::LandscapeToWorldCoords(
	ALandscape* Landscape,
	const FVector2D& LandscapeCoords,
	float Height)
{
	if (!Landscape)
	{
		return FVector::ZeroVector;
	}

	FVector LocalLocation(LandscapeCoords.X, LandscapeCoords.Y, Height);
	return Landscape->GetTransform().TransformPosition(LocalLocation);
}

bool UOPM_LandscapeIntegrationUtilities::MeetsHeightRequirements(
	float Height,
	const FLandscapePlacementSettings& Settings)
{
	return Height >= Settings.MinHeight && Height <= Settings.MaxHeight;
}

bool UOPM_LandscapeIntegrationUtilities::MeetsSlopeRequirements(
	float Slope,
	const FLandscapePlacementSettings& Settings)
{
	return Slope <= Settings.MaxSlope;
}

void UOPM_LandscapeIntegrationUtilities::GetBiomeParameters(
	EBiomeType BiomeType,
	float& OutMinDistance,
	float& OutClusteriness)
{
	switch (BiomeType)
	{
		case EBiomeType::Forest:
			OutMinDistance = 150.0f;
			OutClusteriness = 0.7f; // Moderate clustering
			break;
		case EBiomeType::Desert:
			OutMinDistance = 300.0f;
			OutClusteriness = 0.3f; // Sparse, scattered
			break;
		case EBiomeType::Mountain:
			OutMinDistance = 400.0f;
			OutClusteriness = 0.2f; // Very sparse
			break;
		case EBiomeType::Plains:
			OutMinDistance = 200.0f;
			OutClusteriness = 0.4f; // Even distribution
			break;
		case EBiomeType::Water:
			OutMinDistance = 250.0f;
			OutClusteriness = 0.5f; // Moderate
			break;
		case EBiomeType::Urban:
			OutMinDistance = 100.0f;
			OutClusteriness = 0.8f; // High clustering
			break;
		case EBiomeType::Custom:
		default:
			OutMinDistance = 200.0f;
			OutClusteriness = 0.5f; // Balanced
			break;
	}
}
