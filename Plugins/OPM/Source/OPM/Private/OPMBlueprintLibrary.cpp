// Copyright Epic Games, Inc. All Rights Reserved.

#include "OPMBlueprintLibrary.h"
#include "PlacementUtilities.h"
#include "AlignmentUtilities.h"
#include "NamingUtilities.h"
#include "ActorReplacementUtilities.h"
#include "OrganizationUtilities.h"
#include "OPMTransactionUtils.h"
#include "AIPlacementUtilities.h"
#include "LandscapeIntegrationUtilities.h"
#include "SplineUtilities.h"
#include "Engine/World.h"
#include "Editor.h"
#include "Landscape.h"
#include "Components/SplineComponent.h"

#define LOCTEXT_NAMESPACE "OPMBlueprintLibrary"

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
	FOPM_TransactionScope Transaction(LOCTEXT("AlignActors", "Align Actors"));
	Transaction.ModifyActors(Actors);
	UOPM_AlignmentUtilities::AlignActors(Actors, Type, Axis);
}

void UOPMBlueprintLibrary::AlignActorsLeft(TArray<AActor*> Actors)
{
	FOPM_TransactionScope Transaction(LOCTEXT("AlignLeft", "Align Actors Left"));
	Transaction.ModifyActors(Actors);
	UOPM_AlignmentUtilities::AlignActorsLeft(Actors);
}

void UOPMBlueprintLibrary::AlignActorsRight(TArray<AActor*> Actors)
{
	FOPM_TransactionScope Transaction(LOCTEXT("AlignRight", "Align Actors Right"));
	Transaction.ModifyActors(Actors);
	UOPM_AlignmentUtilities::AlignActorsRight(Actors);
}

void UOPMBlueprintLibrary::AlignActorsTop(TArray<AActor*> Actors)
{
	FOPM_TransactionScope Transaction(LOCTEXT("AlignTop", "Align Actors Top"));
	Transaction.ModifyActors(Actors);
	UOPM_AlignmentUtilities::AlignActorsTop(Actors);
}

void UOPMBlueprintLibrary::AlignActorsBottom(TArray<AActor*> Actors)
{
	FOPM_TransactionScope Transaction(LOCTEXT("AlignBottom", "Align Actors Bottom"));
	Transaction.ModifyActors(Actors);
	UOPM_AlignmentUtilities::AlignActorsBottom(Actors);
}

void UOPMBlueprintLibrary::CenterActorsX(TArray<AActor*> Actors)
{
	FOPM_TransactionScope Transaction(LOCTEXT("CenterX", "Center Actors X"));
	Transaction.ModifyActors(Actors);
	UOPM_AlignmentUtilities::CenterActorsX(Actors);
}

void UOPMBlueprintLibrary::CenterActorsY(TArray<AActor*> Actors)
{
	FOPM_TransactionScope Transaction(LOCTEXT("CenterY", "Center Actors Y"));
	Transaction.ModifyActors(Actors);
	UOPM_AlignmentUtilities::CenterActorsY(Actors);
}

void UOPMBlueprintLibrary::CenterActorsZ(TArray<AActor*> Actors)
{
	FOPM_TransactionScope Transaction(LOCTEXT("CenterZ", "Center Actors Z"));
	Transaction.ModifyActors(Actors);
	UOPM_AlignmentUtilities::CenterActorsZ(Actors);
}

void UOPMBlueprintLibrary::DistributeActors(
	TArray<AActor*> Actors,
	EDistributionType Type)
{
	FOPM_TransactionScope Transaction(LOCTEXT("Distribute", "Distribute Actors"));
	Transaction.ModifyActors(Actors);
	UOPM_AlignmentUtilities::DistributeActors(Actors, Type);
}

void UOPMBlueprintLibrary::SnapActorsToGrid(TArray<AActor*> Actors, float GridSize)
{
	FOPM_TransactionScope Transaction(LOCTEXT("SnapToGrid", "Snap Actors to Grid"));
	Transaction.ModifyActors(Actors);
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
	FOPM_TransactionScope Transaction(LOCTEXT("BatchRename", "Batch Rename Actors"));
	Transaction.ModifyActors(Actors);
	UOPM_NamingUtilities::BatchRename(Actors, Prefix, Suffix, StartNumber, Padding);
}

void UOPMBlueprintLibrary::AddPrefix(TArray<AActor*> Actors, const FString& Prefix)
{
	FOPM_TransactionScope Transaction(LOCTEXT("AddPrefix", "Add Prefix to Actors"));
	Transaction.ModifyActors(Actors);
	UOPM_NamingUtilities::AddPrefix(Actors, Prefix);
}

