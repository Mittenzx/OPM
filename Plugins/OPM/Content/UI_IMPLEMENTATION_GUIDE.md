# Editor Utility Widget Implementation Guide

This guide provides step-by-step instructions for creating the OPM Editor Utility Widgets in Unreal Engine.

## Prerequisites

- Unreal Engine 5.3 or higher installed
- OPM plugin enabled in your project
- Basic knowledge of UMG (Unreal Motion Graphics) and Blueprints

## Part 1: Main Widget (EUW_OPM_Main)

### Step 1: Create the Main Editor Utility Widget

1. In the Content Browser, navigate to `Plugins/OPM/Content/UI`
2. Right-click and select `Editor Utilities > Editor Utility Widget`
3. Name it `EUW_OPM_Main`

### Step 2: Design the Main Interface

Open `EUW_OPM_Main` and add the following widget hierarchy:

```
Canvas Panel (Root)
└── Vertical Box (VBox_Main)
    ├── Horizontal Box (HBox_Header)
    │   ├── Text Block (Title: "Object Placement Manager")
    │   └── Button (Btn_Help)
    ├── Widget Switcher (Switcher_Panels)
    │   ├── Scroll Box (Panel_Placement)
    │   ├── Scroll Box (Panel_Alignment)
    │   ├── Scroll Box (Panel_Naming)
    │   ├── Scroll Box (Panel_Replacement)
    │   └── Scroll Box (Panel_Organization)
    ├── Horizontal Box (HBox_TabBar)
    │   ├── Button (Btn_Placement)
    │   ├── Button (Btn_Alignment)
    │   ├── Button (Btn_Naming)
    │   ├── Button (Btn_Replacement)
    │   └── Button (Btn_Organization)
    └── Border (StatusBar)
        └── Text Block (Txt_Status)
```

### Step 3: Configure Widget Properties

**Canvas Panel:**
- Fill Screen: Enabled
- Anchors: Full Screen

**VBox_Main:**
- Padding: 10px all sides
- Fill: Vertical alignment

**Title Text:**
- Text: "Object Placement Manager v1.0"
- Font Size: 24
- Font Style: Bold
- Justification: Center

**Tab Buttons:**
- Size: 120x40
- Padding: 5px
- Colors: 
  - Normal: (0.1, 0.1, 0.1, 1.0)
  - Hovered: (0.2, 0.2, 0.2, 1.0)
  - Pressed: (0.05, 0.05, 0.05, 1.0)

**Status Bar:**
- Height: 30px
- Background: (0.05, 0.05, 0.05, 1.0)
- Text Color: (0.7, 0.7, 0.7, 1.0)

### Step 4: Add Blueprint Logic

In the Event Graph, add the following logic:

**Event Construct:**
```
Event Construct
├── Set Active Widget Index (Switcher_Panels, 0)
└── Set Status Text ("Ready")
```

**Tab Button Click Events:**
```
Btn_Placement OnClicked
└── Set Active Widget Index (Switcher_Panels, 0)
    └── Update Tab Visual State

Btn_Alignment OnClicked
└── Set Active Widget Index (Switcher_Panels, 1)
    └── Update Tab Visual State

[... similar for other tabs]
```

**Helper Functions:**

Create a function `UpdateTabVisualState`:
- Input: Tab Index (Integer)
- Logic: Highlight active tab, dim inactive tabs

## Part 2: Placement Panel (Panel_Placement)

### Widget Hierarchy

