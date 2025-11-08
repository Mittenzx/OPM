// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OPMTypes.h"
#include "GameFramework/Actor.h"

/**
 * Utility class for aligning and distributing actors
 */
class UOPM_AlignmentUtilities
{
public:
	/**
	 * Align actors based on alignment type and axis
	 * @param Actors Array of actors to align
	 * @param Type Alignment type (left, right, center, etc.)
	 * @param Axis Alignment axis (X, Y, or Z)
	 */
	static void AlignActors(
		TArray<AActor*> Actors,
		EAlignmentType Type,
		EAlignmentAxis Axis);

	/**
	 * Align actors to the left (minimum X)
	 * @param Actors Array of actors to align
	 */
	static void AlignActorsLeft(TArray<AActor*> Actors);

	/**
	 * Align actors to the right (maximum X)
	 * @param Actors Array of actors to align
	 */
	static void AlignActorsRight(TArray<AActor*> Actors);

	/**
	 * Align actors to the top (maximum Z)
	 * @param Actors Array of actors to align
	 */
	static void AlignActorsTop(TArray<AActor*> Actors);

	/**
	 * Align actors to the bottom (minimum Z)
	 * @param Actors Array of actors to align
	 */
	static void AlignActorsBottom(TArray<AActor*> Actors);

	/**
	 * Align actors to the front (minimum Y)
	 * @param Actors Array of actors to align
	 */
	static void AlignActorsFront(TArray<AActor*> Actors);

	/**
	 * Align actors to the back (maximum Y)
	 * @param Actors Array of actors to align
	 */
	static void AlignActorsBack(TArray<AActor*> Actors);

	/**
	 * Center actors on X axis
	 * @param Actors Array of actors to center
	 */
	static void CenterActorsX(TArray<AActor*> Actors);

	/**
	 * Center actors on Y axis
	 * @param Actors Array of actors to center
	 */
	static void CenterActorsY(TArray<AActor*> Actors);

	/**
	 * Center actors on Z axis
	 * @param Actors Array of actors to center
	 */
	static void CenterActorsZ(TArray<AActor*> Actors);

	/**
	 * Distribute actors evenly
	 * @param Actors Array of actors to distribute
	 * @param Type Distribution type (horizontal, vertical, radial)
	 */
	static void DistributeActors(
		TArray<AActor*> Actors,
		EDistributionType Type);

	/**
	 * Distribute actors horizontally (X axis)
	 * @param Actors Array of actors to distribute
	 */
	static void DistributeActorsHorizontally(TArray<AActor*> Actors);

	/**
	 * Distribute actors vertically (Z axis)
	 * @param Actors Array of actors to distribute
	 */
	static void DistributeActorsVertically(TArray<AActor*> Actors);

	/**
	 * Get the combined bounds of all actors
	 * @param Actors Array of actors
	 * @return Bounding box containing all actors
	 */
	static FBox GetActorsBounds(const TArray<AActor*>& Actors);

	/**
	 * Get the center point of all actors
	 * @param Actors Array of actors
	 * @return Center point
	 */
	static FVector GetActorsCenter(const TArray<AActor*>& Actors);

	/**
	 * Snap actor location to grid
	 * @param Actor Actor to snap
	 * @param GridSize Grid size for snapping
	 */
	static void SnapActorToGrid(AActor* Actor, float GridSize);

	/**
	 * Snap multiple actors to grid
	 * @param Actors Array of actors to snap
	 * @param GridSize Grid size for snapping
	 */
	static void SnapActorsToGrid(TArray<AActor*> Actors, float GridSize);
};
