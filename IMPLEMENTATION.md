# Implementation Guide - Object Placement Manager

This document outlines the technical implementation details for OPM's core features.

## Architecture Overview

### Plugin Structure
```
OPM/
├── Source/OPM/           # C++ Module
│   ├── Public/           # Public Headers
│   │   ├── OPM.h
│   │   ├── OPMBlueprintLibrary.h
│   │   └── OPMTypes.h
│   └── Private/          # Implementation
│       ├── OPM.cpp
│       ├── OPMBlueprintLibrary.cpp
│       └── Utilities/
│           ├── PlacementUtilities.cpp
│           ├── AlignmentUtilities.cpp
│           └── NamingUtilities.cpp
└── Content/              # Blueprint Assets
    ├── UI/               # Editor Utility Widgets
    │   ├── EUW_OPM_Main.uasset
    │   ├── EUW_BatchPlacement.uasset
    │   ├── EUW_Alignment.uasset
    │   └── EUW_Naming.uasset
    └── Utilities/        # Blueprint Utilities
        └── BP_OPMUtilities.uasset
```

## Core Components

### 1. Batch Placement System

**Purpose:** Place multiple objects in various patterns

**Implementation:**
- C++ utility functions for pattern generation
- Blueprint-callable functions for editor scripting
- Preview system using temporary actors

**Patterns:**
1. **Grid Pattern**
   - Parameters: rows, columns, spacing X/Y/Z
   - Algorithm: Nested loops with offset calculations
   
2. **Circular Pattern**
   - Parameters: radius, count, start angle, height
   - Algorithm: Trigonometric positioning
   
3. **Line Pattern**
   - Parameters: start point, end point, count
   - Algorithm: Linear interpolation
   
4. **Random Scatter**
   - Parameters: bounds box, count, seed
   - Algorithm: Random position generation within bounds

**Key Functions:**
```cpp
// PlacementUtilities.h
class UOPM_PlacementUtilities
{
public:
    static TArray<FTransform> GenerateGridPattern(
        int32 Rows, int32 Columns, 
        FVector Spacing, FTransform Origin);
    
    static TArray<FTransform> GenerateCircularPattern(
        float Radius, int32 Count, 
        float StartAngle, FTransform Center);
    
    static void PlaceActorsInPattern(
        UClass* ActorClass,
        const TArray<FTransform>& Transforms,
        UWorld* World);
};
```

### 2. Alignment & Distribution System

**Purpose:** Align and distribute selected actors

**Implementation:**
- Get selected actors from editor
- Calculate bounds and positions
- Apply transformations with undo support

**Alignment Types:**
1. **Single-axis Alignment**
   - Left, Right, Center (X-axis)
   - Front, Back, Center (Y-axis)
   - Bottom, Top, Center (Z-axis)

2. **Distribution**
   - Even spacing between actors
   - Horizontal, vertical, or circular
   - Maintain relative positions

3. **Advanced Alignment**
   - Align to first selected
   - Align to average position
   - Snap to grid

**Key Functions:**
```cpp
// AlignmentUtilities.h
class UOPM_AlignmentUtilities
{
public:
    static void AlignActors(
        TArray<AActor*> Actors,
        EAlignmentType Type,
        EAlignmentAxis Axis);
    
    static void DistributeActors(
        TArray<AActor*> Actors,
        EDistributionType Type);
    
    static FVector GetActorsBounds(
        const TArray<AActor*>& Actors);
};
```

### 3. Naming Utilities

**Purpose:** Batch rename actors with conventions

**Implementation:**
- String manipulation utilities
- Pattern-based naming system
- Undo/redo support for naming

**Features:**
1. **Prefix/Suffix**
   - Add to existing names
   - Replace existing prefixes

2. **Auto-numbering**
   - Sequential: 001, 002, 003
   - Custom formats: {Name}_{Type}_{Number}
   - Padding options

3. **Find & Replace**
   - Case sensitive/insensitive
   - Regex support (optional)

4. **Name Templates**
   - Save/load naming patterns
   - Apply to selections

**Key Functions:**
```cpp
// NamingUtilities.h
class UOPM_NamingUtilities
{
public:
    static void BatchRename(
        TArray<AActor*> Actors,
        FString Prefix,
        FString Suffix,
        int32 StartNumber,
        int32 Padding);
    
    static void FindAndReplace(
        TArray<AActor*> Actors,
        FString FindStr,
        FString ReplaceStr,
        bool bCaseSensitive);
};
```

### 4. Actor Replacement System

**Purpose:** Replace actors while preserving transforms

**Implementation:**
- Spawn new actors at existing positions
- Copy transform data
- Maintain hierarchy relationships
- Delete old actors

**Features:**
1. **Simple Replacement**
   - One-to-one replacement
   - Preserve location/rotation/scale

2. **Advanced Options**
   - Preserve attachments
   - Copy component properties
   - Maintain tags and metadata

**Key Functions:**
```cpp
// ActorReplacementUtilities.h
class UOPM_ActorReplacementUtilities
{
public:
    static AActor* ReplaceActor(
        AActor* OldActor,
        UClass* NewActorClass,
        bool bPreserveAttachments,
        bool bPreserveProperties);
    
    static void BatchReplaceActors(
        TArray<AActor*> OldActors,
        UClass* NewActorClass,
        bool bPreserveAttachments);
};
```

### 5. Organization Tools

**Purpose:** Organize level hierarchy and grouping

**Implementation:**
- Folder creation in World Outliner
- Actor grouping utilities
- Tag-based organization

**Features:**
1. **Auto-grouping**
   - Group by actor type
   - Group by location (spatial)
   - Group by naming pattern

