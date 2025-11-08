// Copyright Epic Games, Inc. All Rights Reserved.

#include "ActorReplacementUtilities.h"
#include "Engine/World.h"

AActor* UOPM_ActorReplacementUtilities::ReplaceActor(
	AActor* OldActor,
	UClass* NewActorClass,
	UWorld* World,
	bool bPreserveTransform,
	bool bPreserveAttachments)
{
	if (!OldActor || !NewActorClass || !World)
	{
		return nullptr;
	}

	// Store transform and other properties
	FTransform Transform = OldActor->GetActorTransform();
	TArray<FName> Tags = OldActor->Tags;
	AActor* ParentActor = OldActor->GetAttachParentActor();
	TArray<AActor*> AttachedActors;
	OldActor->GetAttachedActors(AttachedActors);

	// Spawn new actor
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* NewActor = World->SpawnActor<AActor>(
		NewActorClass,
		Transform.GetLocation(),
		Transform.Rotator(),
		SpawnParams
	);

	if (!NewActor)
	{
		return nullptr;
	}

	// Apply transform
	if (bPreserveTransform)
	{
		NewActor->SetActorScale3D(Transform.GetScale3D());
	}

	// Copy tags
	NewActor->Tags = Tags;

	// Preserve attachments
	if (bPreserveAttachments)
	{
		// Attach to parent if it existed
		if (ParentActor)
		{
			NewActor->AttachToActor(ParentActor, FAttachmentTransformRules::KeepWorldTransform);
		}

		// Reattach children
		for (AActor* AttachedActor : AttachedActors)
		{
			if (AttachedActor)
			{
				AttachedActor->AttachToActor(NewActor, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}

	// Copy actor label
	NewActor->SetActorLabel(OldActor->GetActorLabel());

	// Destroy old actor
	OldActor->Destroy();

	return NewActor;
}

TArray<AActor*> UOPM_ActorReplacementUtilities::BatchReplaceActors(
	TArray<AActor*> OldActors,
	UClass* NewActorClass,
	UWorld* World,
	bool bPreserveTransform,
	bool bPreserveAttachments)
{
	TArray<AActor*> NewActors;

	if (!NewActorClass || !World)
	{
		return NewActors;
	}

	NewActors.Reserve(OldActors.Num());

	for (AActor* OldActor : OldActors)
	{
		AActor* NewActor = ReplaceActor(
			OldActor,
			NewActorClass,
			World,
			bPreserveTransform,
			bPreserveAttachments
		);

		if (NewActor)
		{
			NewActors.Add(NewActor);
		}
	}

	return NewActors;
}

void UOPM_ActorReplacementUtilities::CopyTransform(AActor* SourceActor, AActor* TargetActor)
{
	if (!SourceActor || !TargetActor)
	{
		return;
	}

	TargetActor->SetActorTransform(SourceActor->GetActorTransform());
}

void UOPM_ActorReplacementUtilities::CopyTags(AActor* SourceActor, AActor* TargetActor)
{
	if (!SourceActor || !TargetActor)
	{
		return;
	}

	TargetActor->Tags = SourceActor->Tags;
}

void UOPM_ActorReplacementUtilities::CopyAttachments(AActor* SourceActor, AActor* TargetActor)
{
	if (!SourceActor || !TargetActor)
	{
		return;
	}

	// Copy parent attachment
	AActor* ParentActor = SourceActor->GetAttachParentActor();
	if (ParentActor)
	{
		TargetActor->AttachToActor(ParentActor, FAttachmentTransformRules::KeepWorldTransform);
	}

	// Copy child attachments
	TArray<AActor*> AttachedActors;
	SourceActor->GetAttachedActors(AttachedActors);
	
	for (AActor* AttachedActor : AttachedActors)
	{
		if (AttachedActor)
		{
			AttachedActor->AttachToActor(TargetActor, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}
