# OPM Blueprint API Reference for UI Development

This document provides a complete reference of all Blueprint-callable functions in the OPM plugin for use in Editor Utility Widgets.

## Table of Contents
- [Overview](#overview)
- [Getting Selected Actors](#getting-selected-actors)
- [Placement Functions](#placement-functions)
- [Alignment Functions](#alignment-functions)
- [Naming Functions](#naming-functions)
- [Replacement Functions](#replacement-functions)
- [Organization Functions](#organization-functions)
- [Utility Functions](#utility-functions)
- [Common Patterns](#common-patterns)

## Overview

All functions are available in the **OPM Blueprint Library** class. They can be accessed in Blueprint graphs under the "OPM" category.

### World Context

Many functions require a World Context Object. In Editor Utility Widgets:
- Use `Get Editor World` or `Get World Context`
- This ensures operations affect the editor world, not PIE (Play In Editor)

### Transaction Support

All functions automatically support Undo/Redo. No special handling required in your Blueprint code.

## Getting Selected Actors

Before calling most OPM functions, you need to get the currently selected actors.

### Get Selected Actors

```
Function: Get Editor Utility Library > Get Selected Level Actors
Returns: Array<Actor>
Category: Editor Scripting | Level Utility

Usage in Blueprint:
  GetSelectedLevelActors → Selected Actors Array
```

**Example:**
```
Event Button Clicked
├── Get Selected Level Actors
│   └── Selected Actors (out)
└── Branch (Array Length > 0)
    ├── True → Proceed with operation
    └── False → Show error "No actors selected"
```

## Placement Functions

### Place Actors in Grid Pattern

```
Function: PlaceActorsInGrid
Category: OPM|Placement

Inputs:
  - World Context Object (Object Reference)
  - Actor Class (Class)
  - Rows (Integer) - Number of rows
  - Columns (Integer) - Number of columns
  - Spacing X (Float) - Space between columns
  - Spacing Y (Float) - Space between rows
  - Spacing Z (Float) - Vertical offset per row
  - Origin Location (Vector) - Starting position
  - Origin Rotation (Rotator) - Base rotation

Returns: Array<Actor> - Newly placed actors

Example Values:
  - Rows: 5
  - Columns: 5
  - Spacing: 200.0 (all axes)
  - Origin: (0, 0, 0)
```

**Blueprint Usage:**
```
Button Clicked
├── Get Editor World → World
├── Get Actor Class from Picker → Class
├── Get Spin Box Values → Rows, Columns, Spacing
├── PlaceActorsInGrid
│   ├── World Context: World
│   ├── Actor Class: Class
│   ├── Rows: 5
│   ├── Columns: 5
│   ├── Spacing X/Y/Z: 200.0
│   ├── Origin Location: (0, 0, 0)
│   └── Origin Rotation: (0, 0, 0)
└── Print ("Placed X actors")
```

### Place Actors in Circular Pattern

```
Function: PlaceActorsInCircularPattern
Category: OPM|Placement

Inputs:
  - World Context Object
  - Actor Class (Class)
  - Count (Integer) - Number of actors
  - Radius (Float) - Circle radius
  - Start Angle (Float) - Starting angle in degrees
  - Height (Float) - Height offset from center
  - Center Location (Vector)
  - Center Rotation (Rotator)

Returns: Array<Actor>

Example Values:
  - Count: 12
  - Radius: 500.0
  - Start Angle: 0.0
  - Height: 0.0
```

**Blueprint Usage:**
```
Button Clicked
├── Get Values from UI
│   ├── Count: SB_Count → Value
│   ├── Radius: SB_Radius → Value
│   └── Start Angle: SB_Angle → Value
├── Get Selected Actors → Get First Element → Center Point
├── Get Actor Location (Center Point) → Center Location
└── PlaceActorsInCircularPattern
    ├── World Context: Editor World
    ├── Actor Class: Selected Class
    ├── Count: Count Value
    ├── Radius: Radius Value
    ├── Start Angle: Angle Value
    ├── Height: 0.0
    ├── Center Location: Center Location
    └── Center Rotation: (0, 0, 0)
```

### Place Actors in Line Pattern

```
Function: PlaceActorsInLine
Category: OPM|Placement

Inputs:
  - World Context Object
  - Actor Class (Class)
  - Count (Integer) - Number of actors along line
  - Start Location (Vector)
  - End Location (Vector)
  - Rotation (Rotator) - Applied to all actors

Returns: Array<Actor>

Example Values:
  - Count: 10
  - Start: (0, 0, 0)
  - End: (1000, 0, 0)
```

### Place Actors Randomly

```
Function: PlaceActorsRandomly
Category: OPM|Placement

Inputs:
  - World Context Object
  - Actor Class (Class)
  - Count (Integer)
  - Bounds Min (Vector) - Minimum bounds
  - Bounds Max (Vector) - Maximum bounds
  - Random Seed (Integer) - For reproducible randomness
  - Base Rotation (Rotator)

Returns: Array<Actor>

Example Values:
  - Count: 50
  - Bounds Min: (-500, -500, 0)
  - Bounds Max: (500, 500, 100)
  - Seed: -1 (random each time)
```

## Alignment Functions

### Align Actors (Generic)

```
Function: AlignActors
Category: OPM|Alignment

Inputs:
  - Actors (Array<Actor>)
  - Alignment Type (Enum: EAlignmentType)
    • Left
    • Right
    • Center
    • Top
    • Bottom
    • Front
    • Back
  - Alignment Axis (Enum: EAlignmentAxis)
    • X
    • Y
    • Z

Returns: None (modifies actors in place)
```

**Blueprint Usage:**
```
Button Align Left Clicked
├── Get Selected Level Actors → Actors
└── AlignActors
    ├── Actors: Selected Actors
    ├── Alignment Type: Left
    └── Alignment Axis: X
```

### Specific Alignment Functions

Each alignment has a dedicated function for convenience:

```
AlignActorsLeft(Actors)
AlignActorsRight(Actors)
AlignActorsTop(Actors)
AlignActorsBottom(Actors)
AlignActorsFront(Actors)
AlignActorsBack(Actors)
CenterActorsX(Actors)
CenterActorsY(Actors)
CenterActorsZ(Actors)
```

**Example:**
```
Button Align Center Clicked
├── Get Selected Level Actors
└── CenterActorsX (Actors)
    └── Print "Actors centered on X axis"
```

### Distribute Actors

```
Function: DistributeActors
Category: OPM|Alignment

Inputs:
  - Actors (Array<Actor>)
  - Distribution Type (Enum: EDistributionType)
    • Horizontal
    • Vertical
    • Radial

Returns: None
```

**Specific Distribution Functions:**
```
DistributeActorsHorizontally(Actors)
DistributeActorsVertically(Actors)
```

**Example:**
```
Button Distribute Clicked
├── Get Selected Level Actors
└── DistributeActorsHorizontally (Actors)
```

### Snap to Grid

```
Function: SnapActorToGrid
Category: OPM|Alignment

Inputs:
  - Actor (Actor Reference)
  - Grid Size (Float) - Grid unit size

Returns: None

---

Function: SnapActorsToGrid
Category: OPM|Alignment

Inputs:
  - Actors (Array<Actor>)
  - Grid Size (Float)

Returns: None
```

**Example:**
```
Button Snap Clicked
├── Get Selected Level Actors
├── Get Grid Size from Spin Box → Grid Size
└── SnapActorsToGrid
    ├── Actors: Selected Actors
    └── Grid Size: Grid Size Value
```

## Naming Functions

### Batch Rename

```
Function: BatchRename
Category: OPM|Naming

Inputs:
  - Actors (Array<Actor>)
  - Prefix (String) - Added to beginning
  - Suffix (String) - Added to end
  - Start Number (Integer) - First number in sequence
  - Number Padding (Integer) - Zeros to pad (e.g., 3 = "001")

Returns: None

Example:
  - Prefix: "Prop_"
  - Suffix: "_LOD0"
  - Start Number: 1
  - Padding: 3
  - Result: "Prop_001_LOD0", "Prop_002_LOD0", etc.
```

**Blueprint Usage:**
```
Button Apply Naming Clicked
├── Get Selected Level Actors
├── Get Text from UI
│   ├── TB_Prefix → Prefix Text
│   └── TB_Suffix → Suffix Text
├── Get Spin Box Values
│   ├── SB_StartNum → Start Number
│   └── SB_Padding → Padding
└── BatchRename
    ├── Actors: Selected Actors
    ├── Prefix: Prefix Text
    ├── Suffix: Suffix Text
    ├── Start Number: Start Number
    └── Number Padding: Padding
```

### Add Prefix/Suffix

```
Function: AddPrefix
Category: OPM|Naming

Inputs:
  - Actors (Array<Actor>)
  - Prefix (String)

---

Function: AddSuffix
Category: OPM|Naming

Inputs:
  - Actors (Array<Actor>)
  - Suffix (String)
```

### Auto Number

```
Function: AutoNumber
Category: OPM|Naming

Inputs:
  - Actors (Array<Actor>)
  - Start Number (Integer)
  - Padding (Integer)

Note: Appends numbers to existing names
```

### Find and Replace

```
Function: FindAndReplace
Category: OPM|Naming

Inputs:
  - Actors (Array<Actor>)
  - Find Text (String)
  - Replace Text (String)
  - Case Sensitive (Boolean)

Returns: None

Example:
  - Find: "Cube"
  - Replace: "Box"
  - Current: "StaticMeshCube_01"
  - Result: "StaticMeshBox_01"
```

**Blueprint Usage:**
```
Button Find Replace Clicked
├── Get Selected Level Actors
├── Get Find/Replace Text
│   ├── TB_Find → Find Text
│   └── TB_Replace → Replace Text
├── Get Case Sensitive Checkbox → Is Checked
└── FindAndReplace
    ├── Actors: Selected Actors
    ├── Find Text: Find Text
    ├── Replace Text: Replace Text
    └── Case Sensitive: Is Checked
```

### Remove Prefix/Suffix

```
Function: RemovePrefix
Category: OPM|Naming

Inputs:
  - Actors (Array<Actor>)
  - Prefix (String) - Prefix to remove

---

Function: RemoveSuffix
Category: OPM|Naming

Inputs:
  - Actors (Array<Actor>)
  - Suffix (String) - Suffix to remove
```

## Replacement Functions

### Replace Single Actor

```
Function: ReplaceActor
Category: OPM|Replacement

Inputs:
  - World Context Object
  - Original Actor (Actor)
  - New Actor Class (Class)
  - Preserve Transform (Boolean) - Keep location/rotation/scale
  - Preserve Attachments (Boolean) - Maintain parent-child relationships

Returns: Actor (New actor instance)
```

### Batch Replace Actors

```
Function: BatchReplaceActors
Category: OPM|Replacement

Inputs:
  - World Context Object
  - Original Actors (Array<Actor>)
  - New Actor Class (Class)
  - Preserve Transform (Boolean)
  - Preserve Attachments (Boolean)

Returns: Array<Actor> (New actors)
```

**Blueprint Usage:**
```
Button Replace Clicked
├── Show Confirmation Dialog
│   └── Message: "Replace X actors?"
├── On Confirmed
│   ├── Get Selected Level Actors
│   ├── Get New Actor Class from Picker
│   ├── Get Checkbox States
│   │   ├── CB_PreserveTransform → Preserve Transform
│   │   └── CB_PreserveAttachments → Preserve Attachments
│   └── BatchReplaceActors
│       ├── World Context: Editor World
│       ├── Original Actors: Selected Actors
│       ├── New Actor Class: New Class
│       ├── Preserve Transform: Preserve Transform
│       └── Preserve Attachments: Preserve Attachments
└── On Cancelled
    └── Print "Replacement cancelled"
```

## Organization Functions

### Set Actor Folder

```
Function: SetActorFolder
Category: OPM|Organization

Inputs:
  - Actors (Array<Actor>)
  - Folder Path (String) - e.g., "/Environment/Props"

Returns: None
```

**Blueprint Usage:**
```
Button Set Folder Clicked
├── Get Selected Level Actors
├── Get Folder Path from Text Box
└── SetActorFolder
    ├── Actors: Selected Actors
    └── Folder Path: Folder Path Text
```

### Group Actors by Type

```
Function: GroupActorsByType
Category: OPM|Organization

Inputs:
  - Actors (Array<Actor>)

Returns: None

Note: Creates parent actors for each type and attaches actors to them
```

### Tag Management

```
Function: ApplyTagsToActors
Category: OPM|Organization

Inputs:
  - Actors (Array<Actor>)
  - Tags (Array<Name>)

---

Function: RemoveTagsFromActors
Category: OPM|Organization

Inputs:
  - Actors (Array<Actor>)
  - Tags (Array<Name>)

---

Function: ClearActorTags
Category: OPM|Organization

Inputs:
  - Actors (Array<Actor>)
```

**Blueprint Usage:**
```
Button Add Tags Clicked
├── Get Selected Level Actors
├── Get Tags Text from Text Box
├── Split Tags by Comma → Tags Array
├── For Each Loop (Tags Array)
│   └── Convert String to Name → Name Array
└── ApplyTagsToActors
    ├── Actors: Selected Actors
    └── Tags: Name Array
```

### Hierarchy Management

```
Function: AttachActorsToParent
Category: OPM|Organization

Inputs:
  - Parent Actor (Actor)
  - Child Actors (Array<Actor>)

Returns: None

---

Function: DetachActorsFromParent
Category: OPM|Organization

Inputs:
  - Actors (Array<Actor>)

Returns: None
```

**Example:**
```
Button Attach to Parent Clicked
├── Get Selected Level Actors
├── Validate (Has at least 2 actors)
├── Get First Actor → Parent
├── Get Remaining Actors → Children
└── AttachActorsToParent
    ├── Parent Actor: Parent
    └── Child Actors: Children
```

### Create Parent Actor

```
Function: CreateParentActor
Category: OPM|Organization

Inputs:
  - World Context Object
  - Location (Vector)
  - Rotation (Rotator)
  - Actor Name (String)

Returns: Actor (Created parent actor)
```

## Utility Functions

### Get Actors Bounds

```
Function: GetActorsBounds
Category: OPM|Utility

Inputs:
  - Actors (Array<Actor>)

Returns:
  - Bounds Min (Vector)
  - Bounds Max (Vector)
  - Bounds Center (Vector)

Use Case: Calculate collective bounds of selection
```

### Get Actors Center

```
Function: GetActorsCenter
Category: OPM|Utility

Inputs:
  - Actors (Array<Actor>)

Returns: Vector (Center point)

Use Case: Find geometric center of selection
```

**Example:**
```
Calculate Selection Center
├── Get Selected Level Actors
├── GetActorsCenter → Center
└── Print String ("Center: {Center}")
```

## Common Patterns

### Pattern 1: Validate Selection Before Operation

```
Any Operation Button Clicked
├── Get Selected Level Actors → Selected Actors
├── Get Array Length (Selected Actors) → Count
├── Branch (Count > 0)
│   ├── True → Proceed with operation
│   └── False → Show Error Message
│       └── "Please select at least one actor"
└── Update Status Bar
```

### Pattern 2: Preview Before Apply

```
Preview Button Clicked
├── Get Selected Level Actors
├── Get Settings from UI
├── Generate Preview Names/Positions
├── Display in Preview List
└── Enable Apply Button

Apply Button Clicked
├── Get Settings from UI (same as preview)
├── Call OPM Function
└── Update Status
```

### Pattern 3: Confirmation for Destructive Operations

```
Replace/Delete Button Clicked
├── Show Confirmation Dialog
│   ├── Title: "Confirm Operation"
│   ├── Message: "This cannot be undone. Continue?"
│   └── Buttons: [Yes] [No]
├── On Yes → Proceed with operation
└── On No → Cancel and show status
```

### Pattern 4: Progress Feedback for Long Operations

```
Large Batch Operation
├── Get Selected Actors → Count
├── Branch (Count > 100)
│   ├── True → Show "Processing..." dialog
│   └── False → Process immediately
├── Perform Operation
├── Close Dialog
└── Show Result ("Processed X actors")
```

### Pattern 5: Persistent Settings

```
Event Construct
├── Load Saved Settings (from Config or Save Game)
├── Apply to UI Elements
│   ├── Set Spin Box Value
│   ├── Set Text Box Text
│   └── Set Checkbox State
└── Ready to Use

Settings Changed
├── Get Current UI Values
└── Save Settings (to Config or Save Game)
```

### Pattern 6: Real-time Selected Actor Count

```
Event Tick
├── Get Selected Level Actors
├── Get Array Length → Count
├── Format String → "X actors selected"
└── Set Text Block (Status Text)
```

### Pattern 7: Dynamic UI Based on Selection

```
Event Tick
├── Get Selected Level Actors
├── Branch (Array Length > 0)
│   ├── True → Enable Action Buttons
│   └── False → Disable Action Buttons
└── [Also update preview, counts, etc.]
```

### Pattern 8: Error Handling

```
Operation with Validation
├── Get Selected Actors
├── Validate Input
│   ├── Check Actor Class is Set
│   ├── Check Values in Range
│   └── Check Minimum Selection
├── All Valid?
│   ├── True → Execute Operation
│   │   ├── Call OPM Function
│   │   └── Show Success Message
│   └── False → Show Error
│       ├── Display Error Message
│       └── Highlight Problem Field
└── Update Status Bar
```

## Widget Communication

### Accessing Main Widget from Panel

If panels are separate widgets:

```
Panel Event
├── Get Owning Player → Player Controller
├── Get Parent Widget → Main Widget
├── Cast to EUW_OPM_Main
└── Call Custom Event on Main Widget
    └── UpdateStatusBar("Message")
```

### Sharing Data Between Panels

Use the main widget as a data hub:

```
Main Widget Variables:
├── Current Settings (Struct)
├── Last Operation Result (Struct)
└── User Preferences (Struct)

Panel Access:
├── Get Main Widget
└── Get/Set Variables
```

## Performance Tips

### For Large Selections (100+ actors):

1. **Show Progress Indicator**
```
Before Operation
└── Show Progress Bar Widget

After Operation
└── Hide Progress Bar Widget
```

2. **Process in Chunks** (if supported by function)
```
Large Array of Actors
├── Split into Chunks (25 actors each)
├── For Each Chunk
│   ├── Process Chunk
│   └── Update Progress
└── Complete
```

3. **Disable Live Updates**
```
Before Operation
├── Disable Event Tick
├── Process Everything
└── Re-enable Event Tick
```

## Debugging Tips

### Print Debug Information

```
Debug Node
├── Get Selected Actors → Actors
├── Print String ("Count: {Length}")
├── For Each Loop
│   └── Print Actor Name
└── Print "Done"
```

### Verify Function Calls

```
Call OPM Function
├── Before: Print "Calling function..."
├── Execute Function
│   └── On Return: Check return value
└── After: Print "Function complete"
```

### Check World Context

```
Get Editor World
├── Is Valid?
│   ├── True → Use for operations
│   └── False → Show error
└── Print World Name (for verification)
```

## Version Compatibility

This API reference is for **OPM v1.0**

- Unreal Engine: 5.3+
- All functions support undo/redo
- Thread-safe: No (call from Game Thread only)
- Editor-only: Yes (not available in packaged games)

## Additional Resources

- **Full C++ API**: See header files in `Plugins/OPM/Source/OPM/Public/`
- **Usage Examples**: See `USAGE_EXAMPLES.md` in plugin root
- **Implementation Guide**: See `UI_IMPLEMENTATION_GUIDE.md`
- **Support**: GitHub Issues at https://github.com/Mittenzx/OPM

---

**Happy UI Development!**
