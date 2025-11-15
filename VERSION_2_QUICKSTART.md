# Version 2.0 Quick Start Guide

**Get Started with Advanced Features in 5 Minutes**

---

## What's New in Version 2.0?

OPM Version 2.0 introduces three powerful feature sets that transform how you place objects in Unreal Engine:

1. 🤖 **AI-Assisted Placement** - Smart suggestions and automatic optimization
2. 🏔️ **Landscape Integration** - Terrain-aware placement with biome support
3. 🛤️ **Spline-Based Tools** - Roads, fences, and cables along paths

---

## 5-Minute Quick Starts

### AI-Assisted Placement

**Use Case:** You've placed some props manually and want suggestions for more.

```cpp
// In Blueprint or C++

// 1. Get your existing actors
TArray<AActor*> ExistingProps = GetSelectedActors();

// 2. Configure AI settings
FAIPlacementSettings Settings;
Settings.OptimizationGoal = EAIOptimizationGoal::VisualQuality;
Settings.MaxSuggestions = 10;

// 3. Generate smart suggestions
TArray<FTransform> Suggestions;
GenerateSmartSuggestions(ExistingProps, Settings, Suggestions);

// 4. Place actors at suggested locations
// (Review suggestions and place the ones you like)
```

**Result:** AI analyzes your placement pattern and suggests 10 complementary positions!

---

### Landscape Integration

**Use Case:** Place trees that follow terrain and respect slopes.

```cpp
// In Blueprint or C++

// 1. Find landscape
ALandscape* Landscape = FindLandscapeInWorld(this);

// 2. Configure landscape settings
FLandscapePlacementSettings Settings;
Settings.TerrainAlignment = ETerrainAlignment::AlignToNormal;
Settings.MaxSlope = 30.0f; // Only place on slopes < 30 degrees
Settings.BiomeType = EBiomeType::Forest;

// 3. Generate forest distribution
FBox PlacementArea = FBox(FVector(0, 0, 0), FVector(5000, 5000, 0));
TArray<FTransform> TreeLocations = DistributeByBiome(
    PlacementArea, 
    100, // 100 trees
    EBiomeType::Forest, 
    Landscape
);

// 4. Place trees on landscape
TArray<AActor*> Trees = PlaceActorsOnLandscape(
    this, 
    TreeClass, 
    TreeLocations, 
    Landscape, 
    Settings
);
```

**Result:** 100 trees placed on suitable terrain, aligned to surface, avoiding steep slopes!

---

### Spline-Based Tools

**Use Case:** Create a fence along a property boundary.

```cpp
// In Blueprint or C++

// 1. Get spline component (draw in editor first)
USplineComponent* BoundarySpline = GetSplineComponent();

// 2. Generate fence
TArray<AActor*> Fence = GenerateFenceAlongSpline(
    this,
    BoundarySpline,
    FencePostClass,    // Your fence post actor
    FencePanelClass,   // Your fence panel actor
    300.0f             // 3 meters between posts
);
```

**Result:** Complete fence with posts and panels following your spline path!

---

## Common Patterns

### Pattern 1: Natural Environment

```cpp
// Step 1: Create organic rock distribution
TArray<FTransform> RockLocations = GenerateOrganicPattern(
    MyBounds, 
    50,
    AISettings
);

// Step 2: Place on landscape with terrain alignment
TArray<AActor*> Rocks = PlaceActorsOnLandscape(
    this, RockClass, RockLocations, Landscape, LandscapeSettings
);

// Step 3: Optimize for performance
TArray<FTransform> OptimizedTransforms = OptimizeActorPlacement(
    Rocks, 
    AISettings
);
```

### Pattern 2: Road with Props

```cpp
// Step 1: Draw road spline in editor

// Step 2: Generate complete road
TArray<AActor*> RoadActors = GenerateRoadAlongSpline(
    this,
    RoadSpline,
    RoadSegmentClass,
    { StreetLightClass, SignClass }, // Props array
    1000.0f // Props every 10 meters
);

// Step 3: Snap to terrain if needed
SnapSplineToTerrain(RoadSpline, GetWorld(), 10.0f);
```

### Pattern 3: Smart Prop Placement

```cpp
// Step 1: Place 5-10 props manually in a pattern

// Step 2: Detect the pattern
EAIPatternType Pattern = DetectPlacementPattern(MyProps);
// Returns: Grid, Circular, Linear, Organic, etc.

// Step 3: Generate matching suggestions
TArray<FTransform> Suggestions;
GenerateSmartSuggestions(MyProps, AISettings, Suggestions);

// Step 4: Review quality
float Quality = EvaluatePlacementQuality(MyProps);
// Returns: 0.0 (poor) to 1.0 (excellent)
```

---

## Feature Matrix

| Feature | Best For | Setup Time | Flexibility |
|---------|----------|------------|-------------|
| **AI Suggestions** | Continuing patterns | 1 min | High |
| **Organic Patterns** | Natural scattering | 30 sec | High |
| **Biome Distribution** | Large landscapes | 2 min | Medium |
| **Spline Roads** | Linear structures | 3 min | Medium |
| **Spline Fences** | Boundaries | 2 min | Low |
| **Spline Cables** | Infrastructure | 3 min | Medium |

---

## Settings Reference

### AI Placement Settings

