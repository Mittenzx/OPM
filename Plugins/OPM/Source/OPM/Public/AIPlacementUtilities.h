// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OPMTypes.h"
#include "GameFramework/Actor.h"

/**
 * Utility class for AI-assisted placement operations
 * Provides machine learning-based pattern recognition, smart suggestions, and automatic optimization
 */
class UOPM_AIPlacementUtilities
{
public:
	/**
	 * Analyze existing actor placement and detect the pattern type
	 * @param Actors Array of actors to analyze
	 * @return Detected pattern type
	 */
	static EAIPatternType DetectPlacementPattern(const TArray<AActor*>& Actors);

	/**
	 * Generate smart placement suggestions based on existing actors
	 * @param ExistingActors Actors to analyze for context
	 * @param Settings AI placement settings
	 * @param SuggestedTransforms Output array of suggested transforms
	 * @return Number of suggestions generated
	 */
	static int32 GenerateSmartSuggestions(
		const TArray<AActor*>& ExistingActors,
		const FAIPlacementSettings& Settings,
		TArray<FTransform>& SuggestedTransforms);

	/**
	 * Optimize actor placement based on optimization goal
	 * @param Actors Actors to optimize
	 * @param Settings AI placement settings
	 * @return Array of optimized transforms (same order as input actors)
	 */
	static TArray<FTransform> OptimizeActorPlacement(
		const TArray<AActor*>& Actors,
		const FAIPlacementSettings& Settings);

	/**
	 * Calculate clustering density for actors
	 * @param Actors Actors to analyze
	 * @return Density value (higher = more clustered)
	 */
	static float CalculateClusteringDensity(const TArray<AActor*>& Actors);

	/**
	 * Find optimal spacing between actors based on their bounds
	 * @param ActorBounds Array of actor bounds
	 * @param DesiredDensity Desired density (0.0 = loose, 1.0 = tight)
	 * @return Optimal spacing value
	 */
	static float CalculateOptimalSpacing(
		const TArray<FBox>& ActorBounds,
		float DesiredDensity = 0.5f);

	/**
	 * Detect and suggest corrections for overlapping actors
	 * @param Actors Actors to check for overlaps
	 * @param CorrectedTransforms Output array of corrected transforms
	 * @return Number of overlaps detected and corrected
	 */
	static int32 DetectAndCorrectOverlaps(
		const TArray<AActor*>& Actors,
		TArray<FTransform>& CorrectedTransforms);

	/**
	 * Generate organic-looking placement pattern
	 * @param BoundsBox Bounding box for placement
	 * @param Count Number of objects to place
	 * @param Settings AI placement settings
	 * @return Array of transforms with organic distribution
	 */
	static TArray<FTransform> GenerateOrganicPattern(
		const FBox& BoundsBox,
		int32 Count,
		const FAIPlacementSettings& Settings);

	/**
	 * Suggest LOD (Level of Detail) settings based on placement density
	 * @param Actors Actors to analyze
	 * @param OptimizationGoal Optimization goal
	 * @return Suggested LOD distances for each actor
	 */
	static TArray<float> SuggestLODSettings(
		const TArray<AActor*>& Actors,
		EAIOptimizationGoal OptimizationGoal);

	/**
	 * Calculate placement quality score
	 * @param Actors Actors to evaluate
	 * @return Quality score (0.0 = poor, 1.0 = excellent)
	 */
	static float EvaluatePlacementQuality(const TArray<AActor*>& Actors);

	/**
	 * Auto-balance actor distribution in a given area
	 * @param Actors Actors to balance
	 * @param BoundsBox Area to balance within
	 * @return Array of balanced transforms
	 */
	static TArray<FTransform> AutoBalanceDistribution(
		const TArray<AActor*>& Actors,
		const FBox& BoundsBox);

private:
	/**
	 * Calculate variance in actor spacing
	 */
	static float CalculateSpacingVariance(const TArray<AActor*>& Actors);

	/**
	 * Detect linear patterns in actor placement
	 */
	static bool DetectLinearPattern(const TArray<AActor*>& Actors, float Tolerance = 50.0f);

	/**
	 * Detect radial patterns in actor placement
	 */
	static bool DetectRadialPattern(const TArray<AActor*>& Actors, float Tolerance = 50.0f);

	/**
	 * Calculate centroid of actor positions
	 */
	static FVector CalculateCentroid(const TArray<AActor*>& Actors);

	/**
	 * Apply jitter to make placement look more organic
	 */
	static void ApplyOrganicJitter(TArray<FTransform>& Transforms, float JitterAmount);
};
