// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * Utility class for replacing actors while preserving transforms and properties
 */
class UOPM_ActorReplacementUtilities
{
public:
	/**
	 * Replace an actor with a new actor of different class
	 * @param OldActor Actor to replace
	 * @param NewActorClass Class of new actor to spawn
	 * @param World World to spawn in
	 * @param bPreserveTransform Whether to preserve transform (location, rotation, scale)
	 * @param bPreserveAttachments Whether to preserve parent/child attachments
	 * @return Newly spawned actor (or nullptr if failed)
	 */
	static AActor* ReplaceActor(
		AActor* OldActor,
		UClass* NewActorClass,
		UWorld* World,
		bool bPreserveTransform = true,
		bool bPreserveAttachments = false);

	/**
	 * Batch replace multiple actors with new actor class
	 * @param OldActors Array of actors to replace
	 * @param NewActorClass Class of new actor to spawn
	 * @param World World to spawn in
	 * @param bPreserveTransform Whether to preserve transforms
	 * @param bPreserveAttachments Whether to preserve attachments
	 * @return Array of newly spawned actors
	 */
	static TArray<AActor*> BatchReplaceActors(
		TArray<AActor*> OldActors,
		UClass* NewActorClass,
		UWorld* World,
		bool bPreserveTransform = true,
		bool bPreserveAttachments = false);

	/**
	 * Copy transform from one actor to another
	 * @param SourceActor Actor to copy from
	 * @param TargetActor Actor to copy to
	 */
	static void CopyTransform(AActor* SourceActor, AActor* TargetActor);

	/**
	 * Copy tags from one actor to another
	 * @param SourceActor Actor to copy from
	 * @param TargetActor Actor to copy to
	 */
	static void CopyTags(AActor* SourceActor, AActor* TargetActor);

	/**
	 * Copy attachments (parent/child relationships) from one actor to another
	 * @param SourceActor Actor to copy from
	 * @param TargetActor Actor to copy to
	 */
	static void CopyAttachments(AActor* SourceActor, AActor* TargetActor);
};
