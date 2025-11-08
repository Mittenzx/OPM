// Copyright Epic Games, Inc. All Rights Reserved.

#include "OrganizationUtilities.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void UOPM_OrganizationUtilities::SetActorFolder(
	TArray<AActor*> Actors,
	const FName& FolderPath)
{
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			Actor->SetFolderPath(FolderPath);
		}
	}
}

void UOPM_OrganizationUtilities::GroupActorsByType(
	TArray<AActor*> Actors,
	bool bUseClassName)
{
	// Group actors by their class
	TMap<UClass*, TArray<AActor*>> ActorsByClass;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			UClass* ActorClass = Actor->GetClass();
			ActorsByClass.FindOrAdd(ActorClass).Add(Actor);
		}
	}

	// Set folder paths based on class
	for (const auto& Pair : ActorsByClass)
	{
		UClass* ActorClass = Pair.Key;
		const TArray<AActor*>& ClassActors = Pair.Value;

		FString FolderName;
		if (bUseClassName && ActorClass)
		{
			FolderName = ActorClass->GetName();
			// Remove common prefixes like "BP_" or "A"
			if (FolderName.StartsWith(TEXT("BP_")))
			{
				FolderName = FolderName.RightChop(3);
			}
			else if (FolderName.StartsWith(TEXT("A")) && FolderName.Len() > 1)
			{
				FolderName = FolderName.RightChop(1);
			}
		}
		else
		{
			FolderName = TEXT("Group");
		}

		FName FolderPath(*FolderName);
		SetActorFolder(ClassActors, FolderPath);
	}
}

void UOPM_OrganizationUtilities::ApplyTagsToActors(
	TArray<AActor*> Actors,
	const TArray<FName>& Tags,
	bool bReplace)
{
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			if (bReplace)
			{
				Actor->Tags = Tags;
			}
			else
			{
				for (const FName& Tag : Tags)
				{
					Actor->Tags.AddUnique(Tag);
				}
			}
		}
	}
}

void UOPM_OrganizationUtilities::RemoveTagsFromActors(
	TArray<AActor*> Actors,
	const TArray<FName>& Tags)
{
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			for (const FName& Tag : Tags)
			{
				Actor->Tags.Remove(Tag);
			}
		}
	}
}

void UOPM_OrganizationUtilities::ClearActorTags(TArray<AActor*> Actors)
{
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			Actor->Tags.Empty();
		}
	}
}

void UOPM_OrganizationUtilities::AttachActorsToParent(
	TArray<AActor*> Actors,
	AActor* ParentActor,
	bool bMaintainWorldTransform)
{
	if (!ParentActor)
	{
		return;
	}

	FAttachmentTransformRules TransformRules = bMaintainWorldTransform ?
		FAttachmentTransformRules::KeepWorldTransform :
		FAttachmentTransformRules::KeepRelativeTransform;

	for (AActor* Actor : Actors)
	{
		if (Actor && Actor != ParentActor)
		{
			Actor->AttachToActor(ParentActor, TransformRules);
		}
	}
}

void UOPM_OrganizationUtilities::DetachActorsFromParent(
	TArray<AActor*> Actors,
	bool bMaintainWorldTransform)
{
	FDetachmentTransformRules TransformRules = bMaintainWorldTransform ?
		FDetachmentTransformRules::KeepWorldTransform :
		FDetachmentTransformRules::KeepRelativeTransform;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			Actor->DetachFromActor(TransformRules);
		}
	}
}

AActor* UOPM_OrganizationUtilities::CreateParentActor(
	UWorld* World,
	const FVector& Location,
	const FString& GroupName)
{
	if (!World)
	{
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(*GroupName);
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* ParentActor = World->SpawnActor<AActor>(
		AActor::StaticClass(),
		Location,
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (ParentActor)
	{
		ParentActor->SetActorLabel(GroupName);
	}

	return ParentActor;
}
