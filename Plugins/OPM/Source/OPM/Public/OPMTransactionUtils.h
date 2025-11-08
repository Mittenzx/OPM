// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * Utility class for managing undo/redo transactions
 */
class FOPM_TransactionScope
{
public:
	/**
	 * Begin a transaction scope
	 * @param Description Description of the operation for undo/redo UI
	 */
	explicit FOPM_TransactionScope(const FText& Description);

	/**
	 * Destructor - automatically ends the transaction
	 */
	~FOPM_TransactionScope();

	/**
	 * Mark actors as modified for undo/redo
	 * @param Actors Actors to mark as modified
	 */
	void ModifyActors(const TArray<AActor*>& Actors);

	/**
	 * Mark a single actor as modified for undo/redo
	 * @param Actor Actor to mark as modified
	 */
	void ModifyActor(AActor* Actor);

private:
	int32 TransactionIndex;
	bool bTransactionStarted;
};
