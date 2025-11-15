// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OPMTypes.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"

/**
 * Utility class for spline-based placement operations
 * Provides path-following placement, road/fence generation, and cable/pipe routing
 */
class OPM_API UOPM_SplineUtilities
{
public:
	/**
	 * Place actors along a spline path
	 * @param ActorClass Class of actor to spawn
	 * @param SplineComponent Spline to follow
	 * @param Settings Spline placement settings
	 * @param World World to spawn actors in
	 * @return Array of spawned actors
	 */
	static TArray<AActor*> PlaceActorsAlongSpline(
		UClass* ActorClass,
		USplineComponent* SplineComponent,
		const FSplinePlacementSettings& Settings,
		UWorld* World);

	/**
	 * Generate transforms along a spline
	 * @param SplineComponent Spline to follow
	 * @param Settings Spline placement settings
	 * @return Array of transforms along the spline
	 */
	static TArray<FTransform> GenerateTransformsAlongSpline(
		USplineComponent* SplineComponent,
		const FSplinePlacementSettings& Settings);

	/**
	 * Generate road/path with props along spline
	 * @param SplineComponent Spline defining the road path
	 * @param RoadActorClass Actor class for road segments
	 * @param PropActorClasses Array of prop classes (signs, barriers, etc.)
	 * @param PropSpacing Spacing between props
	 * @param World World to spawn in
	 * @return Array of all spawned actors (road + props)
	 */
	static TArray<AActor*> GenerateRoadAlongSpline(
		USplineComponent* SplineComponent,
		UClass* RoadActorClass,
		const TArray<UClass*>& PropActorClasses,
		float PropSpacing,
		UWorld* World);

	/**
	 * Generate fence along spline
	 * @param SplineComponent Spline defining the fence path
	 * @param PostActorClass Actor class for fence posts
	 * @param PanelActorClass Actor class for fence panels
	 * @param PostSpacing Spacing between posts
	 * @param World World to spawn in
	 * @return Array of spawned fence actors
	 */
	static TArray<AActor*> GenerateFenceAlongSpline(
		USplineComponent* SplineComponent,
		UClass* PostActorClass,
		UClass* PanelActorClass,
		float PostSpacing,
		UWorld* World);

	/**
	 * Generate cable/pipe routing along spline
	 * @param SplineComponent Spline defining the cable path
	 * @param CableActorClass Actor class for cable segments
	 * @param SupportsActorClass Actor class for support structures
	 * @param SupportSpacing Spacing between supports
	 * @param SagAmount Amount of sag in cable (0 = no sag)
	 * @param World World to spawn in
	 * @return Array of spawned cable and support actors
	 */
	static TArray<AActor*> GenerateCableRoutingAlongSpline(
		USplineComponent* SplineComponent,
		UClass* CableActorClass,
		UClass* SupportsActorClass,
		float SupportSpacing,
		float SagAmount,
		UWorld* World);

	/**
	 * Calculate distance along spline
	 * @param SplineComponent Spline to measure
	 * @return Total length of the spline
	 */
	static float GetSplineLength(USplineComponent* SplineComponent);

	/**
	 * Get transform at distance along spline
	 * @param SplineComponent Spline to query
	 * @param Distance Distance along spline
	 * @param Alignment How to align the transform
	 * @return Transform at the specified distance
	 */
	static FTransform GetTransformAtDistance(
		USplineComponent* SplineComponent,
		float Distance,
		ESplineAlignment Alignment = ESplineAlignment::Tangent);

	/**
	 * Get array of distances for uniform placement
	 * @param SplineLength Total spline length
	 * @param Spacing Spacing between points
	 * @param StartOffset Offset from start
	 * @param EndOffset Offset from end
	 * @return Array of distances along spline
	 */
	static TArray<float> GetUniformDistances(
		float SplineLength,
		float Spacing,
		float StartOffset = 0.0f,
		float EndOffset = 0.0f);

