// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OPMTypes.h"
#include "GameFramework/Actor.h"

/**
 * Utility class for batch object placement in various patterns
 */
class UOPM_PlacementUtilities
{
public:
	/**
	 * Generate transforms for a grid pattern
	 * @param Rows Number of rows in the grid
	 * @param Columns Number of columns in the grid
	 * @param Spacing Spacing between objects in X, Y, Z
	 * @param Origin Origin transform for the pattern
	 * @return Array of transforms for object placement
	 */
	static TArray<FTransform> GenerateGridPattern(
		int32 Rows,
		int32 Columns,
		FVector Spacing,
		const FTransform& Origin);

	/**
	 * Generate transforms for a grid pattern using settings struct
	 * @param Settings Grid pattern settings
	 * @param Origin Origin transform for the pattern
	 * @return Array of transforms for object placement
	 */
	static TArray<FTransform> GenerateGridPattern(
		const FGridPatternSettings& Settings,
		const FTransform& Origin);

	/**
	 * Generate transforms for a circular pattern
	 * @param Radius Radius of the circle
	 * @param Count Number of objects to place
	 * @param StartAngle Starting angle in degrees
	 * @param Center Center transform of the pattern
	 * @return Array of transforms for object placement
	 */
	static TArray<FTransform> GenerateCircularPattern(
		float Radius,
		int32 Count,
		float StartAngle,
		const FTransform& Center);

	/**
	 * Generate transforms for a circular pattern using settings struct
	 * @param Settings Circular pattern settings
	 * @param Center Center transform of the pattern
	 * @return Array of transforms for object placement
	 */
	static TArray<FTransform> GenerateCircularPattern(
		const FCircularPatternSettings& Settings,
		const FTransform& Center);

	/**
	 * Generate transforms for a line pattern
	 * @param StartPoint Starting point
	 * @param EndPoint Ending point
	 * @param Count Number of objects to place along the line
	 * @param BaseTransform Base transform for rotation and scale
	 * @return Array of transforms for object placement
	 */
	static TArray<FTransform> GenerateLinePattern(
		const FVector& StartPoint,
		const FVector& EndPoint,
		int32 Count,
		const FTransform& BaseTransform);

	/**
	 * Generate transforms for a line pattern using settings struct
	 * @param Settings Line pattern settings
	 * @param BaseTransform Base transform for rotation and scale
	 * @return Array of transforms for object placement
	 */
	static TArray<FTransform> GenerateLinePattern(
		const FLinePatternSettings& Settings,
		const FTransform& BaseTransform);

	/**
	 * Generate transforms for a random scatter pattern
	 * @param BoundsBox Bounding box for random placement
	 * @param Count Number of objects to place
	 * @param Seed Random seed (0 for random seed)
	 * @param BaseTransform Base transform for rotation and scale
	 * @return Array of transforms for object placement
	 */
	static TArray<FTransform> GenerateRandomPattern(
		const FBox& BoundsBox,
		int32 Count,
		int32 Seed,
		const FTransform& BaseTransform);

	/**
	 * Generate transforms for a random scatter pattern using settings struct
	 * @param Settings Random pattern settings
	 * @param BaseTransform Base transform for rotation and scale
	 * @return Array of transforms for object placement
	 */
	static TArray<FTransform> GenerateRandomPattern(
		const FRandomPatternSettings& Settings,
		const FTransform& BaseTransform);

	/**
	 * Place actors in the world using the given transforms
	 * @param ActorClass Class of actor to spawn
	 * @param Transforms Array of transforms for placement
	 * @param World World to spawn actors in
	 * @return Array of spawned actors
	 */
	static TArray<AActor*> PlaceActorsInPattern(
		UClass* ActorClass,
		const TArray<FTransform>& Transforms,
		UWorld* World);
};