```cpp
FAIPlacementSettings Settings;
Settings.OptimizationGoal = EAIOptimizationGoal::Balanced;
Settings.Confidence = 0.7f;          // 0.0 - 1.0
Settings.bAutoOptimize = true;
Settings.MaxSuggestions = 5;         // Number of suggestions
```

**Optimization Goals:**
- `Performance` - Reduce rendering cost
- `VisualQuality` - Better appearance
- `Memory` - Enable instancing
- `Balanced` - Mix of all (recommended)

### Landscape Settings

```cpp
FLandscapePlacementSettings Settings;
Settings.TerrainAlignment = ETerrainAlignment::AlignToNormal;
Settings.MaxSlope = 45.0f;           // Degrees
Settings.MinHeight = 0.0f;           // World units
Settings.MaxHeight = 10000.0f;       // World units
Settings.bUseFoliageRules = true;
Settings.BiomeType = EBiomeType::Forest;
```

**Biome Types:**
- `Forest` - Trees, moderate clustering
- `Desert` - Sparse, scattered
- `Mountain` - Very sparse, isolated
- `Plains` - Even distribution
- `Water` - Coastal placement
- `Urban` - Dense, clustered

### Spline Settings

```cpp
FSplinePlacementSettings Settings;
Settings.PlacementMode = ESplinePlacementMode::Uniform;
Settings.Alignment = ESplineAlignment::Tangent;
Settings.Spacing = 100.0f;           // Distance between objects
Settings.Offset = FVector(0, 50, 0); // Local offset
Settings.bScaleBySpline = false;
Settings.StartOffset = 0.0f;
Settings.EndOffset = 0.0f;
```

**Placement Modes:**
- `Uniform` - Even spacing
- `ByDistance` - Fixed distance
- `BySplinePoints` - At control points
- `Adaptive` - More on curves

**Alignment Modes:**
- `Tangent` - Face path direction
- `Normal` - Perpendicular to path
- `Up` - Maintain upright
- `None` - No rotation

---

## Tips and Tricks

### AI Placement
✅ **DO:**
- Start with 5-10 manual placements
- Use organic patterns for nature
- Check quality score regularly
- Optimize after major changes

❌ **DON'T:**
- Expect perfect results immediately
- Use with < 3 actors
- Optimize repeatedly without changes
- Apply all suggestions blindly

### Landscape Integration
✅ **DO:**
- Set realistic slope limits
- Use appropriate biome types
- Check terrain first
- Filter by height for zones

❌ **DON'T:**
- Place without landscape loaded
- Use extreme slope values
- Ignore foliage overlap
- Mix incompatible biomes

### Spline Tools
✅ **DO:**
- Draw smooth splines first
- Test spacing with one object
- Use adaptive for complex paths
- Snap to terrain when needed

❌ **DON'T:**
- Use too tight curves
- Over-complicate splines
- Place too many objects
- Forget to adjust offsets

---

## Troubleshooting

### AI Placement Issues

**Problem:** No suggestions generated
- **Solution:** Ensure you have 3+ actors selected
- **Solution:** Check if actors have valid transforms

**Problem:** Suggestions overlap
- **Solution:** Increase spacing in detected pattern
- **Solution:** Use DetectAndCorrectOverlaps function

### Landscape Issues

**Problem:** Objects floating or underground
- **Solution:** Enable SnapToSurface alignment
- **Solution:** Increase height sampling accuracy

**Problem:** Objects on steep slopes
- **Solution:** Lower MaxSlope value
- **Solution:** Use FilterLocationsByTerrain

### Spline Issues

**Problem:** Objects not following path
- **Solution:** Check spline is valid and has points
- **Solution:** Verify placement mode is correct

**Problem:** Too many/few objects
- **Solution:** Adjust Spacing value
- **Solution:** Use StartOffset/EndOffset

---

## Next Steps

### Learn More
1. Read **VERSION_2_FEATURES.md** for complete documentation
2. Check **USAGE_EXAMPLES.md** for detailed workflows
3. Explore **DEVELOPER.md** for API reference

### Try Advanced Features
1. Combine AI + Landscape for smart terrain placement
2. Use splines + biomes for realistic roads
3. Chain multiple tools for complex scenes

### Get Help
- **GitHub Issues**: Report bugs
- **Discussions**: Ask questions
- **Documentation**: Comprehensive guides

---

## Examples You Can Build Right Now

### 1. Forest Scene (5 minutes)
```
1. Draw area bounds
2. Generate organic pattern
3. Add biome distribution (Forest)
4. Place trees on landscape
5. Evaluate and optimize
```

### 2. Desert Outpost (7 minutes)
```
1. Place buildings manually
2. Generate smart suggestions for rocks
3. Use Desert biome for cacti
4. Add fence along spline boundary
5. Optimize for performance
```

### 3. Mountain Path (10 minutes)
```
1. Draw path spline
2. Snap to terrain
3. Generate fence along one side
4. Add rocks using contour following
5. Place signs with adaptive spacing
```

---

## Version 2.0 at a Glance

| Category | Features | Functions |
|----------|----------|-----------|
| **AI** | 5 major features | 8 functions |
| **Landscape** | 7 terrain tools | 5 functions |
| **Spline** | 6 generation types | 7 functions |
| **Total** | **18 features** | **20+ functions** |

---

**Ready to build amazing levels? Start with one feature and expand from there!**

For complete details, see [VERSION_2_FEATURES.md](VERSION_2_FEATURES.md)
