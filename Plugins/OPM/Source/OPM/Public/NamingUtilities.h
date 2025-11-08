// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * Utility class for batch naming operations on actors
 */
class UOPM_NamingUtilities
{
public:
	/**
	 * Batch rename actors with prefix, suffix, and auto-numbering
	 * @param Actors Array of actors to rename
	 * @param Prefix Prefix to add before actor name
	 * @param Suffix Suffix to add after actor name
	 * @param StartNumber Starting number for auto-numbering
	 * @param Padding Number of digits for padding (e.g., 3 = 001, 002)
	 */
	static void BatchRename(
		TArray<AActor*> Actors,
		const FString& Prefix,
		const FString& Suffix,
		int32 StartNumber,
		int32 Padding);

	/**
	 * Add prefix to actor names
	 * @param Actors Array of actors to rename
	 * @param Prefix Prefix to add
	 */
	static void AddPrefix(
		TArray<AActor*> Actors,
		const FString& Prefix);

	/**
	 * Add suffix to actor names
	 * @param Actors Array of actors to rename
	 * @param Suffix Suffix to add
	 */
	static void AddSuffix(
		TArray<AActor*> Actors,
		const FString& Suffix);

	/**
	 * Auto-number actors sequentially
	 * @param Actors Array of actors to number
	 * @param StartNumber Starting number
	 * @param Padding Number of digits for padding
	 */
	static void AutoNumber(
		TArray<AActor*> Actors,
		int32 StartNumber,
		int32 Padding);

	/**
	 * Find and replace text in actor names
	 * @param Actors Array of actors to process
	 * @param FindStr Text to find
	 * @param ReplaceStr Text to replace with
	 * @param bCaseSensitive Whether search is case sensitive
	 */
	static void FindAndReplace(
		TArray<AActor*> Actors,
		const FString& FindStr,
		const FString& ReplaceStr,
		bool bCaseSensitive);

	/**
	 * Remove prefix from actor names
	 * @param Actors Array of actors to process
	 * @param Prefix Prefix to remove
	 */
	static void RemovePrefix(
		TArray<AActor*> Actors,
		const FString& Prefix);

	/**
	 * Remove suffix from actor names
	 * @param Actors Array of actors to process
	 * @param Suffix Suffix to remove
	 */
	static void RemoveSuffix(
		TArray<AActor*> Actors,
		const FString& Suffix);

	/**
	 * Format number with padding
	 * @param Number Number to format
	 * @param Padding Number of digits for padding
	 * @return Formatted string
	 */
	static FString FormatNumber(int32 Number, int32 Padding);

	/**
	 * Generate name with pattern
	 * @param BaseName Base name
	 * @param Prefix Prefix
	 * @param Suffix Suffix
	 * @param Number Number for auto-numbering
	 * @param Padding Number padding
	 * @return Generated name
	 */
	static FString GenerateName(
		const FString& BaseName,
		const FString& Prefix,
		const FString& Suffix,
		int32 Number,
		int32 Padding);
};
