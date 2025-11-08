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
