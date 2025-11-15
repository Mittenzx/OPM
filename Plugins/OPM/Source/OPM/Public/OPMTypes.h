// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OPMTypes.generated.h"

/**
 * Alignment type for actor alignment operations
 */
UENUM(BlueprintType)
enum class EAlignmentType : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Top UMETA(DisplayName = "Top"),
	Bottom UMETA(DisplayName = "Bottom"),
	Front UMETA(DisplayName = "Front"),
	Back UMETA(DisplayName = "Back"),
	CenterX UMETA(DisplayName = "Center X"),
	CenterY UMETA(DisplayName = "Center Y"),
	CenterZ UMETA(DisplayName = "Center Z")
};

/**
 * Alignment axis for actor alignment operations
 */
UENUM(BlueprintType)
enum class EAlignmentAxis : uint8
{
	X UMETA(DisplayName = "X Axis"),
	Y UMETA(DisplayName = "Y Axis"),
	Z UMETA(DisplayName = "Z Axis")
};

/**
 * Distribution type for distributing actors
 */
UENUM(BlueprintType)
enum class EDistributionType : uint8
{
	Horizontal UMETA(DisplayName = "Horizontal"),
	Vertical UMETA(DisplayName = "Vertical"),
	Radial UMETA(DisplayName = "Radial")
};

/**
 * Pattern type for batch placement
 */
UENUM(BlueprintType)
enum class EPlacementPattern : uint8
{
	Grid UMETA(DisplayName = "Grid"),
	Circular UMETA(DisplayName = "Circular"),
	Line UMETA(DisplayName = "Line"),
	Random UMETA(DisplayName = "Random")
};

/**
 * Grid pattern settings
 */
USTRUCT(BlueprintType)
struct FGridPatternSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid", meta = (ClampMin = "1"))
	int32 Rows = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid", meta = (ClampMin = "1"))
	int32 Columns = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FVector Spacing = FVector(100.0f, 100.0f, 0.0f);
};

/**
 * Circular pattern settings
 */
USTRUCT(BlueprintType)
struct FCircularPatternSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Circular", meta = (ClampMin = "0.0"))
	float Radius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Circular", meta = (ClampMin = "1"))
	int32 Count = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Circular")
	float StartAngle = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Circular")
	float Height = 0.0f;
};

/**
 * Line pattern settings
 */
USTRUCT(BlueprintType)
struct FLinePatternSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line")
	FVector StartPoint = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line")
	FVector EndPoint = FVector(1000.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line", meta = (ClampMin = "2"))
	int32 Count = 10;
};

/**
 * Random scatter pattern settings
 */
USTRUCT(BlueprintType)
struct FRandomPatternSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random")
	FBox BoundsBox = FBox(FVector(-500.0f), FVector(500.0f));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random", meta = (ClampMin = "1"))
	int32 Count = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random")
	int32 Seed = 0;
};

// ============================================================================
// Version 2.0 Types - AI-Assisted Placement
// ============================================================================

/**
 * AI placement optimization goal
 */
UENUM(BlueprintType)
enum class EAIOptimizationGoal : uint8
{
	Performance UMETA(DisplayName = "Performance"),
	VisualQuality UMETA(DisplayName = "Visual Quality"),
	Balanced UMETA(DisplayName = "Balanced"),
	Memory UMETA(DisplayName = "Memory Efficiency")
};

/**
 * AI placement pattern type for recognition
 */
UENUM(BlueprintType)
enum class EAIPatternType : uint8
{
	Clustered UMETA(DisplayName = "Clustered"),
	Scattered UMETA(DisplayName = "Scattered"),
	Linear UMETA(DisplayName = "Linear"),
	Organic UMETA(DisplayName = "Organic"),
	Grid UMETA(DisplayName = "Grid"),
	Radial UMETA(DisplayName = "Radial")
};

/**
 * AI placement suggestion settings
 */
USTRUCT(BlueprintType)
struct FAIPlacementSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Placement")
	EAIOptimizationGoal OptimizationGoal = EAIOptimizationGoal::Balanced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Placement", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Confidence = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Placement")
	bool bAutoOptimize = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Placement", meta = (ClampMin = "1"))
	int32 MaxSuggestions = 5;
};

// ============================================================================
// Version 2.0 Types - Landscape Integration
// ============================================================================

/**
 * Terrain alignment mode for landscape placement
 */
UENUM(BlueprintType)
enum class ETerrainAlignment : uint8
{
	None UMETA(DisplayName = "None"),
	AlignToNormal UMETA(DisplayName = "Align To Normal"),
	AlignToSlope UMETA(DisplayName = "Align To Slope"),
	SnapToSurface UMETA(DisplayName = "Snap To Surface")
};

/**
 * Biome type for distribution
 */
UENUM(BlueprintType)
enum class EBiomeType : uint8
{
	Forest UMETA(DisplayName = "Forest"),
	Desert UMETA(DisplayName = "Desert"),
	Mountain UMETA(DisplayName = "Mountain"),
	Plains UMETA(DisplayName = "Plains"),
	Water UMETA(DisplayName = "Water"),
	Urban UMETA(DisplayName = "Urban"),
	Custom UMETA(DisplayName = "Custom")
};

/**
 * Landscape placement settings
 */
USTRUCT(BlueprintType)
struct FLandscapePlacementSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape")
	ETerrainAlignment TerrainAlignment = ETerrainAlignment::AlignToNormal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape", meta = (ClampMin = "0.0", ClampMax = "90.0"))
	float MaxSlope = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape", meta = (ClampMin = "0.0"))
	float MinHeight = -10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape", meta = (ClampMin = "0.0"))
	float MaxHeight = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape")
	bool bUseFoliageRules = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape")
	EBiomeType BiomeType = EBiomeType::Plains;
};

// ============================================================================
// Version 2.0 Types - Spline-Based Tools
// ============================================================================

/**
 * Spline placement mode
 */
UENUM(BlueprintType)
enum class ESplinePlacementMode : uint8
{
	Uniform UMETA(DisplayName = "Uniform Spacing"),
	ByDistance UMETA(DisplayName = "By Distance"),
	BySplinePoints UMETA(DisplayName = "By Spline Points"),
	Adaptive UMETA(DisplayName = "Adaptive")
};

/**
 * Spline alignment mode
 */
UENUM(BlueprintType)
enum class ESplineAlignment : uint8
{
	Tangent UMETA(DisplayName = "Align To Tangent"),
	Normal UMETA(DisplayName = "Align To Normal"),
	Up UMETA(DisplayName = "Align To Up Vector"),
	None UMETA(DisplayName = "No Alignment")
};

/**
 * Spline placement settings
 */
USTRUCT(BlueprintType)
struct FSplinePlacementSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	ESplinePlacementMode PlacementMode = ESplinePlacementMode::Uniform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	ESplineAlignment Alignment = ESplineAlignment::Tangent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline", meta = (ClampMin = "0.0"))
	float Spacing = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	FVector Offset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	bool bScaleBySpline = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline", meta = (ClampMin = "0.0"))
	float StartOffset = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline", meta = (ClampMin = "0.0"))
	float EndOffset = 0.0f;
};
