// Copyright Epic Games, Inc. All Rights Reserved.

#include "OPMTransactionUtils.h"

#if WITH_EDITOR
#include "Editor.h"
#include "ScopedTransaction.h"
#endif

FOPM_TransactionScope::FOPM_TransactionScope(const FText& Description)
	: TransactionIndex(-1)
	, bTransactionStarted(false)
{
#if WITH_EDITOR
	if (GEditor)
	{
		TransactionIndex = GEditor->BeginTransaction(Description);
		bTransactionStarted = (TransactionIndex >= 0);
	}
#endif
}

FOPM_TransactionScope::~FOPM_TransactionScope()
{
#if WITH_EDITOR
	if (bTransactionStarted && GEditor)
	{
		GEditor->EndTransaction();
	}
#endif
}

void FOPM_TransactionScope::ModifyActors(const TArray<AActor*>& Actors)
{
#if WITH_EDITOR
	if (bTransactionStarted)
	{
		for (AActor* Actor : Actors)
		{
			if (Actor)
			{
				Actor->Modify();
			}
		}
	}
#endif
}

void FOPM_TransactionScope::ModifyActor(AActor* Actor)
{
#if WITH_EDITOR
	if (bTransactionStarted && Actor)
	{
		Actor->Modify();
	}
#endif
}
