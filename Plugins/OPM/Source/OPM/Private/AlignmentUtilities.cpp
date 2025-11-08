// Copyright Epic Games, Inc. All Rights Reserved.

#include "AlignmentUtilities.h"
#include "Components/PrimitiveComponent.h"

#define LOCTEXT_NAMESPACE "OPMAlignmentUtilities"

void UOPM_AlignmentUtilities::AlignActors(
	TArray<AActor*> Actors,
	EAlignmentType Type,
	EAlignmentAxis Axis)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	switch (Type)
	{
	case EAlignmentType::Left:
		AlignActorsLeft(Actors);
		break;
	case EAlignmentType::Right:
		AlignActorsRight(Actors);
		break;
	case EAlignmentType::Top:
		AlignActorsTop(Actors);
		break;
	case EAlignmentType::Bottom:
		AlignActorsBottom(Actors);
		break;
	case EAlignmentType::Front:
		AlignActorsFront(Actors);
		break;
	case EAlignmentType::Back:
		AlignActorsBack(Actors);
		break;
	case EAlignmentType::CenterX:
		CenterActorsX(Actors);
		break;
	case EAlignmentType::CenterY:
		CenterActorsY(Actors);
		break;
	case EAlignmentType::CenterZ:
		CenterActorsZ(Actors);
		break;
	}
}