2. **Hierarchy Management**
   - Create parent actors
   - Attach actors to parents
   - Clean up empty folders

3. **Tag System**
   - Apply tags to selections
   - Find actors by tag
   - Organize by tags

**Key Functions:**
```cpp
// OrganizationUtilities.h
class UOPM_OrganizationUtilities
{
public:
    static void CreateActorFolder(
        FName FolderName,
        TArray<AActor*> Actors);
    
    static void GroupActorsByType(
        TArray<AActor*> Actors);
    
    static void ApplyTagsToActors(
        TArray<AActor*> Actors,
        TArray<FName> Tags);
};
```

## UI Implementation

### Editor Utility Widgets

**Main Panel (EUW_OPM_Main.uasset):**
- Tabbed interface
- Quick access buttons
- Settings panel
- Help/documentation links

**Placement Panel:**
- Pattern selection dropdown
- Parameter inputs (rows, columns, spacing, etc.)
- Preview checkbox
- Place button
- Reset button

**Alignment Panel:**
- Visual alignment buttons (grid layout)
- Distribution options
- Advanced options expander

**Naming Panel:**
- Text input fields
- Number format options
- Preview list
- Apply/Cancel buttons

**Widget Blueprint Structure:**
```
Main Widget
├── Tab Container
│   ├── Placement Tab
│   │   ├── Pattern Selector
│   │   ├── Grid Settings
│   │   ├── Circle Settings
│   │   └── Action Buttons
│   ├── Alignment Tab
│   │   ├── Alignment Buttons Grid
│   │   └── Distribution Options
│   ├── Naming Tab
│   │   ├── Prefix/Suffix Inputs
│   │   ├── Number Format
│   │   └── Preview List
│   └── Settings Tab
│       ├── Preferences
│       └── Shortcuts
└── Status Bar
```

## Blueprint Integration

### Blueprint Library

**OPMBlueprintLibrary** exposes all functionality to Blueprints:

```cpp
UCLASS()
class UOPMBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Placement
    UFUNCTION(BlueprintCallable, Category = "OPM|Placement")
    static void PlaceActorsInGrid(
        UClass* ActorClass,
        int32 Rows, int32 Columns,
        FVector Spacing);
    
    // Alignment
    UFUNCTION(BlueprintCallable, Category = "OPM|Alignment")
    static void AlignSelectedActors(
        EAlignmentType Type);
    
    // Naming
    UFUNCTION(BlueprintCallable, Category = "OPM|Naming")
    static void RenameSelectedActors(
        FString Prefix,
        FString Suffix,
        int32 StartNumber);
    
    // Replacement
    UFUNCTION(BlueprintCallable, Category = "OPM|Replacement")
    static void ReplaceSelectedActors(
        UClass* NewActorClass,
        bool bPreserveTransform);
};
```

## Undo/Redo System

All operations support undo/redo using Unreal's transaction system:

```cpp
void ExecuteOperation()
{
    // Begin transaction
    FScopedTransaction Transaction(
        LOCTEXT("OPM_Operation", "OPM: Operation Name"));
    
    // Modify actors
    for (AActor* Actor : Actors)
    {
        Actor->Modify();
        // Make changes...
    }
    
    // Transaction ends automatically on scope exit
}
```

## Performance Considerations

### Optimization Strategies:

1. **Batch Operations**
   - Process multiple actors in single transaction
   - Minimize individual actor modifications

2. **Preview System**
   - Use lightweight temporary actors for preview
   - Clean up preview actors immediately

3. **Caching**
   - Cache calculated transforms
   - Reuse computation results

4. **Threading** (Future)
   - Calculate patterns on background thread
   - Apply results on game thread

## Testing Strategy

### Unit Tests
- Pattern generation algorithms
- Alignment calculations
- Naming utilities
- Transform preservation

### Integration Tests
- Full workflow scenarios
- Undo/redo verification
- Multi-selection operations
- Edge cases

### Manual Testing
- UI responsiveness
- Visual verification
- Performance profiling
- Cross-platform testing

## Development Phases

### Phase 1: Core Module (Week 1-2)
- [x] Plugin structure setup
- [ ] C++ utility classes
- [ ] Blueprint library implementation
- [ ] Basic pattern generation

### Phase 2: UI Development (Week 3-4)
- [ ] Main Editor Utility Widget
- [ ] Individual tool panels
- [ ] Visual design and polish
- [ ] Keyboard shortcuts

### Phase 3: Features (Week 5-6)
- [ ] Batch placement
- [ ] Alignment tools
- [ ] Naming utilities
- [ ] Actor replacement

### Phase 4: Polish (Week 7-8)
- [ ] Bug fixes
- [ ] Performance optimization
- [ ] Documentation
- [ ] Example content

### Phase 5: Release (Week 9-10)
- [ ] Final testing
- [ ] Marketplace submission
- [ ] Marketing materials
- [ ] Launch!

## Future Enhancements

### Version 1.1
- Preset saving/loading
- Additional patterns
- Custom pattern editor
- Performance improvements

### Version 1.5
- Material assignment tools
- Component manipulation
- Advanced scripting API
- Plugin extensibility

### Version 2.0
- AI-assisted placement
- Landscape integration
- Spline-based tools
- VR editor support

## Resources

### Unreal Engine Documentation
- Editor Scripting Utilities
- Editor Utility Widgets
- Blueprint Function Libraries
- Transaction System

### Development Tools
- Visual Studio / Rider
- Unreal Engine Editor
- Git for version control
- Documentation tools

## Questions & Discussion

For implementation questions or technical discussions, please open an issue on GitHub with the "technical" label.

---

**This guide is a living document and will be updated as development progresses.**
