// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OPMTypes.h"
#include "GameFramework/Actor.h"
#include "Landscape.h"

/**
 * Utility class for landscape-aware placement operations
 * Provides terrain-aware placement, foliage integration, and biome-based distribution
 */
class OPM_API UOPM_LandscapeIntegrationUtilities
{
public:
	/**
	 * Place actors on landscape with terrain-aware positioning
	 * @param ActorClass Class of actor to spawn
	 * @param Transforms Initial transforms (will be adjusted to terrain)
	 * @param Landscape Landscape actor to place on
	 * @param Settings Landscape placement settings
	 * @param World World to spawn actors in
	 * @return Array of spawned actors
	 */
	static TArray<AActor*> PlaceActorsOnLandscape(
		UClass* ActorClass,
		const TArray<FTransform>& Transforms,
		ALandscape* Landscape,
		const FLandscapePlacementSettings& Settings,
		UWorld* World);

	/**
	 * Sample landscape height at a given location
	 * @param Landscape Landscape to sample
	 * @param Location Location to sample (X, Y will be used)
	 * @param OutHeight Output height value
	 * @return True if sampling was successful
	 */
	static bool SampleLandscapeHeight(
		ALandscape* Landscape,
		const FVector& Location,
		float& OutHeight);

	/**
	 * Sample landscape normal at a given location
	 * @param Landscape Landscape to sample
	 * @param Location Location to sample
	 * @param OutNormal Output normal vector
	 * @return True if sampling was successful
	 */
	static bool SampleLandscapeNormal(
		ALandscape* Landscape,
		const FVector& Location,
		FVector& OutNormal);

	/**
	 * Calculate slope angle at a landscape location
	 * @param Landscape Landscape to sample
	 * @param Location Location to calculate slope
	 * @return Slope angle in degrees
	 */
	static float CalculateSlopeAngle(
		ALandscape* Landscape,
		const FVector& Location);

	/**
	 * Adjust transform to align with terrain
	 * @param Transform Original transform
	 * @param Landscape Landscape to align to
	 * @param Settings Landscape placement settings
	 * @return Adjusted transform
	 */
	static FTransform AlignToTerrain(
		const FTransform& Transform,
		ALandscape* Landscape,
		const FLandscapePlacementSettings& Settings);

	/**
	 * Distribute actors based on biome type
	 * @param BoundsBox Area to distribute in
	 * @param Count Number of actors to place
	 * @param BiomeType Type of biome
	 * @param Landscape Landscape for reference
	 * @return Array of transforms for biome-appropriate distribution
	 */
	static TArray<FTransform> DistributeByBiome(
		const FBox& BoundsBox,
		int32 Count,
		EBiomeType BiomeType,
		ALandscape* Landscape);

	/**
	 * Filter locations based on landscape properties
	 * @param Locations Locations to filter
	 * @param Landscape Landscape to check against
	 * @param Settings Landscape placement settings
	 * @return Filtered array of valid locations
	 */
	static TArray<FVector> FilterLocationsByTerrain(
		const TArray<FVector>& Locations,
		ALandscape* Landscape,
		const FLandscapePlacementSettings& Settings);

	/**
	 * Generate placement pattern that follows terrain contours
	 * @param Landscape Landscape to follow
	 * @param StartLocation Starting location
	 * @param Count Number of points to generate
	 * @param Spacing Spacing between points
	 * @param Settings Landscape placement settings
	 * @return Array of transforms following terrain contours
	 */
	static TArray<FTransform> GenerateContourFollowingPattern(
		ALandscape* Landscape,
		const FVector& StartLocation,
		int32 Count,
		float Spacing,
		const FLandscapePlacementSettings& Settings);

	/**
	 * Integrate with foliage system by checking foliage density
	 * @param Landscape Landscape to check
	 * @param Location Location to check foliage
	 * @param Radius Radius to check
	 * @return Foliage density (0.0 = no foliage, 1.0 = dense)
	 */
	static float GetFoliageDensityAtLocation(
		ALandscape* Landscape,
		const FVector& Location,
		float Radius = 100.0f);

	/**
	 * Avoid placing actors where foliage already exists
	 * @param Locations Candidate locations
	 * @param Landscape Landscape to check
	 * @param FoliageDensityThreshold Maximum allowed foliage density
	 * @return Filtered locations avoiding foliage
	 */
	static TArray<FVector> FilterLocationsByFoliage(
		const TArray<FVector>& Locations,
		ALandscape* Landscape,
		float FoliageDensityThreshold = 0.5f);

	/**
	 * Find landscape actor in world
	 * @param World World to search
	 * @return First landscape actor found, or nullptr
	 */
	static ALandscape* FindLandscapeInWorld(UWorld* World);

	/**
	 * Get suitable placement locations on landscape based on biome rules
	 * @param Landscape Landscape to analyze
	 * @param BoundsBox Area to search
	 * @param Settings Landscape placement settings
	 * @param MaxLocations Maximum number of locations to return
	 * @return Array of suitable locations
	 */
	static TArray<FVector> GetSuitablePlacementLocations(
		ALandscape* Landscape,
		const FBox& BoundsBox,
		const FLandscapePlacementSettings& Settings,
		int32 MaxLocations = 100);

	/**
	 * Calculate terrain complexity in an area (for adaptive density)
	 * @param Landscape Landscape to analyze
	 * @param Location Center location
	 * @param Radius Radius to analyze
	 * @return Complexity value (0.0 = flat, 1.0 = very complex)
	 */
	static float CalculateTerrainComplexity(
		ALandscape* Landscape,
		const FVector& Location,
		float Radius = 500.0f);

private:
	/**
	 * Helper to convert world location to landscape coordinates
	 */
	static FVector2D WorldToLandscapeCoords(
		ALandscape* Landscape,
		const FVector& WorldLocation);

	/**
	 * Helper to convert landscape coordinates to world location
	 */
	static FVector LandscapeToWorldCoords(
		ALandscape* Landscape,
		const FVector2D& LandscapeCoords,
		float Height);

	/**
	 * Check if location meets height requirements
	 */
	static bool MeetsHeightRequirements(
		float Height,
		const FLandscapePlacementSettings& Settings);

	/**
	 * Check if location meets slope requirements
	 */
	static bool MeetsSlopeRequirements(
		float Slope,
		const FLandscapePlacementSettings& Settings);

	/**
	 * Get biome-specific distribution parameters
	 */
	static void GetBiomeParameters(
		EBiomeType BiomeType,
		float& OutMinDistance,
		float& OutClusteriness);
};
