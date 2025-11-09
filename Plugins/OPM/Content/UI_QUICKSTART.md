# OPM UI Quick Start Guide

Get your OPM Editor Utility Widget UI up and running in 30 minutes!

## Prerequisites

✅ Unreal Engine 5.3+ installed  
✅ OPM Plugin enabled in your project  
✅ Basic knowledge of UMG and Blueprints

## Quick Start Steps

### Step 1: Create the Main Widget (5 minutes)

1. Open your project in Unreal Engine
2. In Content Browser, navigate to `Content/OPM/UI` (create folders if they don't exist)
3. Right-click → `Editor Utilities → Editor Utility Widget`
4. Name it `EUW_OPM_Main`
5. Double-click to open

### Step 2: Build Basic Layout (10 minutes)

Add these widgets to create a simple tabbed interface:

```
Canvas Panel (Root)
└── Vertical Box
    ├── Text Block (Title: "Object Placement Manager")
    ├── Border (Tab Content Area)
    │   └── Widget Switcher (Name: "Switcher_Panels")
    │       ├── Vertical Box (Placement Panel)
    │       ├── Vertical Box (Alignment Panel)
    │       └── Vertical Box (Naming Panel)
    ├── Horizontal Box (Tab Buttons)
    │   ├── Button (Name: "Btn_Placement", Text: "Placement")
    │   ├── Button (Name: "Btn_Alignment", Text: "Alignment")
    │   └── Button (Name: "Btn_Naming", Text: "Naming")
    └── Text Block (Name: "Txt_Status", Text: "Ready")
```

**Quick Setup:**
- Set Canvas Panel anchors to full screen
- Set Vertical Box fill to vertical
- Set Tab Content Border to fill remaining space

### Step 3: Add Tab Switching Logic (5 minutes)

In the Event Graph:

1. Select `Btn_Placement` in Designer
2. In Details → Events, click `+` next to OnClicked
3. Add this logic:

```
Btn_Placement OnClicked
└── Set Active Widget Index (Switcher_Panels, Index: 0)
```

Repeat for other tabs with indices 1, 2, etc.

### Step 4: Create Placement Panel (5 minutes)

In the Designer, select the Placement Panel (Vertical Box at index 0):

Add these widgets:

```
Vertical Box (Placement Panel)
├── Text Block ("Select actors to place:")
├── Combo Box String (Name: "CB_PatternType")
├── Spin Box (Name: "SB_Rows", Default: 5)
├── Spin Box (Name: "SB_Columns", Default: 5)
├── Spin Box (Name: "SB_Spacing", Default: 200)
└── Button (Name: "Btn_PlaceGrid", Text: "Place Grid")
```

### Step 5: Connect to OPM API (5 minutes)

1. Select `Btn_PlaceGrid` in Designer
2. Add OnClicked event
3. Add this Blueprint logic:

```
Btn_PlaceGrid OnClicked
├── Get Editor World → World Context
├── Get Class (StaticMeshActor) → Actor Class
├── Get SB_Rows Value → Rows
├── Get SB_Columns Value → Columns
├── Get SB_Spacing Value → Spacing
├── Make Vector (X:Spacing, Y:Spacing, Z:0) → Spacing Vector
├── Get Actor Iterator First Selected Actor Location → Origin
└── OPM Blueprint Library → PlaceActorsInGrid
    ├── World Context: World Context
    ├── Actor Class: Actor Class
    ├── Rows: Rows
    ├── Columns: Columns
    ├── Spacing X: Spacing
    ├── Spacing Y: Spacing
    ├── Spacing Z: 0
    ├── Origin Location: Origin
    └── Origin Rotation: (0,0,0)
```

**Simplified Version (Just to test):**
```
Btn_PlaceGrid OnClicked
└── OPM Blueprint Library → PlaceActorsInGrid
    ├── World Context: Get Editor World
    ├── Actor Class: StaticMeshActor (hardcoded)
    ├── Rows: 5
    ├── Columns: 5
    ├── Spacing X/Y/Z: 200.0
    ├── Origin Location: (0, 0, 0)
    └── Origin Rotation: (0, 0, 0)
```

### Step 6: Test It! (1 minute)

1. Click "Compile" and "Save"
2. Close the widget editor
3. In Content Browser, right-click `EUW_OPM_Main`
4. Select "Run Editor Utility Widget"
5. Click "Place Grid" button
6. See actors appear in your level!

## Next Steps

Now that you have a working prototype:

### Enhance Placement Panel
- Add more pattern options (Circular, Line, Random)
- Add actor class picker
- Add preview mode
- Add reset button

### Create Alignment Panel
Add simple alignment buttons:

```
Alignment Panel
├── Button ("Align Left")
├── Button ("Align Center")
├── Button ("Align Right")
└── Button ("Distribute Evenly")
```

Connect each to OPM alignment functions:
```
Btn_AlignLeft OnClicked
├── Get Selected Level Actors
└── OPM Blueprint Library → AlignActorsLeft
```

### Create Naming Panel
Add naming tools:

```
Naming Panel
├── Text Box (Name: "TB_Prefix")
├── Text Box (Name: "TB_Suffix")
├── Spin Box (Name: "SB_StartNumber")
└── Button (Name: "Btn_Rename")
```

Connect to OPM:
```
Btn_Rename OnClicked
├── Get Selected Level Actors
├── Get TB_Prefix Text
├── Get TB_Suffix Text
├── Get SB_StartNumber Value
└── OPM Blueprint Library → BatchRename
```

## Common Issues & Solutions

### "Function not found in OPM Blueprint Library"
- **Solution:** Make sure OPM plugin is enabled and compiled
- Check Edit → Plugins → OPM (should have checkmark)
- Restart editor if needed

### "No actors placed" / "Nothing happens"
- **Solution:** Check World Context is valid
- Use "Get Editor World" node, not "Get World"
- Print debug messages to verify function is called

### "Actors placed in wrong location"
- **Solution:** Check Origin Location parameter
- Use (0,0,0) for world origin
- Or get location from selected actor

### Widget doesn't appear in Tools menu
- **Solution:** Make sure you created an "Editor Utility Widget", not a regular Widget Blueprint
- The asset icon should be different (blue wrench symbol)

### Undo doesn't work
- **Solution:** This should work automatically
- If not, OPM plugin may not be loaded properly
- Check log for errors

## Tips & Tricks

### Quick Testing
- Don't worry about perfect UI initially
- Focus on functionality first
- Use hardcoded values to test quickly
- Polish later

### Debugging
Add Print String nodes after each step:
```
Any Node
└── Print String ("Step completed: {NodeName}")
```

### Actor Class Selection
For quick testing, use these common classes:
- `StaticMeshActor` - For static meshes
- `PointLight` - For lights
- `PlayerStart` - For spawn points
- `TriggerBox` - For volumes

### Reusable Patterns

**Get Selected or Use Default:**
```
Get Selected Actors
├── Branch (Array Length > 0)
│   ├── True → Get First Actor Location → Origin
│   └── False → Use (0, 0, 0) → Origin
```

**Validate Before Operation:**
```
Button Clicked
├── Get Value from Spin Box
├── Branch (Value > 0 AND Value < 100)
│   ├── True → Execute Operation
│   └── False → Show Error Message
```

### Performance
For testing, keep values reasonable:
- Grid: Max 10x10 (100 actors)
- Circular: Max 50 actors
- Random: Max 100 actors

Larger values work but may be slow during testing.

## Resources

### Documentation
- **Full UI Guide:** `UI_IMPLEMENTATION_GUIDE.md`
- **Blueprint API:** `BLUEPRINT_API_REFERENCE.md`
- **Usage Examples:** `../USAGE_EXAMPLES.md`

### Help
- **GitHub Issues:** https://github.com/Mittenzx/OPM/issues
- **UE Documentation:** https://docs.unrealengine.com/umg
- **Blueprint Reference:** https://docs.unrealengine.com/blueprints

## Example Layouts

### Minimal Placement UI (1 button)
```
Button: "Place 5x5 Grid"
└── Calls PlaceActorsInGrid with hardcoded values
```
**Time to create:** 2 minutes  
**Complexity:** Beginner

### Basic Placement UI (Pattern selection)
```
Combo Box: Pattern Type (Grid/Circle/Line)
Spin Boxes: Parameters (rows, columns, spacing, etc.)
Button: Place Actors
```
**Time to create:** 15 minutes  
**Complexity:** Beginner

### Complete Placement Panel (Full featured)
```
Pattern Selection with Dynamic Settings
Actor Class Picker
Preview Mode Toggle
Place/Reset Buttons
Status Messages
```
**Time to create:** 1-2 hours  
**Complexity:** Intermediate

### Full OPM Interface (All features)
```
Tabbed Interface
5 Feature Panels
Persistent Settings
Keyboard Shortcuts
Help Integration
```
**Time to create:** 4-8 hours  
**Complexity:** Advanced

## Quick Reference Card

### Most Common OPM Functions

```
// Placement
PlaceActorsInGrid(World, Class, Rows, Cols, SpacingX, SpacingY, SpacingZ, Origin, Rotation)
PlaceActorsInCircularPattern(World, Class, Count, Radius, StartAngle, Height, Center, Rotation)

// Alignment
AlignActorsLeft(Actors)
AlignActorsRight(Actors)
CenterActorsX(Actors)
DistributeActorsHorizontally(Actors)
SnapActorsToGrid(Actors, GridSize)

// Naming
BatchRename(Actors, Prefix, Suffix, StartNumber, Padding)
FindAndReplace(Actors, FindText, ReplaceText, CaseSensitive)

// Replacement
BatchReplaceActors(World, OriginalActors, NewClass, PreserveTransform, PreserveAttachments)

// Organization
SetActorFolder(Actors, FolderPath)
ApplyTagsToActors(Actors, Tags)
GroupActorsByType(Actors)
```

### Most Common UMG Widgets

```
// Input
Spin Box - Numeric input with slider
Text Box - Text input
Combo Box String - Dropdown selection
Check Box - Boolean toggle
Button - Clickable action

// Layout
Vertical Box - Stack vertically
Horizontal Box - Stack horizontally
Canvas Panel - Free positioning
Widget Switcher - Show one of many
Border - Background/spacing
```

### Essential Blueprint Nodes

```
// Editor Functions
Get Selected Level Actors - Get selection
Get Editor World - Get editor world context

// OPM Functions
(See functions above, under OPM category)

// UI Functions
Set Text - Update text blocks
Get Value (Spin Box) - Read numeric input
Get Text (Text Box) - Read text input
Set Active Widget Index - Switch tabs
```

---

## Success Checklist

After following this guide, you should have:

- ✅ Working Editor Utility Widget
- ✅ Basic tabbed interface
- ✅ At least one working placement function
- ✅ Understanding of how to connect UI to OPM API
- ✅ Foundation for building complete UI

**Time invested:** ~30 minutes  
**Result:** Working OPM UI prototype!

## What's Next?

1. **Expand functionality** - Add more features to each panel
2. **Polish UI** - Improve layout and styling
3. **Add validation** - Check inputs before operations
4. **Implement presets** - Save/load common settings
5. **Create help** - Add tooltips and documentation
6. **Test thoroughly** - Try different scenarios
7. **Get feedback** - Share with team/community

**Happy UI building!** 🎨🚀
