# Object Placement Manager - Version 2.0 Features

**Professional-Grade Advanced Features for Level Design**

This document details the major features introduced in OPM Version 2.0, representing a significant leap forward in intelligent placement and workflow automation.

---

## Overview

Version 2.0 introduces three groundbreaking feature sets that elevate OPM from a placement tool to an intelligent level design assistant:

1. **AI-Assisted Placement** - Machine learning-inspired pattern recognition and optimization
2. **Landscape Integration** - Terrain-aware placement with biome support
3. **Spline-Based Tools** - Path-following placement for roads, fences, and cables

---

## 1. AI-Assisted Placement 🤖

### Overview

AI-Assisted Placement brings intelligent decision-making to object placement, analyzing existing patterns and providing smart suggestions for optimal placement.

### Key Features

#### Pattern Recognition
Automatically detect placement patterns from existing actors:
- **Clustered** - Grouped objects with high density
- **Scattered** - Random distribution across an area
- **Linear** - Objects arranged in a line
- **Organic** - Natural, irregular distribution
- **Grid** - Regular grid arrangement
- **Radial** - Circular arrangement around a center point

#### Smart Suggestions
Generate placement suggestions based on existing actor context:
- Analyzes current placement patterns
- Suggests complementary positions
- Respects detected spacing and density
- Provides multiple alternatives

#### Automatic Optimization
Optimize actor placement based on different goals:
- **Performance** - Reduce overdraw and collision checks
- **Visual Quality** - Apply organic variation for natural look
- **Memory** - Group for instancing opportunities
- **Balanced** - Compromise between all factors

#### Organic Pattern Generation
Create natural-looking distributions using Poisson disk sampling:
- Maintains minimum spacing
- Avoids artificial grid patterns
- Suitable for vegetation, rocks, debris
- Customizable density and randomness

### Blueprint Functions

```cpp
// Detect what pattern actors follow
EAIPatternType DetectPlacementPattern(const TArray<AActor*>& Actors);

// Generate smart placement suggestions
int32 GenerateSmartSuggestions(
    const TArray<AActor*>& ExistingActors,
    const FAIPlacementSettings& Settings,
    TArray<FTransform>& SuggestedTransforms);

// Optimize existing placement
TArray<FTransform> OptimizeActorPlacement(
    const TArray<AActor*>& Actors,
    const FAIPlacementSettings& Settings);

// Create organic distribution
TArray<FTransform> GenerateOrganicPattern(
    const FBox& BoundsBox,
    int32 Count,
    const FAIPlacementSettings& Settings);

// Evaluate how good the placement is
float EvaluatePlacementQuality(const TArray<AActor*>& Actors);
```

### Settings Structure

```cpp
USTRUCT(BlueprintType)
struct FAIPlacementSettings
{
    // What to optimize for
    EAIOptimizationGoal OptimizationGoal;
    
    // Minimum confidence threshold (0.0 - 1.0)
    float Confidence;
    
    // Enable automatic optimization
    bool bAutoOptimize;
    
    // Maximum number of suggestions to generate
    int32 MaxSuggestions;
};
```

### Use Cases

1. **Smart Asset Population**
   - Place initial props manually
   - Let AI detect pattern
   - Generate suggestions for similar placement
   - Review and apply suggestions

2. **Placement Optimization**
   - Select existing actors
   - Choose optimization goal
   - Apply optimized transforms
   - Verify performance improvement

3. **Natural Environment Creation**
   - Use organic pattern generation
   - Distribute rocks, plants, debris
   - Adjust density for different areas
   - Achieve natural, non-repetitive look

---

## 2. Landscape Integration 🏔️

### Overview

Landscape Integration enables terrain-aware placement that respects landscape properties, follows contours, and distributes objects based on biome rules.

### Key Features

#### Terrain-Aware Placement
Place actors with automatic terrain alignment:
- **Height Sampling** - Place objects on landscape surface
- **Normal Alignment** - Orient to surface normal
- **Slope Alignment** - Align to terrain slope
- **Surface Snapping** - Snap to exact surface height

#### Slope and Height Filtering
Control placement based on terrain properties:
- Maximum slope angle restriction
- Minimum/maximum height range
- Automatic filtering of invalid locations
- Terrain complexity analysis