```
Scroll Box (Panel_Placement)
└── Vertical Box
    ├── Text Block (Header: "Placement Patterns")
    ├── Combo Box String (CB_PatternType)
    │   Options: ["Grid", "Circular", "Line", "Random"]
    ├── Widget Switcher (Switcher_PatternSettings)
    │   ├── Vertical Box (Settings_Grid)
    │   │   ├── Horizontal Box
    │   │   │   ├── Text Block ("Rows:")
    │   │   │   └── Spin Box (SB_GridRows)
    │   │   ├── Horizontal Box
    │   │   │   ├── Text Block ("Columns:")
    │   │   │   └── Spin Box (SB_GridColumns)
    │   │   ├── Horizontal Box
    │   │   │   ├── Text Block ("Spacing X:")
    │   │   │   └── Spin Box (SB_SpacingX)
    │   │   ├── Horizontal Box
    │   │   │   ├── Text Block ("Spacing Y:")
    │   │   │   └── Spin Box (SB_SpacingY)
    │   │   └── Horizontal Box
    │   │       ├── Text Block ("Spacing Z:")
    │   │       └── Spin Box (SB_SpacingZ)
    │   ├── Vertical Box (Settings_Circular)
    │   │   ├── Horizontal Box
    │   │   │   ├── Text Block ("Radius:")
    │   │   │   └── Spin Box (SB_CircRadius)
    │   │   ├── Horizontal Box
    │   │   │   ├── Text Block ("Count:")
    │   │   │   └── Spin Box (SB_CircCount)
    │   │   ├── Horizontal Box
    │   │   │   ├── Text Block ("Start Angle:")
    │   │   │   └── Spin Box (SB_StartAngle)
    │   │   └── Horizontal Box
    │   │       ├── Text Block ("Height:")
    │   │       └── Spin Box (SB_CircHeight)
    │   ├── Vertical Box (Settings_Line)
    │   │   └── [Similar layout for line settings]
    │   └── Vertical Box (Settings_Random)
    │       └── [Similar layout for random settings]
    ├── Spacer (Height: 20)
    ├── Text Block (Header: "Actor Selection")
    ├── Class Picker (ClassPicker_Actor)
    ├── Spacer (Height: 20)
    ├── Check Box (CB_ShowPreview)
    │   └── Text Block ("Show Preview")
    ├── Spacer (Height: 20)
    └── Horizontal Box (ActionButtons)
        ├── Button (Btn_Place)
        │   └── Text Block ("Place Actors")
        ├── Spacer (Width: 10)
        └── Button (Btn_Reset)
            └── Text Block ("Reset")
```

### Widget Configuration

**Spin Boxes:**
- Min Value: 1 (for counts), -10000 (for spacing)
- Max Value: 100 (for counts), 10000 (for spacing)
- Default: 5 (for counts), 100 (for spacing)
- Slider Visible: Yes
- Keyboard Step: 1
- Mouse Step: 0.1

**Class Picker:**
- Allowed Class: Actor
- Show None: No

**Buttons:**
- Place Button:
  - Color: Green tint (0.2, 0.8, 0.2, 1.0)
  - Size: 150x40
- Reset Button:
  - Color: Red tint (0.8, 0.2, 0.2, 1.0)
  - Size: 100x40

### Blueprint Logic

**CB_PatternType OnSelectionChanged:**
```
OnSelectionChanged
├── Get Selected Option
└── Branch (Check Pattern Type)
    ├── "Grid" → Set Active Widget Index (Switcher_PatternSettings, 0)
    ├── "Circular" → Set Active Widget Index (Switcher_PatternSettings, 1)
    ├── "Line" → Set Active Widget Index (Switcher_PatternSettings, 2)
    └── "Random" → Set Active Widget Index (Switcher_PatternSettings, 3)
```

**Btn_Place OnClicked:**
```
OnClicked
├── Get World Context
├── Get Selected Actor Class (ClassPicker_Actor)
├── Validate Selection (Branch: Is Valid?)
│   ├── False → Show Error ("Please select an actor class")
│   └── True → Continue
├── Get Pattern Type (CB_PatternType)
├── Branch (Check Pattern Type)
│   ├── "Grid" → Call PlaceActorsInGrid
│   │   ├── Get Values: SB_GridRows, SB_GridColumns
│   │   ├── Get Spacing: SB_SpacingX, SB_SpacingY, SB_SpacingZ
│   │   └── Call: OPM Blueprint Library > PlaceActorsInGrid
│   ├── "Circular" → Call PlaceActorsInCircularPattern
│   │   ├── Get Values: SB_CircRadius, SB_CircCount, SB_StartAngle
│   │   └── Call: OPM Blueprint Library > PlaceActorsInCircularPattern
│   ├── "Line" → Call PlaceActorsInLine
│   └── "Random" → Call PlaceActorsRandomly
└── Update Status ("Actors placed successfully")
```

