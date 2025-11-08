// Copyright Epic Games, Inc. All Rights Reserved.

#include "NamingUtilities.h"

void UOPM_NamingUtilities::BatchRename(
	TArray<AActor*> Actors,
	const FString& Prefix,
	const FString& Suffix,
	int32 StartNumber,
	int32 Padding)
{
	int32 CurrentNumber = StartNumber;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FString BaseName = Actor->GetActorLabel();
			FString NewName = GenerateName(BaseName, Prefix, Suffix, CurrentNumber, Padding);
			Actor->SetActorLabel(NewName);
			CurrentNumber++;
		}
	}
}

void UOPM_NamingUtilities::AddPrefix(
	TArray<AActor*> Actors,
	const FString& Prefix)
{
	if (Prefix.IsEmpty())
	{
		return;
	}

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FString CurrentName = Actor->GetActorLabel();
			FString NewName = Prefix + CurrentName;
			Actor->SetActorLabel(NewName);
		}
	}
}

void UOPM_NamingUtilities::AddSuffix(
	TArray<AActor*> Actors,
	const FString& Suffix)
{
	if (Suffix.IsEmpty())
	{
		return;
	}

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FString CurrentName = Actor->GetActorLabel();
			FString NewName = CurrentName + Suffix;
			Actor->SetActorLabel(NewName);
		}
	}
}

void UOPM_NamingUtilities::AutoNumber(
	TArray<AActor*> Actors,
	int32 StartNumber,
	int32 Padding)
{
	int32 CurrentNumber = StartNumber;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FString CurrentName = Actor->GetActorLabel();
			FString NumberStr = FormatNumber(CurrentNumber, Padding);
			FString NewName = CurrentName + TEXT("_") + NumberStr;
			Actor->SetActorLabel(NewName);
			CurrentNumber++;
		}
	}
}

void UOPM_NamingUtilities::FindAndReplace(
	TArray<AActor*> Actors,
	const FString& FindStr,
	const FString& ReplaceStr,
	bool bCaseSensitive)
{
	if (FindStr.IsEmpty())
	{
		return;
	}

	ESearchCase::Type SearchCase = bCaseSensitive ? 
		ESearchCase::CaseSensitive : 
		ESearchCase::IgnoreCase;

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FString CurrentName = Actor->GetActorLabel();
			FString NewName = CurrentName.Replace(*FindStr, *ReplaceStr, SearchCase);
			
			if (NewName != CurrentName)
			{
				Actor->SetActorLabel(NewName);
			}
		}
	}
}

void UOPM_NamingUtilities::RemovePrefix(
	TArray<AActor*> Actors,
	const FString& Prefix)
{
	if (Prefix.IsEmpty())
	{
		return;
	}

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FString CurrentName = Actor->GetActorLabel();
			if (CurrentName.StartsWith(Prefix))
			{
				FString NewName = CurrentName.RightChop(Prefix.Len());
				Actor->SetActorLabel(NewName);
			}
		}
	}
}

void UOPM_NamingUtilities::RemoveSuffix(
	TArray<AActor*> Actors,
	const FString& Suffix)
{
	if (Suffix.IsEmpty())
	{
		return;
	}

	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			FString CurrentName = Actor->GetActorLabel();
			if (CurrentName.EndsWith(Suffix))
			{
				FString NewName = CurrentName.LeftChop(Suffix.Len());
				Actor->SetActorLabel(NewName);
			}
		}
	}
}

FString UOPM_NamingUtilities::FormatNumber(int32 Number, int32 Padding)
{
	if (Padding <= 0)
	{
		return FString::FromInt(Number);
	}

	FString NumberStr = FString::FromInt(Number);
	
	// Add leading zeros
	while (NumberStr.Len() < Padding)
	{
		NumberStr = TEXT("0") + NumberStr;
	}

	return NumberStr;
}

FString UOPM_NamingUtilities::GenerateName(
	const FString& BaseName,
	const FString& Prefix,
	const FString& Suffix,
	int32 Number,
	int32 Padding)
{
	FString NewName = BaseName;

	// Add prefix
	if (!Prefix.IsEmpty())
	{
		NewName = Prefix + NewName;
	}

	// Add suffix
	if (!Suffix.IsEmpty())
	{
		NewName = NewName + Suffix;
	}

	// Add number
	if (Number >= 0)
	{
		FString NumberStr = FormatNumber(Number, Padding);
		NewName = NewName + TEXT("_") + NumberStr;
	}

	return NewName;
}