#### Biome-Based Distribution
Distribute objects according to biome types:
- **Forest** - Moderate clustering, medium density
- **Desert** - Sparse, scattered placement
- **Mountain** - Very sparse, isolated placement
- **Plains** - Even, moderate distribution
- **Water** - Moderate density near shores
- **Urban** - High clustering, dense placement
- **Custom** - User-defined parameters

#### Foliage Integration
Respect and integrate with foliage system:
- Query foliage density at locations
- Avoid areas with dense foliage
- Filter placement by foliage threshold
- Coordinate with procedural foliage

### Blueprint Functions

```cpp
// Place actors on landscape with terrain awareness
TArray<AActor*> PlaceActorsOnLandscape(
    UClass* ActorClass,
    const TArray<FTransform>& Transforms,
    ALandscape* Landscape,
    const FLandscapePlacementSettings& Settings);

// Sample terrain properties
bool SampleLandscapeHeight(ALandscape* Landscape, const FVector& Location, float& OutHeight);
float CalculateSlopeAngle(ALandscape* Landscape, const FVector& Location);

// Distribute based on biome
TArray<FTransform> DistributeByBiome(
    const FBox& BoundsBox,
    int32 Count,
    EBiomeType BiomeType,
    ALandscape* Landscape);

// Find landscape in world
ALandscape* FindLandscapeInWorld(UObject* WorldContextObject);
```

### Settings Structure

```cpp
USTRUCT(BlueprintType)
struct FLandscapePlacementSettings
{
    // How to align to terrain
    ETerrainAlignment TerrainAlignment;
    
    // Maximum allowed slope (degrees)
    float MaxSlope;
    
    // Height range restrictions
    float MinHeight;
    float MaxHeight;
    
    // Consider foliage when placing
    bool bUseFoliageRules;
    
    // Biome type for distribution
    EBiomeType BiomeType;
};
```

### Use Cases

1. **Terrain-Aware Props**
   - Place props that follow terrain
   - Automatically align to surface normals
   - Respect slope limitations
   - Filter out steep or unsuitable areas

2. **Biome Population**
   - Define biome type for region
   - Generate appropriate distribution
   - Match vegetation density
   - Create believable environments

3. **Contour Following**
   - Place objects along contour lines
   - Maintain consistent height
   - Follow terrain features
   - Create natural paths and boundaries

---

## 3. Spline-Based Tools 🛤️

### Overview

Spline-Based Tools enable path-following placement for creating roads, fences, cables, and any linear structures that need to follow a defined path.

### Key Features

#### Flexible Placement Modes
Multiple ways to place objects along splines:
- **Uniform** - Even spacing along the path
- **By Distance** - Specific distance intervals
- **By Spline Points** - At spline control points
- **Adaptive** - Dense on curves, sparse on straights

#### Intelligent Alignment
Automatic orientation based on spline:
- **Tangent** - Face along the path direction
- **Normal** - Orient to spline normal
- **Up Vector** - Maintain upright orientation
- **No Alignment** - Keep original rotation

#### Road Generation
Create complete road systems:
- Place road segments along spline
- Add props (signs, barriers, lights) on both sides
- Automatic spacing and alignment
- Support for branching roads

#### Fence Generation
Build fences and walls:
- Place posts at regular intervals
- Add panels between posts
- Automatic scaling to fit gaps
- Support for varying terrain

#### Cable/Pipe Routing
Route cables and pipes:
- Add support structures at intervals
- Create catenary sag between supports
- Automatic cable segment placement
- Realistic physics-based curves

### Blueprint Functions

