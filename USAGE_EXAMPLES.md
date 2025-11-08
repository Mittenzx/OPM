# OPM Usage Examples

This document provides code examples for using the Object Placement Manager utilities.

## Table of Contents
- [C++ Usage](#c-usage)
- [Blueprint Usage](#blueprint-usage)
- [Common Workflows](#common-workflows)

---

## C++ Usage

### Basic Pattern Generation

```cpp
#include "OPM.h"

// Generate a grid of transforms
FGridPatternSettings GridSettings;
GridSettings.Rows = 5;
GridSettings.Columns = 5;
GridSettings.Spacing = FVector(100.0f, 100.0f, 0.0f);

FTransform Origin = FTransform::Identity;
TArray<FTransform> Transforms = UOPM_PlacementUtilities::GenerateGridPattern(GridSettings, Origin);

// Spawn actors at those transforms
UWorld* World = GetWorld();
UClass* ActorClass = AStaticMeshActor::StaticClass();
TArray<AActor*> SpawnedActors = UOPM_PlacementUtilities::PlaceActorsInPattern(ActorClass, Transforms, World);
```

### Circular Pattern

```cpp
FCircularPatternSettings CircleSettings;
CircleSettings.Radius = 500.0f;
CircleSettings.Count = 8;
CircleSettings.StartAngle = 0.0f;

FTransform Center = FTransform(FVector(0, 0, 100));
TArray<FTransform> Transforms = UOPM_PlacementUtilities::GenerateCircularPattern(CircleSettings, Center);
```

### Align Selected Actors

```cpp
// Get selected actors (editor only)
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

// Align them to the left
UOPM_AlignmentUtilities::AlignActorsLeft(SelectedActors);

// Or center them on X axis
UOPM_AlignmentUtilities::CenterActorsX(SelectedActors);

// Distribute evenly
UOPM_AlignmentUtilities::DistributeActorsHorizontally(SelectedActors);
```

### Batch Rename

```cpp
TArray<AActor*> Actors; // Your actors array

// Add prefix and number
UOPM_NamingUtilities::BatchRename(
    Actors,
    TEXT("SM_"),      // Prefix
    TEXT("_Prop"),    // Suffix
    1,                // Start number
    3                 // Padding (001, 002, 003)
);

// Result: SM_ActorName_Prop_001, SM_ActorName_Prop_002, etc.

// Find and replace
UOPM_NamingUtilities::FindAndReplace(
    Actors,
    TEXT("Old"),
    TEXT("New"),
    false  // Case insensitive
);
```

### Replace Actors

```cpp
TArray<AActor*> OldActors; // Actors to replace
UClass* NewClass = AStaticMeshActor::StaticClass();
UWorld* World = GetWorld();

TArray<AActor*> NewActors = UOPM_ActorReplacementUtilities::BatchReplaceActors(
    OldActors,
    NewClass,
    World,
    true,  // Preserve transform
    true   // Preserve attachments
);
```

### Organize Actors

```cpp
TArray<AActor*> Actors;

// Set folder
UOPM_OrganizationUtilities::SetActorFolder(Actors, FName(TEXT("Environment/Props")));

// Group by type
UOPM_OrganizationUtilities::GroupActorsByType(Actors, true);

// Apply tags
TArray<FName> Tags = { FName(TEXT("Decorative")), FName(TEXT("Interactive")) };
UOPM_OrganizationUtilities::ApplyTagsToActors(Actors, Tags, false);

// Create parent and attach actors
FVector GroupLocation = FVector::ZeroVector;
AActor* ParentActor = UOPM_OrganizationUtilities::CreateParentActor(
    World,
    GroupLocation,
    TEXT("PropGroup")
);
UOPM_OrganizationUtilities::AttachActorsToParent(Actors, ParentActor, true);
```

---

## Blueprint Usage

All functionality is available in Blueprints through the `OPM` category.

### Placement in Blueprint

```
1. Create an Editor Utility Blueprint or Widget
2. Add "Generate Grid Pattern" node
3. Configure settings (rows, columns, spacing)
4. Connect to "Place Actors in Pattern" node
5. Specify actor class to spawn
```

**Node Categories:**
- `OPM|Placement` - Pattern generation and placement
- `OPM|Alignment` - Alignment and distribution
- `OPM|Naming` - Batch naming operations
- `OPM|Replacement` - Actor replacement
- `OPM|Organization` - Folder and tag management
- `OPM|Utility` - Helper functions

### Common Blueprint Nodes

**Get Selected Actors:**
```
Get Selected Actors -> Returns array of selected actors in editor
```

**Align Left:**
```
Get Selected Actors -> Align Actors Left
```

**Batch Rename:**
```
Get Selected Actors -> Batch Rename
    Prefix: "SM_"
    Suffix: "_Prop"
    Start Number: 1
    Padding: 3
```

**Snap to Grid:**
```
Get Selected Actors -> Snap Actors to Grid
    Grid Size: 100.0
```

---

## Common Workflows

### Workflow 1: Place Props in Grid

```cpp
// 1. Define grid settings
FGridPatternSettings Settings;
Settings.Rows = 10;
Settings.Columns = 10;
Settings.Spacing = FVector(200.0f, 200.0f, 0.0f);

// 2. Generate transforms
FTransform Origin(FVector(0, 0, 0));
TArray<FTransform> Transforms = UOPM_PlacementUtilities::GenerateGridPattern(Settings, Origin);

// 3. Spawn actors
TArray<AActor*> Actors = UOPM_PlacementUtilities::PlaceActorsInPattern(
    PropClass,
    Transforms,
    World
);

// 4. Name them
UOPM_NamingUtilities::BatchRename(Actors, TEXT("Prop_"), TEXT(""), 1, 3);

// 5. Organize
UOPM_OrganizationUtilities::SetActorFolder(Actors, FName(TEXT("Environment/Props")));
```

### Workflow 2: Organize Existing Level

```cpp
// 1. Get all actors of a type
TArray<AActor*> StaticMeshActors;
UGameplayStatics::GetAllActorsOfClass(World, AStaticMeshActor::StaticClass(), StaticMeshActors);

// 2. Group by type
UOPM_OrganizationUtilities::GroupActorsByType(StaticMeshActors, true);

// 3. Apply naming convention
UOPM_NamingUtilities::BatchRename(StaticMeshActors, TEXT("SM_"), TEXT(""), 1, 3);

// 4. Add tags
TArray<FName> Tags = { FName(TEXT("Static")) };
UOPM_OrganizationUtilities::ApplyTagsToActors(StaticMeshActors, Tags, false);
```

### Workflow 3: Create Circular Array

```cpp
// 1. Define circular pattern
FCircularPatternSettings Settings;
Settings.Radius = 1000.0f;
Settings.Count = 12;
Settings.StartAngle = 0.0f;
Settings.Height = 100.0f;

// 2. Generate and place
FTransform Center(FVector(0, 0, 0));
TArray<FTransform> Transforms = UOPM_PlacementUtilities::GenerateCircularPattern(Settings, Center);
TArray<AActor*> Actors = UOPM_PlacementUtilities::PlaceActorsInPattern(LampClass, Transforms, World);

// 3. Create parent for easy manipulation
AActor* Parent = UOPM_OrganizationUtilities::CreateParentActor(World, FVector::ZeroVector, TEXT("LampArray"));
UOPM_OrganizationUtilities::AttachActorsToParent(Actors, Parent, true);
```

### Workflow 4: Replace and Align

```cpp
// 1. Get actors to replace
TArray<AActor*> OldActors = GetActorsToReplace();

// 2. Replace with new class
TArray<AActor*> NewActors = UOPM_ActorReplacementUtilities::BatchReplaceActors(
    OldActors,
    NewActorClass,
    World,
    true,  // Keep transform
    false  // Don't need to preserve attachments
);

// 3. Align the new actors
UOPM_AlignmentUtilities::AlignActorsBottom(NewActors);

// 4. Distribute evenly
UOPM_AlignmentUtilities::DistributeActorsHorizontally(NewActors);
```

### Workflow 5: Cleanup and Organize

```cpp
// 1. Get messy actors
TArray<AActor*> Actors = GetUnorganizedActors();

// 2. Snap to grid for clean alignment
UOPM_AlignmentUtilities::SnapActorsToGrid(Actors, 100.0f);

// 3. Apply naming convention
UOPM_NamingUtilities::FindAndReplace(Actors, TEXT("_old"), TEXT(""), false);
UOPM_NamingUtilities::AutoNumber(Actors, 1, 3);

// 4. Organize into folders
UOPM_OrganizationUtilities::GroupActorsByType(Actors, true);

// 5. Add organizational tags
TArray<FName> Tags = { FName(TEXT("Organized")), FName(TEXT("Level01")) };
UOPM_OrganizationUtilities::ApplyTagsToActors(Actors, Tags, false);
```

---

## Editor Utility Widget Example

You can create an Editor Utility Widget that uses these functions:

### Widget Blueprint Example

**Variables:**
- `Rows` (Integer) - Number of rows
- `Columns` (Integer) - Number of columns
- `SpacingX` (Float) - Spacing in X
- `SpacingY` (Float) - Spacing in Y
- `ActorClass` (Class Reference) - Actor class to spawn

**Button OnClicked Event:**
```
1. Make Grid Pattern Settings
    Rows: Rows
    Columns: Columns
    Spacing: Make Vector(SpacingX, SpacingY, 0)

2. Generate Grid Pattern
    Settings: (from above)
    Origin: Make Transform

3. Place Actors in Pattern
    World Context: Self
    Actor Class: ActorClass
    Transforms: (from step 2)

4. Batch Rename
    Actors: (from step 3)
    Prefix: "Prop_"
    Suffix: ""
    Start Number: 1
    Padding: 3
```

---

## Performance Tips

1. **Batch Operations**: Always operate on arrays rather than individual actors
2. **Transaction Overhead**: Transactions are automatically handled in Blueprint Library functions
3. **Preview Before Placing**: Generate transforms first, validate them, then place actors
4. **Large Arrays**: For 1000+ actors, consider processing in chunks
5. **Undo History**: Very large operations may create large undo buffers

---

## Best Practices

1. **Always Use Transactions**: When using C++ directly, wrap operations in `FOPM_TransactionScope`
2. **Validate Input**: Check for null actors and valid parameters
3. **Preview Mode**: Generate transforms first to preview before committing
4. **Naming Conventions**: Establish project naming standards early
5. **Folder Structure**: Use hierarchical folder paths for organization
6. **Tags**: Use tags for quick filtering and selection

---

## Troubleshooting

**Q: Actors are spawning at wrong locations**
A: Ensure your Origin transform is correct and check coordinate system

**Q: Alignment not working**
A: Verify actors have valid bounds. Some actors may need collision enabled

**Q: Undo not working**
A: Make sure you're using Blueprint Library functions or wrapping C++ calls in transactions

**Q: Performance issues with large arrays**
A: Consider processing in batches or using async operations (future feature)

---

For more information, see:
- [Plugin README](Plugins/OPM/README.md)
- [Implementation Guide](IMPLEMENTATION.md)
- [FAQ](FAQ.md)
