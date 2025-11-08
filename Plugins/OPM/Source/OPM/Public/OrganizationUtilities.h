// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * Utility class for organizing actors in the world outliner
 */
class UOPM_OrganizationUtilities
{
public:
	/**
	 * Set folder path for actors
	 * @param Actors Array of actors to organize
	 * @param FolderPath Folder path (e.g., "Environment/Props")
	 */
	static void SetActorFolder(
		TArray<AActor*> Actors,
		const FName& FolderPath);

	/**
	 * Group actors by type and place in folders
	 * @param Actors Array of actors to group
	 * @param bUseClassName Whether to use class name for folder naming
	 */
	static void GroupActorsByType(
		TArray<AActor*> Actors,
		bool bUseClassName = true);

	/**
	 * Apply tags to actors
	 * @param Actors Array of actors to tag
	 * @param Tags Tags to apply
	 * @param bReplace Whether to replace existing tags or add to them
	 */
	static void ApplyTagsToActors(
		TArray<AActor*> Actors,
		const TArray<FName>& Tags,
		bool bReplace = false);

	/**
	 * Remove tags from actors
	 * @param Actors Array of actors to process
	 * @param Tags Tags to remove
	 */
	static void RemoveTagsFromActors(
		TArray<AActor*> Actors,
		const TArray<FName>& Tags);

	/**
	 * Clear all tags from actors
	 * @param Actors Array of actors to clear
	 */
	static void ClearActorTags(TArray<AActor*> Actors);

	/**
	 * Attach actors to a parent actor
	 * @param Actors Array of actors to attach
	 * @param ParentActor Parent actor to attach to
	 * @param bMaintainWorldTransform Whether to maintain world transform
	 */
	static void AttachActorsToParent(
		TArray<AActor*> Actors,
		AActor* ParentActor,
		bool bMaintainWorldTransform = true);

	/**
	 * Detach actors from their parents
	 * @param Actors Array of actors to detach
	 * @param bMaintainWorldTransform Whether to maintain world transform
	 */
	static void DetachActorsFromParent(
		TArray<AActor*> Actors,
		bool bMaintainWorldTransform = true);

	/**
	 * Create a parent actor for grouping
	 * @param World World to spawn in
	 * @param Location Location for parent actor
	 * @param GroupName Name for the parent actor
	 * @return Spawned parent actor
	 */
	static AActor* CreateParentActor(
		UWorld* World,
		const FVector& Location,
		const FString& GroupName);
};