```cpp
// Place actors along spline
TArray<AActor*> PlaceActorsAlongSpline(
    UClass* ActorClass,
    USplineComponent* SplineComponent,
    const FSplinePlacementSettings& Settings);

// Generate road with props
TArray<AActor*> GenerateRoadAlongSpline(
    USplineComponent* SplineComponent,
    UClass* RoadActorClass,
    const TArray<UClass*>& PropActorClasses,
    float PropSpacing);

// Generate fence
TArray<AActor*> GenerateFenceAlongSpline(
    USplineComponent* SplineComponent,
    UClass* PostActorClass,
    UClass* PanelActorClass,
    float PostSpacing);

// Generate cable routing
TArray<AActor*> GenerateCableRoutingAlongSpline(
    USplineComponent* SplineComponent,
    UClass* CableActorClass,
    UClass* SupportsActorClass,
    float SupportSpacing,
    float SagAmount);

// Get spline properties
float GetSplineLength(USplineComponent* SplineComponent);
TArray<float> GetAdaptiveDistances(USplineComponent* SplineComponent, float MinSpacing, float MaxSpacing);
```

### Settings Structure

```cpp
USTRUCT(BlueprintType)
struct FSplinePlacementSettings
{
    // How to place objects
    ESplinePlacementMode PlacementMode;
    
    // How to orient objects
    ESplineAlignment Alignment;
    
    // Spacing between objects
    float Spacing;
    
    // Local offset from spline
    FVector Offset;
    
    // Scale objects by spline scale
    bool bScaleBySpline;
    
    // Offset from start/end
    float StartOffset;
    float EndOffset;
};
```

### Use Cases

1. **Road Creation**
   - Draw spline for road path
   - Generate road segments
   - Add street props (lights, signs)
   - Create realistic streets

2. **Fence Building**
   - Define fence boundary with spline
   - Generate posts and panels
   - Automatic terrain following
   - Quick perimeter creation

3. **Cable Routing**
   - Plan cable path with spline
   - Add support poles
   - Generate sagging cables
   - Realistic infrastructure

4. **Decorative Paths**
   - Place lights along paths
   - Add props at regular intervals
   - Create guided tours
   - Decorate walkways

---

## Technical Details

### Performance Considerations

#### AI Placement
- Pattern detection: O(n²) for overlap checking
- Smart suggestions: O(n) for pattern analysis
- Optimization: O(n) for basic transforms
- Recommended for < 1000 actors at once

#### Landscape Integration
- Height sampling: O(1) per query
- Slope calculation: O(1) per query
- Terrain complexity: O(samples²)
- Efficient for large-scale placement

#### Spline Tools
- Transform generation: O(n) where n = number of points
- Adaptive spacing: O(length/minSpacing)
- Curvature calculation: O(1) per sample
- Suitable for any spline length

### Best Practices

#### AI-Assisted Placement
1. Start with manual placement of 5-10 objects
2. Use pattern detection to understand arrangement
3. Generate suggestions in batches
4. Review and apply selectively
5. Optimize after major placement operations

#### Landscape Integration
1. Ensure landscape is fully loaded
2. Use appropriate biome for environment
3. Set realistic slope limitations
4. Consider foliage density
5. Test with small batches first

#### Spline-Based Tools
1. Create clean, smooth splines
2. Use appropriate placement mode
3. Test spacing with one instance
4. Consider performance with many objects
5. Use adaptive spacing on complex paths

---

## Integration with Existing Features

### Works With v1.0 Features

#### Placement Patterns
- Combine AI suggestions with grid patterns
- Use organic distribution with landscape filtering
- Apply existing patterns along splines

#### Alignment Tools
- Align spline-placed objects afterward
- Distribute landscape objects evenly
- Center AI-generated suggestions

#### Naming Utilities
- Auto-name spline-placed objects
- Number fence posts sequentially
- Organize by biome or pattern type

#### Organization
- Group spline objects by path
- Folder landscape objects by biome
- Tag AI-optimized actors

---

## Examples and Workflows

### Example 1: Natural Forest Scene

```blueprint
1. Find landscape in world
2. Define forest bounds
3. Generate organic pattern with Forest biome
4. Place trees on landscape with terrain alignment
5. Use AI to evaluate placement quality
6. Optimize if needed
```

### Example 2: Road with Fence

```blueprint
1. Draw spline for road path
2. Generate road segments along spline
3. Add road props (signs, barriers)
4. Create parallel spline for fence
5. Generate fence along parallel spline
6. Snap spline to terrain
```

### Example 3: Power Line Infrastructure

```blueprint
1. Draw spline for power line route
2. Generate power poles at support spacing
3. Create cable segments with sag
4. Use adaptive spacing on terrain changes
5. Snap to terrain height
6. Add insulators and equipment
```

