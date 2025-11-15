// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OPMTypes.h"
#include "GameFramework/Actor.h"
#include "OPMBlueprintLibrary.generated.h"

/**
 * Blueprint library exposing OPM functionality to Blueprints and Editor Utility Widgets
 */
UCLASS()
class OPM_API UOPMBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ==================== Placement Functions ====================

	/**
	 * Generate transforms for a grid pattern
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Placement")
	static TArray<FTransform> GenerateGridPattern(
		const FGridPatternSettings& Settings,
		const FTransform& Origin);

	/**
	 * Generate transforms for a circular pattern
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Placement")
	static TArray<FTransform> GenerateCircularPattern(
		const FCircularPatternSettings& Settings,
		const FTransform& Center);

	/**
	 * Generate transforms for a line pattern
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Placement")
	static TArray<FTransform> GenerateLinePattern(
		const FLinePatternSettings& Settings,
		const FTransform& BaseTransform);

	/**
	 * Generate transforms for a random scatter pattern
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Placement")
	static TArray<FTransform> GenerateRandomPattern(
		const FRandomPatternSettings& Settings,
		const FTransform& BaseTransform);

	/**
	 * Place actors in the world using the given transforms
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Placement", meta = (WorldContext = "WorldContextObject"))
	static TArray<AActor*> PlaceActorsInPattern(
		UObject* WorldContextObject,
		UClass* ActorClass,
		const TArray<FTransform>& Transforms);

	// ==================== Alignment Functions ====================

	/**
	 * Align actors based on alignment type
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void AlignActors(
		TArray<AActor*> Actors,
		EAlignmentType Type,
		EAlignmentAxis Axis);

	/**
	 * Align actors to the left
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void AlignActorsLeft(TArray<AActor*> Actors);

	/**
	 * Align actors to the right
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void AlignActorsRight(TArray<AActor*> Actors);

	/**
	 * Align actors to the top
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void AlignActorsTop(TArray<AActor*> Actors);

	/**
	 * Align actors to the bottom
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void AlignActorsBottom(TArray<AActor*> Actors);

	/**
	 * Center actors on X axis
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void CenterActorsX(TArray<AActor*> Actors);

	/**
	 * Center actors on Y axis
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void CenterActorsY(TArray<AActor*> Actors);

	/**
	 * Center actors on Z axis
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void CenterActorsZ(TArray<AActor*> Actors);

	/**
	 * Distribute actors evenly
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void DistributeActors(
		TArray<AActor*> Actors,
		EDistributionType Type);

	/**
	 * Snap actors to grid
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
	static void SnapActorsToGrid(TArray<AActor*> Actors, float GridSize);

	// ==================== Naming Functions ====================

	/**
	 * Batch rename actors with prefix, suffix, and auto-numbering
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Naming")
	static void BatchRename(
		TArray<AActor*> Actors,
		const FString& Prefix,
		const FString& Suffix,
		int32 StartNumber,
		int32 Padding);

	/**
	 * Add prefix to actor names
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Naming")
	static void AddPrefix(TArray<AActor*> Actors, const FString& Prefix);

	/**
	 * Add suffix to actor names
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Naming")
	static void AddSuffix(TArray<AActor*> Actors, const FString& Suffix);

	/**
	 * Auto-number actors sequentially
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Naming")
	static void AutoNumber(TArray<AActor*> Actors, int32 StartNumber, int32 Padding);

	/**
	 * Find and replace text in actor names
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Naming")
	static void FindAndReplace(
		TArray<AActor*> Actors,
		const FString& FindStr,
		const FString& ReplaceStr,
		bool bCaseSensitive);

	// ==================== Replacement Functions ====================

	/**
	 * Replace actors with new actor class
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Replacement", meta = (WorldContext = "WorldContextObject"))
	static TArray<AActor*> BatchReplaceActors(
		UObject* WorldContextObject,
		TArray<AActor*> OldActors,
		UClass* NewActorClass,
		bool bPreserveTransform,
		bool bPreserveAttachments);

	// ==================== Organization Functions ====================

	/**
	 * Set folder path for actors
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Organization")
	static void SetActorFolder(TArray<AActor*> Actors, const FString& FolderPath);

	/**
	 * Group actors by type
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Organization")
	static void GroupActorsByType(TArray<AActor*> Actors);

	/**
	 * Apply tags to actors
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Organization")
	static void ApplyTags(TArray<AActor*> Actors, const TArray<FName>& Tags);

	/**
	 * Attach actors to a parent
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Organization")
	static void AttachActorsToParent(
		TArray<AActor*> Actors,
		AActor* ParentActor,
		bool bMaintainWorldTransform);

	/**
	 * Detach actors from parent
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Organization")
	static void DetachActorsFromParent(TArray<AActor*> Actors, bool bMaintainWorldTransform);

	// ==================== Utility Functions ====================

	/**
	 * Get currently selected actors in editor
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Utility")
	static TArray<AActor*> GetSelectedActors();

	/**
	 * Get actors bounds
	 */
	UFUNCTION(BlueprintPure, Category = "OPM|Utility")
	static FBox GetActorsBounds(const TArray<AActor*>& Actors);

	/**
	 * Get actors center point
	 */
	UFUNCTION(BlueprintPure, Category = "OPM|Utility")
	static FVector GetActorsCenter(const TArray<AActor*>& Actors);

	// ==================== AI-Assisted Placement (v2.0) ====================

	/**
	 * Detect placement pattern from existing actors
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|AI Placement")
	static EAIPatternType DetectPlacementPattern(const TArray<AActor*>& Actors);

	/**
	 * Generate smart placement suggestions based on existing actors
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|AI Placement")
	static int32 GenerateSmartSuggestions(
		const TArray<AActor*>& ExistingActors,
		const FAIPlacementSettings& Settings,
		TArray<FTransform>& SuggestedTransforms);

	/**
	 * Optimize actor placement based on optimization goal
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|AI Placement")
	static TArray<FTransform> OptimizeActorPlacement(
		const TArray<AActor*>& Actors,
		const FAIPlacementSettings& Settings);

	/**
	 * Generate organic-looking placement pattern
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|AI Placement")
	static TArray<FTransform> GenerateOrganicPattern(
		const FBox& BoundsBox,
		int32 Count,
		const FAIPlacementSettings& Settings);

	/**
	 * Evaluate placement quality score
	 */
	UFUNCTION(BlueprintPure, Category = "OPM|AI Placement")
	static float EvaluatePlacementQuality(const TArray<AActor*>& Actors);

	// ==================== Landscape Integration (v2.0) ====================

	/**
	 * Place actors on landscape with terrain-aware positioning
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Landscape", meta = (WorldContext = "WorldContextObject"))
	static TArray<AActor*> PlaceActorsOnLandscape(
		UObject* WorldContextObject,
		UClass* ActorClass,
		const TArray<FTransform>& Transforms,
		class ALandscape* Landscape,
		const FLandscapePlacementSettings& Settings);

	/**
	 * Sample landscape height at a given location
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Landscape")
	static bool SampleLandscapeHeight(
		class ALandscape* Landscape,
		const FVector& Location,
		float& OutHeight);

	/**
	 * Calculate slope angle at a landscape location
	 */
	UFUNCTION(BlueprintPure, Category = "OPM|Landscape")
	static float CalculateSlopeAngle(
		class ALandscape* Landscape,
		const FVector& Location);

	/**
	 * Distribute actors based on biome type
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Landscape")
	static TArray<FTransform> DistributeByBiome(
		const FBox& BoundsBox,
		int32 Count,
		EBiomeType BiomeType,
		class ALandscape* Landscape);

	/**
	 * Find landscape actor in world
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Landscape", meta = (WorldContext = "WorldContextObject"))
	static class ALandscape* FindLandscapeInWorld(UObject* WorldContextObject);

	// ==================== Spline-Based Tools (v2.0) ====================

	/**
	 * Place actors along a spline path
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Spline", meta = (WorldContext = "WorldContextObject"))
	static TArray<AActor*> PlaceActorsAlongSpline(
		UObject* WorldContextObject,
		UClass* ActorClass,
		class USplineComponent* SplineComponent,
		const FSplinePlacementSettings& Settings);

	/**
	 * Generate transforms along a spline
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Spline")
	static TArray<FTransform> GenerateTransformsAlongSpline(
		class USplineComponent* SplineComponent,
		const FSplinePlacementSettings& Settings);

	/**
	 * Generate road with props along spline
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Spline", meta = (WorldContext = "WorldContextObject"))
	static TArray<AActor*> GenerateRoadAlongSpline(
		UObject* WorldContextObject,
		class USplineComponent* SplineComponent,
		UClass* RoadActorClass,
		const TArray<UClass*>& PropActorClasses,
		float PropSpacing);

	/**
	 * Generate fence along spline
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Spline", meta = (WorldContext = "WorldContextObject"))
	static TArray<AActor*> GenerateFenceAlongSpline(
		UObject* WorldContextObject,
		class USplineComponent* SplineComponent,
		UClass* PostActorClass,
		UClass* PanelActorClass,
		float PostSpacing);

	/**
	 * Generate cable routing along spline
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Spline", meta = (WorldContext = "WorldContextObject"))
	static TArray<AActor*> GenerateCableRoutingAlongSpline(
		UObject* WorldContextObject,
		class USplineComponent* SplineComponent,
		UClass* CableActorClass,
		UClass* SupportsActorClass,
		float SupportSpacing,
		float SagAmount);

	/**
	 * Get spline length
	 */
	UFUNCTION(BlueprintPure, Category = "OPM|Spline")
	static float GetSplineLength(class USplineComponent* SplineComponent);

	/**
	 * Get adaptive distances based on spline curvature
	 */
	UFUNCTION(BlueprintCallable, Category = "OPM|Spline")
	static TArray<float> GetAdaptiveDistances(
		class USplineComponent* SplineComponent,
		float MinSpacing,
		float MaxSpacing);
};