void UOPMBlueprintLibrary::AddSuffix(TArray<AActor*> Actors, const FString& Suffix)
{
	FOPM_TransactionScope Transaction(LOCTEXT("AddSuffix", "Add Suffix to Actors"));
	Transaction.ModifyActors(Actors);
	UOPM_NamingUtilities::AddSuffix(Actors, Suffix);
}

void UOPMBlueprintLibrary::AutoNumber(TArray<AActor*> Actors, int32 StartNumber, int32 Padding)
{
	FOPM_TransactionScope Transaction(LOCTEXT("AutoNumber", "Auto Number Actors"));
	Transaction.ModifyActors(Actors);
	UOPM_NamingUtilities::AutoNumber(Actors, StartNumber, Padding);
}

void UOPMBlueprintLibrary::FindAndReplace(
	TArray<AActor*> Actors,
	const FString& FindStr,
	const FString& ReplaceStr,
	bool bCaseSensitive)
{
	FOPM_TransactionScope Transaction(LOCTEXT("FindReplace", "Find and Replace in Names"));
	Transaction.ModifyActors(Actors);
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
	FOPM_TransactionScope Transaction(LOCTEXT("SetFolder", "Set Actor Folder"));
	Transaction.ModifyActors(Actors);
	UOPM_OrganizationUtilities::SetActorFolder(Actors, FName(*FolderPath));
}

void UOPMBlueprintLibrary::GroupActorsByType(TArray<AActor*> Actors)
{
	FOPM_TransactionScope Transaction(LOCTEXT("GroupByType", "Group Actors by Type"));
	Transaction.ModifyActors(Actors);
	UOPM_OrganizationUtilities::GroupActorsByType(Actors, true);
}

void UOPMBlueprintLibrary::ApplyTags(TArray<AActor*> Actors, const TArray<FName>& Tags)
{
	FOPM_TransactionScope Transaction(LOCTEXT("ApplyTags", "Apply Tags to Actors"));
	Transaction.ModifyActors(Actors);
	UOPM_OrganizationUtilities::ApplyTagsToActors(Actors, Tags, false);
}

void UOPMBlueprintLibrary::AttachActorsToParent(
	TArray<AActor*> Actors,
	AActor* ParentActor,
	bool bMaintainWorldTransform)
{
	FOPM_TransactionScope Transaction(LOCTEXT("AttachToParent", "Attach Actors to Parent"));
	Transaction.ModifyActors(Actors);
	if (ParentActor)
	{
		Transaction.ModifyActor(ParentActor);
	}
	UOPM_OrganizationUtilities::AttachActorsToParent(Actors, ParentActor, bMaintainWorldTransform);
}

void UOPMBlueprintLibrary::DetachActorsFromParent(TArray<AActor*> Actors, bool bMaintainWorldTransform)
{
	FOPM_TransactionScope Transaction(LOCTEXT("DetachFromParent", "Detach Actors from Parent"));
	Transaction.ModifyActors(Actors);
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

// ==================== AI-Assisted Placement (v2.0) ====================

EAIPatternType UOPMBlueprintLibrary::DetectPlacementPattern(const TArray<AActor*>& Actors)
{
	return UOPM_AIPlacementUtilities::DetectPlacementPattern(Actors);
}

int32 UOPMBlueprintLibrary::GenerateSmartSuggestions(
	const TArray<AActor*>& ExistingActors,
	const FAIPlacementSettings& Settings,
	TArray<FTransform>& SuggestedTransforms)
{
	return UOPM_AIPlacementUtilities::GenerateSmartSuggestions(ExistingActors, Settings, SuggestedTransforms);
}

TArray<FTransform> UOPMBlueprintLibrary::OptimizeActorPlacement(
	const TArray<AActor*>& Actors,
	const FAIPlacementSettings& Settings)
{
	return UOPM_AIPlacementUtilities::OptimizeActorPlacement(Actors, Settings);
}

TArray<FTransform> UOPMBlueprintLibrary::GenerateOrganicPattern(
	const FBox& BoundsBox,
	int32 Count,
	const FAIPlacementSettings& Settings)
{
	return UOPM_AIPlacementUtilities::GenerateOrganicPattern(BoundsBox, Count, Settings);
}

float UOPMBlueprintLibrary::EvaluatePlacementQuality(const TArray<AActor*>& Actors)
{
	return UOPM_AIPlacementUtilities::EvaluatePlacementQuality(Actors);
}

// ==================== Landscape Integration (v2.0) ====================

TArray<AActor*> UOPMBlueprintLibrary::PlaceActorsOnLandscape(
	UObject* WorldContextObject,
	UClass* ActorClass,
	const TArray<FTransform>& Transforms,
	ALandscape* Landscape,
	const FLandscapePlacementSettings& Settings)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return TArray<AActor*>();
	}

	return UOPM_LandscapeIntegrationUtilities::PlaceActorsOnLandscape(ActorClass, Transforms, Landscape, Settings, World);
}

