// Copyright Epic Games, Inc. All Rights Reserved.

#include "OPMBlueprintLibrary.h"
#include "PlacementUtilities.h"
#include "AlignmentUtilities.h"
#include "NamingUtilities.h"
#include "ActorReplacementUtilities.h"
#include "OrganizationUtilities.h"
#include "Engine/World.h"
#include "Editor.h"

// ==================== Placement Functions ====================

TArray<FTransform> UOPMBlueprintLibrary::GenerateGridPattern(
	const FGridPatternSettings& Settings,
	const FTransform& Origin)
{
	return UOPM_PlacementUtilities::GenerateGridPattern(Settings, Origin);
}

TArray<FTransform> UOPMBlueprintLibrary::GenerateCircularPattern(
	const FCircularPatternSettings& Settings,
	const FTransform& Center)
{
	return UOPM_PlacementUtilities::GenerateCircularPattern(Settings, Center);
}

TArray<FTransform> UOPMBlueprintLibrary::GenerateLinePattern(
	const FLinePatternSettings& Settings,
	const FTransform& BaseTransform)
{
	return UOPM_PlacementUtilities::GenerateLinePattern(Settings, BaseTransform);
}

TArray<FTransform> UOPMBlueprintLibrary::GenerateRandomPattern(
	const FRandomPatternSettings& Settings,
	const FTransform& BaseTransform)
{
	return UOPM_PlacementUtilities::GenerateRandomPattern(Settings, BaseTransform);
}

TArray<AActor*> UOPMBlueprintLibrary::PlaceActorsInPattern(
	UObject* WorldContextObject,
	UClass* ActorClass,
	const TArray<FTransform>& Transforms)
{
	if (!WorldContextObject)
	{
		return TArray<AActor*>();
	}

	UWorld* World = WorldContextObject->GetWorld();
	return UOPM_PlacementUtilities::PlaceActorsInPattern(ActorClass, Transforms, World);
}

// ==================== Alignment Functions ====================

void UOPMBlueprintLibrary::AlignActors(
	TArray<AActor*> Actors,
	EAlignmentType Type,
	EAlignmentAxis Axis)
{
	UOPM_AlignmentUtilities::AlignActors(Actors, Type, Axis);
}

void UOPMBlueprintLibrary::AlignActorsLeft(TArray<AActor*> Actors)
{
	UOPM_AlignmentUtilities::AlignActorsLeft(Actors);
}

void UOPMBlueprintLibrary::AlignActorsRight(TArray<AActor*> Actors)
{
	UOPM_AlignmentUtilities::AlignActorsRight(Actors);
}

void UOPMBlueprintLibrary::AlignActorsTop(TArray<AActor*> Actors)
{
	UOPM_AlignmentUtilities::AlignActorsTop(Actors);
}

void UOPMBlueprintLibrary::AlignActorsBottom(TArray<AActor*> Actors)
{
	UOPM_AlignmentUtilities::AlignActorsBottom(Actors);
}

void UOPMBlueprintLibrary::CenterActorsX(TArray<AActor*> Actors)
{
	UOPM_AlignmentUtilities::CenterActorsX(Actors);
}

void UOPMBlueprintLibrary::CenterActorsY(TArray<AActor*> Actors)
{
	UOPM_AlignmentUtilities::CenterActorsY(Actors);
}

void UOPMBlueprintLibrary::CenterActorsZ(TArray<AActor*> Actors)
{
	UOPM_AlignmentUtilities::CenterActorsZ(Actors);
}

void UOPMBlueprintLibrary::DistributeActors(
	TArray<AActor*> Actors,
	EDistributionType Type)
{
	UOPM_AlignmentUtilities::DistributeActors(Actors, Type);
}

void UOPMBlueprintLibrary::SnapActorsToGrid(TArray<AActor*> Actors, float GridSize)
{
	UOPM_AlignmentUtilities::SnapActorsToGrid(Actors, GridSize);
}

// ==================== Naming Functions ====================