void UOPM_AlignmentUtilities::AlignActorsLeft(TArray<AActor*> Actors)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	FBox Bounds = GetActorsBounds(Actors);
	float AlignValue = Bounds.Min.X;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Location = Actor->GetActorLocation();
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			float Offset = Location.X - ActorBounds.Min.X;
			Location.X = AlignValue + Offset;
			Actor->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::AlignActorsRight(TArray<AActor*> Actors)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	FBox Bounds = GetActorsBounds(Actors);
	float AlignValue = Bounds.Max.X;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Location = Actor->GetActorLocation();
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			float Offset = Location.X - ActorBounds.Max.X;
			Location.X = AlignValue + Offset;
			Actor->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::AlignActorsTop(TArray<AActor*> Actors)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	FBox Bounds = GetActorsBounds(Actors);
	float AlignValue = Bounds.Max.Z;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Location = Actor->GetActorLocation();
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			float Offset = Location.Z - ActorBounds.Max.Z;
			Location.Z = AlignValue + Offset;
			Actor->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::AlignActorsBottom(TArray<AActor*> Actors)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	FBox Bounds = GetActorsBounds(Actors);
	float AlignValue = Bounds.Min.Z;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Location = Actor->GetActorLocation();
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			float Offset = Location.Z - ActorBounds.Min.Z;
			Location.Z = AlignValue + Offset;
			Actor->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::AlignActorsFront(TArray<AActor*> Actors)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	FBox Bounds = GetActorsBounds(Actors);
	float AlignValue = Bounds.Min.Y;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Location = Actor->GetActorLocation();
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			float Offset = Location.Y - ActorBounds.Min.Y;
			Location.Y = AlignValue + Offset;
			Actor->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::AlignActorsBack(TArray<AActor*> Actors)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	FBox Bounds = GetActorsBounds(Actors);
	float AlignValue = Bounds.Max.Y;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Location = Actor->GetActorLocation();
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			float Offset = Location.Y - ActorBounds.Max.Y;
			Location.Y = AlignValue + Offset;
			Actor->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::CenterActorsX(TArray<AActor*> Actors)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	FBox Bounds = GetActorsBounds(Actors);
	float Center = (Bounds.Min.X + Bounds.Max.X) * 0.5f;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Location = Actor->GetActorLocation();
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			float ActorCenter = (ActorBounds.Min.X + ActorBounds.Max.X) * 0.5f;
			float Offset = Location.X - ActorCenter;
			Location.X = Center + Offset;
			Actor->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::CenterActorsY(TArray<AActor*> Actors)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	FBox Bounds = GetActorsBounds(Actors);
	float Center = (Bounds.Min.Y + Bounds.Max.Y) * 0.5f;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Location = Actor->GetActorLocation();
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			float ActorCenter = (ActorBounds.Min.Y + ActorBounds.Max.Y) * 0.5f;
			float Offset = Location.Y - ActorCenter;
			Location.Y = Center + Offset;
			Actor->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::CenterActorsZ(TArray<AActor*> Actors)
{
	if (Actors.Num() < 2)
	{
		return;
	}

	FBox Bounds = GetActorsBounds(Actors);
	float Center = (Bounds.Min.Z + Bounds.Max.Z) * 0.5f;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FVector Location = Actor->GetActorLocation();
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			float ActorCenter = (ActorBounds.Min.Z + ActorBounds.Max.Z) * 0.5f;
			float Offset = Location.Z - ActorCenter;
			Location.Z = Center + Offset;
			Actor->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::DistributeActors(
	TArray<AActor*> Actors,
	EDistributionType Type)
{
	if (Actors.Num() < 3)
	{
		return;
	}

	switch (Type)
	{
	case EDistributionType::Horizontal:
		DistributeActorsHorizontally(Actors);
		break;
	case EDistributionType::Vertical:
		DistributeActorsVertically(Actors);
		break;
	case EDistributionType::Radial:
		// Radial distribution not yet implemented
		break;
	}
}

void UOPM_AlignmentUtilities::DistributeActorsHorizontally(TArray<AActor*> Actors)
{
	if (Actors.Num() < 3)
	{
		return;
	}

	// Sort actors by X position
	Actors.Sort([](const AActor& A, const AActor& B) {
		return A.GetActorLocation().X < B.GetActorLocation().X;
	});

	FBox Bounds = GetActorsBounds(Actors);
	float TotalDistance = Bounds.Max.X - Bounds.Min.X;
	float Spacing = TotalDistance / (Actors.Num() - 1);

	// Keep first and last actors in place, distribute the rest
	for (int32 i = 1; i < Actors.Num() - 1; ++i)
	{
		if (Actors[i])
		{
			FVector Location = Actors[i]->GetActorLocation();
			Location.X = Bounds.Min.X + Spacing * i;
			Actors[i]->SetActorLocation(Location);
		}
	}
}

void UOPM_AlignmentUtilities::DistributeActorsVertically(TArray<AActor*> Actors)
{
	if (Actors.Num() < 3)
	{
		return;
	}

	// Sort actors by Z position
	Actors.Sort([](const AActor& A, const AActor& B) {
		return A.GetActorLocation().Z < B.GetActorLocation().Z;
	});

	FBox Bounds = GetActorsBounds(Actors);
	float TotalDistance = Bounds.Max.Z - Bounds.Min.Z;
	float Spacing = TotalDistance / (Actors.Num() - 1);

	// Keep first and last actors in place, distribute the rest
	for (int32 i = 1; i < Actors.Num() - 1; ++i)
	{
		if (Actors[i])
		{
			FVector Location = Actors[i]->GetActorLocation();
			Location.Z = Bounds.Min.Z + Spacing * i;
			Actors[i]->SetActorLocation(Location);
		}
	}
}

FBox UOPM_AlignmentUtilities::GetActorsBounds(const TArray<AActor*>& Actors)
{
	FBox Bounds(ForceInit);

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
			Bounds += ActorBounds;
		}
	}

	return Bounds;
}

FVector UOPM_AlignmentUtilities::GetActorsCenter(const TArray<AActor*>& Actors)
{
	FBox Bounds = GetActorsBounds(Actors);
	return Bounds.GetCenter();
}

void UOPM_AlignmentUtilities::SnapActorToGrid(AActor* Actor, float GridSize)
{
	if (!Actor || GridSize <= 0.0f)
	{
		return;
	}

	FVector Location = Actor->GetActorLocation();
	Location.X = FMath::GridSnap(Location.X, GridSize);
	Location.Y = FMath::GridSnap(Location.Y, GridSize);
	Location.Z = FMath::GridSnap(Location.Z, GridSize);
	Actor->SetActorLocation(Location);
}

void UOPM_AlignmentUtilities::SnapActorsToGrid(TArray<AActor*> Actors, float GridSize)
{
	for (AActor* Actor : Actors)
	{
		SnapActorToGrid(Actor, GridSize);
	}
}

#undef LOCTEXT_NAMESPACE