**Btn_Reset OnClicked:**
```
OnClicked
├── Reset All Spin Boxes to Default
├── Reset Pattern Selection to "Grid"
└── Update Status ("Settings reset")
```

## Part 3: Alignment Panel (Panel_Alignment)

### Widget Hierarchy

```
Scroll Box (Panel_Alignment)
└── Vertical Box
    ├── Text Block (Header: "Alignment Tools")
    ├── Text Block (Instruction: "Select actors in viewport, then choose alignment")
    ├── Spacer (Height: 20)
    ├── Text Block (Subheader: "Horizontal Alignment")
    ├── Horizontal Box (Align_Horizontal)
    │   ├── Button (Btn_AlignLeft)
    │   │   └── Text Block ("← Left")
    │   ├── Button (Btn_AlignCenterX)
    │   │   └── Text Block ("⊙ Center")
    │   └── Button (Btn_AlignRight)
    │       └── Text Block ("Right →")
    ├── Spacer (Height: 10)
    ├── Text Block (Subheader: "Vertical Alignment")
    ├── Horizontal Box (Align_Vertical)
    │   ├── Button (Btn_AlignFront)
    │   │   └── Text Block ("↑ Front")
    │   ├── Button (Btn_AlignCenterY)
    │   │   └── Text Block ("⊙ Center")
    │   └── Button (Btn_AlignBack)
    │       └── Text Block ("↓ Back")
    ├── Spacer (Height: 10)
    ├── Text Block (Subheader: "Height Alignment")
    ├── Horizontal Box (Align_Height)
    │   ├── Button (Btn_AlignBottom)
    │   │   └── Text Block ("⊥ Bottom")
    │   ├── Button (Btn_AlignCenterZ)
    │   │   └── Text Block ("⊙ Center")
    │   └── Button (Btn_AlignTop)
    │       └── Text Block ("⊤ Top")
    ├── Spacer (Height: 30)
    ├── Text Block (Header: "Distribution Tools")
    ├── Horizontal Box (Distribution)
    │   ├── Button (Btn_DistributeHorizontal)
    │   │   └── Text Block ("⟷ Distribute Horizontal")
    │   └── Button (Btn_DistributeVertical)
    │       └── Text Block ("⟺ Distribute Vertical")
    ├── Spacer (Height: 30)
    ├── Text Block (Header: "Grid Snap")
    ├── Horizontal Box (GridSnap)
    │   ├── Text Block ("Grid Size:")
    │   ├── Spin Box (SB_GridSize)
    │   └── Button (Btn_SnapToGrid)
    │       └── Text Block ("Snap to Grid")
    └── Text Block (Txt_SelectedCount)
        └── Text: "0 actors selected"
```

### Widget Configuration

**Alignment Buttons:**
- Size: 100x60
- Font Size: 14
- Uniform size for consistent grid layout

**Distribution Buttons:**
- Size: 150x40
- Color: Blue tint (0.2, 0.5, 0.8, 1.0)

**Grid Size Spin Box:**
- Min: 1
- Max: 1000
- Default: 100
- Increment: 10

### Blueprint Logic

**Event Tick:**
```
Event Tick
├── Get Selected Actors (Editor Utility Library)
├── Get Array Length
└── Set Text (Txt_SelectedCount, "X actors selected")
```