	/**
	 * Get array of distances based on spline points
	 * @param SplineComponent Spline to use
	 * @return Array of distances at spline points
	 */
	static TArray<float> GetSplinePointDistances(USplineComponent* SplineComponent);

	/**
	 * Get adaptive distances based on spline curvature
	 * @param SplineComponent Spline to analyze
	 * @param MinSpacing Minimum spacing between points
	 * @param MaxSpacing Maximum spacing on straight sections
	 * @return Array of adaptive distances
	 */
	static TArray<float> GetAdaptiveDistances(
		USplineComponent* SplineComponent,
		float MinSpacing = 50.0f,
		float MaxSpacing = 200.0f);

	/**
	 * Calculate curvature at distance along spline
	 * @param SplineComponent Spline to analyze
	 * @param Distance Distance along spline
	 * @return Curvature value (0 = straight, higher = more curved)
	 */
	static float GetCurvatureAtDistance(
		USplineComponent* SplineComponent,
		float Distance);

	/**
	 * Smooth spline by adjusting tangents
	 * @param SplineComponent Spline to smooth
	 * @param SmoothingFactor Smoothing factor (0 = no change, 1 = maximum smoothing)
	 */
	static void SmoothSpline(
		USplineComponent* SplineComponent,
		float SmoothingFactor = 0.5f);

	/**
	 * Distribute actors with varying density based on spline curvature
	 * @param ActorClass Actor class to spawn
	 * @param SplineComponent Spline to follow
	 * @param BaseDensity Base number of actors per unit length
	 * @param CurvatureFactor How much curvature affects density (higher = more actors on curves)
	 * @param World World to spawn in
	 * @return Array of spawned actors
	 */
	static TArray<AActor*> PlaceActorsWithVariableDensity(
		UClass* ActorClass,
		USplineComponent* SplineComponent,
		float BaseDensity,
		float CurvatureFactor,
		UWorld* World);

	/**
	 * Create parallel spline offset from original
	 * @param SourceSpline Source spline
	 * @param Offset Offset distance (positive = right, negative = left)
	 * @param TargetSpline Spline to modify (will be cleared and repopulated)
	 */
	static void CreateParallelSpline(
		USplineComponent* SourceSpline,
		float Offset,
		USplineComponent* TargetSpline);

	/**
	 * Snap spline points to terrain
	 * @param SplineComponent Spline to snap
	 * @param World World for terrain queries
	 * @param HeightOffset Additional height offset after snapping
	 */
	static void SnapSplineToTerrain(
		USplineComponent* SplineComponent,
		UWorld* World,
		float HeightOffset = 0.0f);

	/**
	 * Create branching paths from a main spline
	 * @param MainSpline Main spline path
	 * @param BranchLocations Array of distances along main spline where branches start
	 * @param BranchAngles Array of angles for each branch (degrees)
	 * @param BranchLengths Array of lengths for each branch
	 * @return Array of created branch spline components
	 */
	static TArray<USplineComponent*> CreateBranchingSplines(
		USplineComponent* MainSpline,
		const TArray<float>& BranchLocations,
		const TArray<float>& BranchAngles,
		const TArray<float>& BranchLengths);

private:
	/**
	 * Helper to calculate tangent-aligned rotation
	 */
	static FRotator GetTangentRotation(
		USplineComponent* SplineComponent,
		float Distance);

	/**
	 * Helper to calculate normal-aligned rotation
	 */
	static FRotator GetNormalRotation(
		USplineComponent* SplineComponent,
		float Distance);

	/**
	 * Helper to apply offset to transform
	 */
	static FTransform ApplyOffsetToTransform(
		const FTransform& BaseTransform,
		const FVector& Offset);

	/**
	 * Helper to calculate cable sag transform
	 */
	static FVector CalculateCableSag(
		const FVector& Start,
		const FVector& End,
		float Alpha,
		float SagAmount);
};