### Example 4: AI-Enhanced Decoration

```blueprint
1. Manually place 8-10 props
2. Detect placement pattern
3. Generate 20 smart suggestions
4. Review and accept 15 suggestions
5. Optimize for visual quality
6. Evaluate placement quality score
```

---

## Limitations and Known Issues

### AI Placement
- Pattern detection requires minimum 3 actors
- Organic patterns may need multiple attempts
- Optimization is heuristic-based, not perfect
- Large selections (>1000) may be slow

### Landscape Integration
- Requires valid landscape in scene
- Foliage integration is basic (no detailed queries)
- Height sampling may fail at landscape edges
- Biome parameters are preset (not customizable in v2.0)

### Spline Tools
- Cable sag uses simple parabola (not catenary)
- Branching splines need manual adjustment
- No automatic obstacle avoidance
- Terrain snapping uses simple raycasts

---

## Future Enhancements (v2.1+)

### Planned Improvements
1. **Machine Learning Integration**
   - Train custom pattern recognition models
   - Learn from user preferences
   - Adaptive optimization strategies

2. **Advanced Landscape Features**
   - Custom biome definitions
   - Layer-based material queries
   - Integration with procedural foliage spawner
   - Erosion and weathering patterns

3. **Enhanced Spline Tools**
   - True catenary curves for cables
   - Automatic obstacle avoidance
   - Road width and banking
   - Tunnels and bridges

4. **Cross-Feature Integration**
   - AI-optimized spline placement
   - Landscape-aware organic patterns
   - Biome-specific AI suggestions

---

## API Reference

### Enumerations

#### EAIOptimizationGoal
- `Performance` - Optimize for rendering performance
- `VisualQuality` - Optimize for visual appearance
- `Balanced` - Balance between performance and quality
- `Memory` - Optimize for memory usage

#### EAIPatternType
- `Clustered` - Grouped distribution
- `Scattered` - Random distribution
- `Linear` - Line arrangement
- `Organic` - Natural distribution
- `Grid` - Regular grid
- `Radial` - Circular arrangement

#### ETerrainAlignment
- `None` - No terrain alignment
- `AlignToNormal` - Orient to surface normal
- `AlignToSlope` - Align to terrain slope
- `SnapToSurface` - Snap Z to surface height

#### EBiomeType
- `Forest` - Forest environment
- `Desert` - Desert environment
- `Mountain` - Mountain environment
- `Plains` - Plains/grassland
- `Water` - Water/coastal
- `Urban` - Urban/city
- `Custom` - User-defined

#### ESplinePlacementMode
- `Uniform` - Even spacing
- `ByDistance` - Specific distances
- `BySplinePoints` - At control points
- `Adaptive` - Density based on curvature

#### ESplineAlignment
- `Tangent` - Align to path direction
- `Normal` - Align to spline normal
- `Up` - Maintain upright
- `None` - No alignment

---

## Migration from v1.0

Version 2.0 is **fully backward compatible** with v1.0. All existing:
- Placement patterns continue to work
- Alignment tools unchanged
- Naming utilities unchanged
- Organization features unchanged
- Blueprint API extended (not modified)

### New Dependencies
- **Landscape** module added for terrain features
- No breaking changes to existing code
- All v1.0 functions remain available

---

## Support and Documentation

### Resources
- **User Guide**: See QUICKSTART.md for basic usage
- **API Reference**: Full API in DEVELOPER.md
- **Examples**: Example project (coming soon)
- **Video Tutorials**: YouTube channel (coming soon)

### Getting Help
- **GitHub Issues**: Bug reports and feature requests
- **Discussions**: Community Q&A and showcases
- **Documentation**: Comprehensive guides and API reference

---

## Credits and Acknowledgments

Version 2.0 features inspired by:
- Community feedback and feature requests
- Professional level design workflows
- Industry-standard placement tools
- Research in procedural generation

**Thank you to all contributors and beta testers!**

---

**Object Placement Manager v2.0**  
*Intelligent Level Design Tools for Unreal Engine*

*Created by Mittenzx*  
*License: MIT*
