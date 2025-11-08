# Developer Guide - Object Placement Manager

This guide is for developers who want to contribute to OPM or understand its internals.

## Table of Contents
- [Architecture Overview](#architecture-overview)
- [Building the Plugin](#building-the-plugin)
- [Code Structure](#code-structure)
- [Adding New Features](#adding-new-features)
- [Testing](#testing)
- [Contributing](#contributing)

---

## Architecture Overview

OPM follows a clean, modular architecture:

```
┌─────────────────────────────────────────────────┐
│          Editor Utility Widgets (UI)            │
│              (Blueprint/UMG)                    │
└─────────────────────┬───────────────────────────┘
                      │
┌─────────────────────┴───────────────────────────┐
│        OPMBlueprintLibrary (API Layer)          │
│         - Blueprint-callable functions          │
│         - Transaction management                │
│         - Input validation                      │
└─────────────────────┬───────────────────────────┘
                      │
┌─────────────────────┴───────────────────────────┐
│       Core Utility Classes (C++)                │
│  PlacementUtilities | AlignmentUtilities        │
│  NamingUtilities    | ActorReplacementUtilities │
│  OrganizationUtilities                          │
└─────────────────────┬───────────────────────────┘
                      │
┌─────────────────────┴───────────────────────────┐
│         Unreal Engine Editor API                │
│    (Actor manipulation, world queries, etc.)    │
└─────────────────────────────────────────────────┘
```

### Key Design Principles

1. **Separation of Concerns**: UI, API, and core logic are separate
2. **Editor-Only**: All code is editor-only, zero runtime overhead
3. **Transaction Support**: Every operation supports undo/redo
4. **Blueprint-Friendly**: Full API exposure to Blueprints
5. **Performance**: Batch operations for efficiency

---

## Building the Plugin

### Prerequisites

- Unreal Engine 5.3 or higher
- Visual Studio 2022 (Windows) or Xcode (Mac)
- Git for version control

### Setup

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Mittenzx/OPM.git
   cd OPM
   ```

2. **Create a test project:**
   ```bash
   # Create a blank UE5 project for testing
   # Copy the Plugins folder to your project
   ```

3. **Generate project files:**
   ```bash
   # Right-click .uproject -> Generate Visual Studio project files
   ```

4. **Build the plugin:**
   ```bash
   # Open the solution in Visual Studio
   # Build in Development Editor configuration
   ```

5. **Enable the plugin:**
   - Open the project in Unreal Engine
   - Edit -> Plugins -> Search "OPM"
   - Enable the plugin
   - Restart the editor

### Build Configurations

- **Development Editor**: For development and debugging
- **Shipping**: For final marketplace build

---

## Code Structure

### Module Organization

```
Plugins/OPM/Source/OPM/
├── Public/                 # Public headers
│   ├── OPM.h              # Main module header
│   ├── OPMTypes.h         # Core types and enums
│   ├── OPMBlueprintLibrary.h    # Blueprint API
│   ├── OPMTransactionUtils.h    # Transaction support
│   ├── PlacementUtilities.h     # Placement logic
│   ├── AlignmentUtilities.h     # Alignment logic
│   ├── NamingUtilities.h        # Naming logic
│   ├── ActorReplacementUtilities.h
│   └── OrganizationUtilities.h
└── Private/               # Implementation files
    ├── OPM.cpp            # Module implementation
    ├── OPMBlueprintLibrary.cpp
    ├── OPMTransactionUtils.cpp
    ├── PlacementUtilities.cpp
    ├── AlignmentUtilities.cpp
    ├── NamingUtilities.cpp
    ├── ActorReplacementUtilities.cpp
    └── OrganizationUtilities.cpp
```

### Key Files

**OPM.uplugin** - Plugin descriptor
- Defines plugin metadata
- Specifies module dependencies
- Engine version requirements

**OPM.Build.cs** - Build configuration
- Module dependencies
- Include paths
- Compile settings

**OPMTypes.h** - Core types
- Enums for operations
- Settings structures
- Shared data types

**OPMBlueprintLibrary.h/cpp** - API layer
- Blueprint-callable functions
- Transaction wrapping
- World context handling

**Utility Classes** - Core logic
- Pure C++ implementations
- No direct Blueprint dependencies
- Reusable algorithms

---

## Adding New Features

### Adding a New Utility Function

1. **Define in utility header:**
   ```cpp
   // In PlacementUtilities.h
   static TArray<FTransform> GenerateSpiralPattern(
       float Radius,
       int32 Count,
       float Height,
       const FTransform& Center);
   ```

2. **Implement in .cpp:**
   ```cpp
   // In PlacementUtilities.cpp
   TArray<FTransform> UOPM_PlacementUtilities::GenerateSpiralPattern(
       float Radius,
       int32 Count,
       float Height,
       const FTransform& Center)
   {
       TArray<FTransform> Transforms;
       // Implementation...
       return Transforms;
   }
   ```

3. **Expose to Blueprint:**
   ```cpp
   // In OPMBlueprintLibrary.h
   UFUNCTION(BlueprintCallable, Category = "OPM|Placement")
   static TArray<FTransform> GenerateSpiralPattern(
       float Radius,
       int32 Count,
       float Height,
       const FTransform& Center);
   
   // In OPMBlueprintLibrary.cpp
   TArray<FTransform> UOPMBlueprintLibrary::GenerateSpiralPattern(
       float Radius,
       int32 Count,
       float Height,
       const FTransform& Center)
   {
       return UOPM_PlacementUtilities::GenerateSpiralPattern(
           Radius, Count, Height, Center);
   }
   ```

4. **Add transaction support if modifying actors:**
   ```cpp
   void UOPMBlueprintLibrary::SomeFunction(TArray<AActor*> Actors)
   {
       FOPM_TransactionScope Transaction(
           LOCTEXT("SomeOp", "Some Operation"));
       Transaction.ModifyActors(Actors);
       // ... perform operation
   }
   ```

### Adding a New Settings Structure

```cpp
// In OPMTypes.h
USTRUCT(BlueprintType)
struct FSpiralPatternSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral")
    float Radius = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral")
    int32 Count = 20;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral")
    float Height = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral")
    float Rotations = 2.0f;
};
```

### Adding a New Utility Class

1. **Create header file:**
   ```cpp
   // In Public/NewUtilities.h
   #pragma once
   
   #include "CoreMinimal.h"
   
   class UOPM_NewUtilities
   {
   public:
       static void SomeFunction(...);
   };
   ```

2. **Create implementation:**
   ```cpp
   // In Private/NewUtilities.cpp
   #include "NewUtilities.h"
   
   void UOPM_NewUtilities::SomeFunction(...)
   {
       // Implementation
   }
   ```

3. **Include in main header:**
   ```cpp
   // In OPM.h
   #include "NewUtilities.h"
   ```

4. **Expose through Blueprint Library if needed**

---

## Testing

### Manual Testing in Editor

1. **Create test level:**
   - Create a new level for testing
   - Add various actors (cubes, spheres, etc.)

2. **Test via Blueprint:**
   - Create Editor Utility Widget
   - Add test buttons
   - Connect to OPM functions

3. **Test in C++:**
   ```cpp
   // In a test class or game mode
   #include "OPM.h"
   
   void ATestGameMode::TestPlacement()
   {
       FGridPatternSettings Settings;
       Settings.Rows = 5;
       Settings.Columns = 5;
       Settings.Spacing = FVector(100, 100, 0);
       
       TArray<FTransform> Transforms = 
           UOPM_PlacementUtilities::GenerateGridPattern(
               Settings, FTransform::Identity);
       
       // Verify results
       check(Transforms.Num() == 25);
   }
   ```

### Unit Testing (Future)

Create automated tests in a Test module:

```cpp
// In Tests/PlacementTests.cpp
#include "Misc/AutomationTest.h"
#include "PlacementUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FGridPatternTest,
    "OPM.Placement.GridPattern",
    EAutomationTestFlags::ApplicationContextMask | 
    EAutomationTestFlags::ProductFilter)

bool FGridPatternTest::RunTest(const FString& Parameters)
{
    FGridPatternSettings Settings;
    Settings.Rows = 3;
    Settings.Columns = 4;
    
    TArray<FTransform> Result = 
        UOPM_PlacementUtilities::GenerateGridPattern(
            Settings, FTransform::Identity);
    
    TestEqual("Grid size", Result.Num(), 12);
    return true;
}
```

### Performance Testing

```cpp
void TestPerformance()
{
    double StartTime = FPlatformTime::Seconds();
    
    // Perform operation
    FGridPatternSettings Settings;
    Settings.Rows = 100;
    Settings.Columns = 100;
    TArray<FTransform> Transforms = 
        UOPM_PlacementUtilities::GenerateGridPattern(
            Settings, FTransform::Identity);
    
    double ElapsedTime = FPlatformTime::Seconds() - StartTime;
    UE_LOG(LogTemp, Log, TEXT("Generated 10,000 transforms in %f seconds"), 
           ElapsedTime);
}
```

---

## Contributing

### Code Style

Follow Unreal Engine coding standards:

1. **Naming Conventions:**
   - Classes: `UOPM_ClassName` or `FOPM_ClassName`
   - Functions: `PascalCase`
   - Variables: `camelCase` for local, `PascalCase` for member
   - Constants: `PascalCase` with 'k' prefix if global

2. **Formatting:**
   - Tab indentation (4 spaces)
   - Allman braces style
   - Space after keywords

3. **Comments:**
   - Doxygen-style documentation for public APIs
   - Clear explanatory comments for complex logic

### Git Workflow

1. **Create feature branch:**
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Make changes and commit:**
   ```bash
   git add .
   git commit -m "Add feature description"
   ```

3. **Push and create PR:**
   ```bash
   git push origin feature/your-feature-name
   ```

4. **Submit pull request on GitHub**

### Pull Request Guidelines

- **Clear description** of what the PR does
- **Link to related issues** if applicable
- **Test your changes** thoroughly
- **Update documentation** if needed
- **Follow code style** guidelines
- **Keep PRs focused** on a single feature/fix

### Reporting Issues

When reporting bugs, include:
- Unreal Engine version
- Plugin version
- Steps to reproduce
- Expected vs actual behavior
- Screenshots/logs if applicable

---

## API Reference

### Transaction Management

```cpp
// Create a transaction scope
FOPM_TransactionScope Transaction(LOCTEXT("OpName", "Operation Name"));

// Mark actors for undo
Transaction.ModifyActors(Actors);

// Perform operations
// Transaction automatically ends on scope exit
```

### Common Patterns

**Safe Actor Iteration:**
```cpp
for (AActor* Actor : Actors)
{
    if (Actor)  // Always check for null
    {
        // Operate on actor
    }
}
```

**World Context:**
```cpp
UWorld* World = WorldContextObject->GetWorld();
if (!World)
{
    return;  // Always validate world
}
```

**Bounds Calculation:**
```cpp
FBox ActorBounds = Actor->GetComponentsBoundingBox(true);
// true = include non-colliding components
```

---

## Performance Considerations

### Optimization Tips

1. **Batch Operations:**
   - Process arrays, not individual items
   - Single transaction for multiple operations

2. **Memory:**
   - Reserve array capacity when size is known
   - Use const references for large data

3. **Editor Performance:**
   - Minimize viewport redraws
   - Use progress dialogs for long operations

### Profiling

```cpp
// Use Unreal's profiling tools
SCOPE_CYCLE_COUNTER(STAT_OPM_PlacementOperation);

// Or manual timing
double StartTime = FPlatformTime::Seconds();
// ... operation
double Duration = FPlatformTime::Seconds() - StartTime;
UE_LOG(LogTemp, Log, TEXT("Operation took %f seconds"), Duration);
```

---

## Debugging

### Enable Verbose Logging

```cpp
// In OPM.cpp
UE_LOG(LogTemp, Verbose, TEXT("OPM: %s"), *Message);
```

### Visual Debugging

```cpp
// Draw debug shapes in viewport
DrawDebugBox(World, Location, Extent, FColor::Red, false, 2.0f);
DrawDebugLine(World, Start, End, FColor::Green, false, 2.0f);
DrawDebugSphere(World, Center, Radius, 16, FColor::Blue, false, 2.0f);
```

### Breakpoint Debugging

- Set breakpoints in Visual Studio
- Launch editor in Debug mode
- Trigger operation to hit breakpoint

---

## Resources

### Unreal Engine Documentation
- [Plugin Development](https://docs.unrealengine.com/en-US/ProductionPipelines/Plugins/)
- [Editor Utilities](https://docs.unrealengine.com/en-US/InteractiveExperiences/UMG/UserGuide/EditorUtilityWidgets/)
- [Blueprint Function Libraries](https://docs.unrealengine.com/en-US/ProgrammingAndScripting/Blueprints/TechnicalGuide/ExtendingBlueprints/)

### Community
- [Unreal Slackers Discord](http://discord.gg/unreal-slackers)
- [Epic Developer Forums](https://forums.unrealengine.com/)
- [GitHub Issues](https://github.com/Mittenzx/OPM/issues)

---

## FAQ for Developers

**Q: Why separate utility classes from Blueprint library?**
A: Separation of concerns. Utility classes contain pure logic, Blueprint library handles API concerns (transactions, validation, etc.).

**Q: Why not use AActor inheritance for utilities?**
A: These are pure utility functions that don't need actor lifecycle. Keeps them lightweight and reusable.

**Q: How do I add a new pattern type?**
A: Add to `EPlacementPattern` enum, create settings struct, implement in `PlacementUtilities`, expose in Blueprint library.

**Q: What about thread safety?**
A: Current implementation is single-threaded on game thread. All actor operations must be on game thread per UE requirements.

---

## Contact

For development questions:
- Open an issue on GitHub
- Tag with 'question' or 'technical' label
- Provide code context and what you've tried

---

**Happy coding! 🚀**