**Btn_AlignLeft OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Validate (Has Selected Actors?)
│   ├── False → Show Warning ("No actors selected")
│   └── True → Continue
├── Call: OPM Blueprint Library > AlignActorsLeft
│   └── Input: Selected Actors Array
└── Update Status ("Actors aligned left")
```

**[Similar logic for all alignment buttons]**

**Btn_SnapToGrid OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Get Grid Size (SB_GridSize)
├── For Each Loop (Selected Actors)
│   └── Call: OPM Blueprint Library > SnapActorToGrid
│       ├── Actor: Loop Body
│       └── Grid Size: SB_GridSize Value
└── Update Status ("Actors snapped to grid")
```

## Part 4: Naming Panel (Panel_Naming)

### Widget Hierarchy

```
Scroll Box (Panel_Naming)
└── Vertical Box
    ├── Text Block (Header: "Batch Rename Tools")
    ├── Spacer (Height: 10)
    ├── Horizontal Box
    │   ├── Text Block ("Prefix:")
    │   └── Editable Text Box (TB_Prefix)
    ├── Horizontal Box
    │   ├── Text Block ("Suffix:")
    │   └── Editable Text Box (TB_Suffix)
    ├── Spacer (Height: 10)
    ├── Text Block (Subheader: "Numbering")
    ├── Horizontal Box
    │   ├── Check Box (CB_AddNumbers)
    │   │   └── Text Block ("Add Numbers")
    │   ├── Text Block ("Start:")
    │   ├── Spin Box (SB_StartNumber)
    │   ├── Text Block ("Padding:")
    │   └── Spin Box (SB_Padding)
    ├── Spacer (Height: 20)
    ├── Text Block (Subheader: "Find and Replace")
    ├── Horizontal Box
    │   ├── Text Block ("Find:")
    │   └── Editable Text Box (TB_FindText)
    ├── Horizontal Box
    │   ├── Text Block ("Replace:")
    │   └── Editable Text Box (TB_ReplaceText)
    ├── Check Box (CB_CaseSensitive)
    │   └── Text Block ("Case Sensitive")
    ├── Spacer (Height: 30)
    ├── Text Block (Header: "Preview")
    ├── Border (PreviewBorder)
    │   └── Scroll Box (Preview_Scroll)
    │       └── Vertical Box (VB_PreviewList)
    │           └── [Dynamic preview items]
    ├── Spacer (Height: 20)
    └── Horizontal Box (ActionButtons)
        ├── Button (Btn_Preview)
        │   └── Text Block ("Preview Changes")
        ├── Button (Btn_Apply)
        │   └── Text Block ("Apply Changes")
        └── Button (Btn_ResetNaming)
            └── Text Block ("Reset")
```

### Widget Configuration

**Text Boxes:**
- Hint Text: Provide guidance (e.g., "Enter prefix...")
- Min Desired Width: 200

**Spin Boxes (Numbering):**
- Start Number: 
  - Min: 0, Max: 9999, Default: 1
- Padding:
  - Min: 0, Max: 10, Default: 2

**Preview Border:**
- Min Height: 150px
- Max Height: 300px
- Background: Dark gray (0.1, 0.1, 0.1, 1.0)

**Buttons:**
- Preview: Blue tint
- Apply: Green tint
- Reset: Red tint

### Blueprint Logic

**Btn_Preview OnClicked:**
```
OnClicked
├── Clear Preview List (VB_PreviewList)
├── Get Selected Actors
├── For Each Loop (Selected Actors)
│   ├── Get Current Name
│   ├── Generate New Name
│   │   ├── Add Prefix (if not empty)
│   │   ├── Keep Base Name
│   │   ├── Add Number (if CB_AddNumbers is checked)
│   │   │   └── Format with Padding
│   │   └── Add Suffix (if not empty)
│   └── Add Preview Item to List
│       ├── Text: "Current Name → New Name"
│       └── Color code: Green for changed, Gray for unchanged
└── Update Status ("Preview generated")
```