bool UOPMBlueprintLibrary::SampleLandscapeHeight(
	ALandscape* Landscape,
	const FVector& Location,
	float& OutHeight)
{
	return UOPM_LandscapeIntegrationUtilities::SampleLandscapeHeight(Landscape, Location, OutHeight);
}

float UOPMBlueprintLibrary::CalculateSlopeAngle(
	ALandscape* Landscape,
	const FVector& Location)
{
	return UOPM_LandscapeIntegrationUtilities::CalculateSlopeAngle(Landscape, Location);
}

TArray<FTransform> UOPMBlueprintLibrary::DistributeByBiome(
	const FBox& BoundsBox,
	int32 Count,
	EBiomeType BiomeType,
	ALandscape* Landscape)
{
	return UOPM_LandscapeIntegrationUtilities::DistributeByBiome(BoundsBox, Count, BiomeType, Landscape);
}

ALandscape* UOPMBlueprintLibrary::FindLandscapeInWorld(UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return nullptr;
	}

	return UOPM_LandscapeIntegrationUtilities::FindLandscapeInWorld(World);
}

// ==================== Spline-Based Tools (v2.0) ====================

TArray<AActor*> UOPMBlueprintLibrary::PlaceActorsAlongSpline(
	UObject* WorldContextObject,
	UClass* ActorClass,
	USplineComponent* SplineComponent,
	const FSplinePlacementSettings& Settings)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return TArray<AActor*>();
	}

	return UOPM_SplineUtilities::PlaceActorsAlongSpline(ActorClass, SplineComponent, Settings, World);
}

TArray<FTransform> UOPMBlueprintLibrary::GenerateTransformsAlongSpline(
	USplineComponent* SplineComponent,
	const FSplinePlacementSettings& Settings)
{
	return UOPM_SplineUtilities::GenerateTransformsAlongSpline(SplineComponent, Settings);
}

TArray<AActor*> UOPMBlueprintLibrary::GenerateRoadAlongSpline(
	UObject* WorldContextObject,
	USplineComponent* SplineComponent,
	UClass* RoadActorClass,
	const TArray<UClass*>& PropActorClasses,
	float PropSpacing)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return TArray<AActor*>();
	}

	return UOPM_SplineUtilities::GenerateRoadAlongSpline(SplineComponent, RoadActorClass, PropActorClasses, PropSpacing, World);
}

TArray<AActor*> UOPMBlueprintLibrary::GenerateFenceAlongSpline(
	UObject* WorldContextObject,
	USplineComponent* SplineComponent,
	UClass* PostActorClass,
	UClass* PanelActorClass,
	float PostSpacing)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return TArray<AActor*>();
	}

	return UOPM_SplineUtilities::GenerateFenceAlongSpline(SplineComponent, PostActorClass, PanelActorClass, PostSpacing, World);
}

TArray<AActor*> UOPMBlueprintLibrary::GenerateCableRoutingAlongSpline(
	UObject* WorldContextObject,
	USplineComponent* SplineComponent,
	UClass* CableActorClass,
	UClass* SupportsActorClass,
	float SupportSpacing,
	float SagAmount)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return TArray<AActor*>();
	}

	return UOPM_SplineUtilities::GenerateCableRoutingAlongSpline(SplineComponent, CableActorClass, SupportsActorClass, SupportSpacing, SagAmount, World);
}

float UOPMBlueprintLibrary::GetSplineLength(USplineComponent* SplineComponent)
{
	return UOPM_SplineUtilities::GetSplineLength(SplineComponent);
}

TArray<float> UOPMBlueprintLibrary::GetAdaptiveDistances(
	USplineComponent* SplineComponent,
	float MinSpacing,
	float MaxSpacing)
{
	return UOPM_SplineUtilities::GetAdaptiveDistances(SplineComponent, MinSpacing, MaxSpacing);
}

#undef LOCTEXT_NAMESPACE