void UOPMBlueprintLibrary::BatchRename(
	TArray<AActor*> Actors,
	const FString& Prefix,
	const FString& Suffix,
	int32 StartNumber,
	int32 Padding)
{
	UOPM_NamingUtilities::BatchRename(Actors, Prefix, Suffix, StartNumber, Padding);
}

void UOPMBlueprintLibrary::AddPrefix(TArray<AActor*> Actors, const FString& Prefix)
{
	UOPM_NamingUtilities::AddPrefix(Actors, Prefix);
}

void UOPMBlueprintLibrary::AddSuffix(TArray<AActor*> Actors, const FString& Suffix)
{
	UOPM_NamingUtilities::AddSuffix(Actors, Suffix);
}

void UOPMBlueprintLibrary::AutoNumber(TArray<AActor*> Actors, int32 StartNumber, int32 Padding)
{
	UOPM_NamingUtilities::AutoNumber(Actors, StartNumber, Padding);
}

void UOPMBlueprintLibrary::FindAndReplace(
	TArray<AActor*> Actors,
	const FString& FindStr,
	const FString& ReplaceStr,
	bool bCaseSensitive)
{
	UOPM_NamingUtilities::FindAndReplace(Actors, FindStr, ReplaceStr, bCaseSensitive);
}

// ==================== Replacement Functions ====================

TArray<AActor*> UOPMBlueprintLibrary::BatchReplaceActors(
	UObject* WorldContextObject,
	TArray<AActor*> OldActors,
	UClass* NewActorClass,
	bool bPreserveTransform,
	bool bPreserveAttachments)
{
	if (!WorldContextObject)
	{
		return TArray<AActor*>();
	}

	UWorld* World = WorldContextObject->GetWorld();
	return UOPM_ActorReplacementUtilities::BatchReplaceActors(
		OldActors,
		NewActorClass,
		World,
		bPreserveTransform,
		bPreserveAttachments
	);
}

// ==================== Organization Functions ====================

void UOPMBlueprintLibrary::SetActorFolder(TArray<AActor*> Actors, const FString& FolderPath)
{
	UOPM_OrganizationUtilities::SetActorFolder(Actors, FName(*FolderPath));
}

void UOPMBlueprintLibrary::GroupActorsByType(TArray<AActor*> Actors)
{
	UOPM_OrganizationUtilities::GroupActorsByType(Actors, true);
}

void UOPMBlueprintLibrary::ApplyTags(TArray<AActor*> Actors, const TArray<FName>& Tags)
{
	UOPM_OrganizationUtilities::ApplyTagsToActors(Actors, Tags, false);
}

void UOPMBlueprintLibrary::AttachActorsToParent(
	TArray<AActor*> Actors,
	AActor* ParentActor,
	bool bMaintainWorldTransform)
{
	UOPM_OrganizationUtilities::AttachActorsToParent(Actors, ParentActor, bMaintainWorldTransform);
}

void UOPMBlueprintLibrary::DetachActorsFromParent(TArray<AActor*> Actors, bool bMaintainWorldTransform)
{
	UOPM_OrganizationUtilities::DetachActorsFromParent(Actors, bMaintainWorldTransform);
}

// ==================== Utility Functions ====================

TArray<AActor*> UOPMBlueprintLibrary::GetSelectedActors()
{
	TArray<AActor*> SelectedActors;

#if WITH_EDITOR
	if (GEditor)
	{
		for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
		{
			if (AActor* Actor = Cast<AActor>(*It))
			{
				SelectedActors.Add(Actor);
			}
		}
	}
#endif

	return SelectedActors;
}

FBox UOPMBlueprintLibrary::GetActorsBounds(const TArray<AActor*>& Actors)
{
	return UOPM_AlignmentUtilities::GetActorsBounds(Actors);
}

FVector UOPMBlueprintLibrary::GetActorsCenter(const TArray<AActor*>& Actors)
{
	return UOPM_AlignmentUtilities::GetActorsCenter(Actors);
}