**Btn_Apply OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Validate (Has Actors?)
│   ├── False → Show Warning
│   └── True → Continue
├── Get Naming Parameters
│   ├── Prefix: TB_Prefix Text
│   ├── Suffix: TB_Suffix Text
│   ├── Start Number: SB_StartNumber Value
│   ├── Padding: SB_Padding Value
│   └── Add Numbers: CB_AddNumbers State
├── Branch (Check Operation Type)
│   ├── Has Prefix/Suffix/Numbers?
│   │   └── Call: OPM Blueprint Library > BatchRename
│   │       ├── Actors: Selected Actors
│   │       ├── Prefix: TB_Prefix Text
│   │       ├── Suffix: TB_Suffix Text
│   │       ├── Start Number: SB_StartNumber Value
│   │       └── Number Padding: SB_Padding Value
│   └── Has Find/Replace Text?
│       └── Call: OPM Blueprint Library > FindAndReplace
│           ├── Actors: Selected Actors
│           ├── Find: TB_FindText Text
│           ├── Replace: TB_ReplaceText Text
│           └── Case Sensitive: CB_CaseSensitive State
└── Update Status ("Actors renamed successfully")
    └── Refresh Preview
```

**Btn_ResetNaming OnClicked:**
```
OnClicked
├── Clear All Text Boxes
├── Reset Checkboxes
├── Reset Spin Boxes to Default
├── Clear Preview List
└── Update Status ("Settings reset")
```

**Custom Function: Generate Preview Name**
```
Input: Actor (Object Reference), Settings (Struct)
Output: Preview Name (String)

Logic:
├── Get Actor Label
├── Apply Find/Replace (if applicable)
├── Prepend Prefix (if not empty)
├── Append Number (if CB_AddNumbers)
│   └── Format: PadLeft(Number, Padding, '0')
└── Append Suffix (if not empty)
```

## Part 5: Replacement Panel (Panel_Replacement)

### Widget Hierarchy

```
Scroll Box (Panel_Replacement)
└── Vertical Box
    ├── Text Block (Header: "Actor Replacement")
    ├── Text Block (Instruction: "Select actors to replace, choose new actor class")
    ├── Spacer (Height: 20)
    ├── Text Block (Subheader: "Target Actor Class")
    ├── Class Picker (ClassPicker_NewActor)
    ├── Spacer (Height: 20)
    ├── Text Block (Subheader: "Preservation Options")
    ├── Check Box (CB_PreserveTransform)
    │   └── Text Block ("Preserve Transform (Location, Rotation, Scale)")
    ├── Check Box (CB_PreserveTags)
    │   └── Text Block ("Preserve Actor Tags")
    ├── Check Box (CB_PreserveAttachments)
    │   └── Text Block ("Preserve Child Attachments")
    ├── Spacer (Height: 30)
    ├── Text Block (Header: "Selected Actors")
    ├── Border (SelectedActorsBorder)
    │   └── Scroll Box
    │       └── Vertical Box (VB_SelectedList)
    │           └── [Dynamic list of selected actors]
    ├── Spacer (Height: 20)
    └── Horizontal Box (ActionButtons)
        ├── Button (Btn_Replace)
        │   └── Text Block ("Replace Actors")
        └── Button (Btn_CancelReplace)
            └── Text Block ("Cancel")
```

### Widget Configuration

**Class Picker:**
- Allowed Class: AActor
- Show None: No
- Required Selection

**Check Boxes:**
- Default State: Checked (preserve everything by default)
- Spacing: 5px between items

**Selected Actors List:**
- Max Height: 200px
- Scrollable
- Shows actor name and class

**Replace Button:**
- Size: 150x50
- Color: Orange/Yellow (Warning color)
- Requires confirmation

### Blueprint Logic

**Event Tick:**
```
Event Tick
├── Get Selected Actors
├── Clear List (VB_SelectedList)
└── For Each Loop (Selected Actors)
    └── Add Text Block to VB_SelectedList
        └── Text: "Actor Name (Class Name)"
