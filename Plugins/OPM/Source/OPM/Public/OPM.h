// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FOPMModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

// Include public headers for easy access
#include "OPMTypes.h"
#include "PlacementUtilities.h"
#include "AlignmentUtilities.h"
#include "NamingUtilities.h"
#include "ActorReplacementUtilities.h"
#include "OrganizationUtilities.h"
#include "OPMBlueprintLibrary.h"