```

**Btn_Replace OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Validate Selection
│   ├── Has Selected Actors? (Branch)
│   │   ├── False → Show Error ("No actors selected")
│   │   └── True → Continue
│   └── Has New Actor Class? (Branch)
│       ├── False → Show Error ("Please select target actor class")
│       └── True → Continue
├── Show Confirmation Dialog
│   └── Message: "Replace X actors? This cannot be undone."
│   └── Buttons: [Yes] [No]
├── On Confirmed (Yes clicked)
│   ├── Get Parameters
│   │   ├── New Class: ClassPicker_NewActor Selection
│   │   ├── Preserve Transform: CB_PreserveTransform State
│   │   ├── Preserve Tags: CB_PreserveTags State
│   │   └── Preserve Attachments: CB_PreserveAttachments State
│   ├── Call: OPM Blueprint Library > BatchReplaceActors
│   │   ├── Actors: Selected Actors
│   │   ├── New Actor Class: New Class
│   │   ├── Preserve Transform: Preserve Transform
│   │   └── Preserve Attachments: Preserve Attachments
│   └── Update Status ("X actors replaced successfully")
└── On Cancelled (No clicked)
    └── Update Status ("Replacement cancelled")
```

**Custom Function: Create Confirmation Dialog**
```
Create Widget (WBP_ConfirmDialog)
├── Set Message Text
├── Bind Yes Button → On Confirmed Event
├── Bind No Button → On Cancelled Event
└── Add to Viewport (Modal)
```

## Part 6: Organization Panel (Panel_Organization)

### Widget Hierarchy

```
Scroll Box (Panel_Organization)
└── Vertical Box
    ├── Text Block (Header: "Level Organization Tools")
    ├── Spacer (Height: 10)
    ├── Text Block (Subheader: "Folder Management")
    ├── Horizontal Box
    │   ├── Text Block ("Folder Path:")
    │   └── Editable Text Box (TB_FolderPath)
    ├── Button (Btn_SetFolder)
    │   └── Text Block ("Move to Folder")
    ├── Spacer (Height: 20)
    ├── Text Block (Subheader: "Tag Management")
    ├── Horizontal Box
    │   ├── Text Block ("Tags:")
    │   └── Editable Text Box (TB_Tags)
    │       └── Hint: "Comma-separated tags"
    ├── Horizontal Box (TagButtons)
    │   ├── Button (Btn_AddTags)
    │   │   └── Text Block ("Add Tags")
    │   ├── Button (Btn_RemoveTags)
    │   │   └── Text Block ("Remove Tags")
    │   └── Button (Btn_ClearTags)
    │       └── Text Block ("Clear All Tags")
    ├── Spacer (Height: 20)
    ├── Text Block (Subheader: "Hierarchy Management")
    ├── Button (Btn_GroupByType)
    │   └── Text Block ("Group Selected by Type")
    ├── Horizontal Box
    │   ├── Button (Btn_AttachToParent)
    │   │   └── Text Block ("Attach to Parent")
    │   └── Button (Btn_DetachFromParent)
    │       └── Text Block ("Detach from Parent")
    ├── Spacer (Height: 20)
    ├── Text Block (Subheader: "Quick Actions")
    └── Wrap Box (QuickActions)
        ├── Button (Btn_GroupAll)
        │   └── Text Block ("Create Group")
        └── Button (Btn_Organize)
            └── Text Block ("Auto Organize")
```

### Widget Configuration

**Text Boxes:**
- TB_FolderPath:
  - Hint: "e.g., /Environment/Props"
  - Min Width: 250
- TB_Tags:
  - Hint: "tag1, tag2, tag3"
  - Min Width: 250

**Buttons:**
- Consistent sizing: 120x30
- Color coding:
  - Add operations: Green
  - Remove operations: Red
  - Modify operations: Blue

### Blueprint Logic

**Btn_SetFolder OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Validate Selection
├── Get Folder Path (TB_FolderPath Text)
├── Validate Folder Path (not empty)
├── Call: OPM Blueprint Library > SetActorFolder
│   ├── Actors: Selected Actors
│   └── Folder Path: TB_FolderPath Text
└── Update Status ("Actors moved to folder")
```

**Btn_AddTags OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Get Tags Text (TB_Tags)
├── Parse Tags (Split by comma, trim whitespace)
│   └── Result: Array of Tag Names
├── Call: OPM Blueprint Library > ApplyTagsToActors
│   ├── Actors: Selected Actors
│   └── Tags: Parsed Tags Array
└── Update Status ("Tags added to X actors")
```

**Btn_RemoveTags OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Get Tags Text (TB_Tags)
├── Parse Tags
├── Call: OPM Blueprint Library > RemoveTagsFromActors
│   ├── Actors: Selected Actors
│   └── Tags: Parsed Tags Array
└── Update Status ("Tags removed from X actors")
```

**Btn_ClearTags OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Show Confirmation ("Clear all tags from selected actors?")
├── On Confirmed
│   ├── Call: OPM Blueprint Library > ClearActorTags
│   │   └── Actors: Selected Actors
│   └── Update Status ("Tags cleared")
└── On Cancelled
    └── Update Status ("Operation cancelled")
```

**Btn_GroupByType OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Call: OPM Blueprint Library > GroupActorsByType
│   └── Actors: Selected Actors
└── Update Status ("Actors grouped by type")
```

**Btn_AttachToParent OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Validate (Has at least 2 actors selected?)
│   ├── False → Show Error ("Select at least 2 actors")
│   └── True → Continue
├── Get First Actor (Parent)
├── Get Remaining Actors (Children)
├── Call: OPM Blueprint Library > AttachActorsToParent
│   ├── Parent: First Actor
│   └── Children: Remaining Actors
└── Update Status ("Actors attached")
```

**Btn_AutoOrganize OnClicked:**
```
OnClicked
├── Get Selected Actors
├── Show Options Dialog
│   ├── Organize by Type
│   ├── Organize by Layer
│   └── Organize by Tags
├── Based on Selection
│   ├── Call GroupActorsByType
│   ├── Apply naming conventions
│   └── Set appropriate folders
└── Update Status ("Auto-organization complete")
```

## Part 7: Opening the Main Widget

### Method 1: From Tools Menu

1. In the Editor, go to `Tools > Blutilities > Object Placement Manager`
2. The EUW_OPM_Main widget will open as a floating window

### Method 2: From Content Browser

1. Navigate to `Plugins/OPM/Content/UI`
2. Double-click `EUW_OPM_Main`
3. The widget opens in edit mode
4. Click "Run" to execute the widget

### Method 3: Create Shortcut (Optional)

Add a toolbar button:
1. Edit > Editor Preferences
2. Search for "Editor Utility Widget"
3. Add `EUW_OPM_Main` to the toolbar
4. Click the new button to launch

## Part 8: Testing Checklist

### Placement Panel Tests
- [ ] Grid pattern generates correct number of actors
- [ ] Circular pattern respects radius and angle
- [ ] Line pattern spaces actors evenly
- [ ] Random pattern stays within bounds
- [ ] Preview mode works correctly
- [ ] Reset button clears all settings

### Alignment Panel Tests
- [ ] All 9 alignment buttons work (3x3 grid)
- [ ] Distribution creates even spacing
- [ ] Snap to grid rounds to nearest grid point
- [ ] Selected actor count updates in real-time
- [ ] Works with different actor types

### Naming Panel Tests
- [ ] Prefix and suffix are applied correctly
- [ ] Numbering increments properly
- [ ] Number padding works as expected
- [ ] Find and replace modifies names
- [ ] Case sensitivity toggle works
- [ ] Preview matches actual result

### Replacement Panel Tests
- [ ] Selected actors list populates
- [ ] Confirmation dialog appears
- [ ] Transform preservation works
- [ ] Tag preservation works
- [ ] Attachment preservation works
- [ ] Undo restores original actors

### Organization Panel Tests
- [ ] Actors move to specified folder
- [ ] Tags are added/removed correctly
- [ ] Group by type creates proper hierarchy
- [ ] Attach/detach maintains relationships
- [ ] Auto-organize applies conventions

### General UI Tests
- [ ] Tab switching works smoothly
- [ ] Status bar updates with messages
- [ ] All buttons are responsive
- [ ] Tooltips display helpful information
- [ ] Window can be docked
- [ ] Settings persist between sessions

## Part 9: Styling and Polish

### Theme Colors

Define a consistent color palette:

```
Primary: (0.1, 0.4, 0.8, 1.0)    // Blue
Success: (0.2, 0.8, 0.2, 1.0)    // Green
Warning: (0.9, 0.6, 0.1, 1.0)    // Orange
Danger: (0.8, 0.2, 0.2, 1.0)     // Red
Background: (0.05, 0.05, 0.05, 1.0)  // Dark gray
Surface: (0.15, 0.15, 0.15, 1.0)     // Medium gray
Text: (0.9, 0.9, 0.9, 1.0)           // Light gray
```

### Typography

- Headers: Size 18, Bold
- Subheaders: Size 14, Bold
- Body: Size 12, Regular
- Buttons: Size 12, Bold
- Status: Size 10, Italic

### Spacing

- Section padding: 20px
- Element spacing: 10px
- Button padding: 15px horizontal, 10px vertical

### Icons (Optional)

Add icons to buttons for better visual clarity:
- Placement: 📍
- Alignment: ⊞
- Naming: 🏷️
- Replacement: 🔄
- Organization: 📁

## Part 10: Advanced Features (Optional)

### Keyboard Shortcuts

Implement shortcuts for common actions:
- Ctrl+G: Grid placement
- Ctrl+Alt+L: Align left
- Ctrl+Alt+C: Center alignment
- Ctrl+Alt+R: Align right
- Ctrl+Shift+N: Open naming panel

Add in Event Graph:
```
Event On Key Down
├── Get Key
├── Check Modifiers (Ctrl, Alt, Shift)
└── Branch to appropriate action
```

### Presets System

Add ability to save/load settings:
```
Vertical Box
├── Text Block ("Presets")
├── Combo Box (CB_Presets)
├── Horizontal Box
│   ├── Button (Btn_SavePreset)
│   └── Button (Btn_LoadPreset)
```

Save presets to JSON files in project saved folder.

### Undo/Redo Integration

Ensure all operations properly integrate with Unreal's undo system:
- All Blueprint API functions already support undo
- Test with Ctrl+Z and Ctrl+Y
- Verify transaction names appear correctly

## Troubleshooting

### Widget doesn't appear in Tools menu
- Check that EUW_OPM_Main is an Editor Utility Widget (not regular Widget Blueprint)
- Verify plugin is enabled
- Restart editor

### Blueprint functions not visible
- Ensure OPM plugin is compiled and loaded
- Check that functions are marked `BlueprintCallable`
- Look in correct category (OPM|...)

### Changes don't save
- Editor Utility Widgets don't save by design
- Create a save system if persistence needed
- Use editor preferences for settings

### Performance issues
- Limit number of actors processed at once
- Show progress bar for large operations
- Consider async processing for very large batches

## Next Steps

1. Create all widget assets following this guide
2. Implement Blueprint logic for each panel
3. Test each feature thoroughly
4. Gather user feedback
5. Iterate and improve

## Resources

- [Unreal Engine UMG Documentation](https://docs.unrealengine.com/en-US/umg)
- [Editor Utility Widgets](https://docs.unrealengine.com/en-US/editor-utility-widgets)
- [Blueprint Visual Scripting](https://docs.unrealengine.com/en-US/blueprints)
- OPM Blueprint API: See `USAGE_EXAMPLES.md` in plugin root

## Support

For questions or issues with UI implementation:
- GitHub Issues: https://github.com/Mittenzx/OPM/issues
- Documentation: See plugin README.md
- Blueprint API Reference: See USAGE_EXAMPLES.md
