# OPM UI Testing Guide

Comprehensive testing procedures for the Object Placement Manager Editor Utility Widgets.

## Testing Philosophy

**Goal:** Ensure all UI features work correctly, provide good user experience, and handle edge cases gracefully.

**Approach:**
1. **Functional Testing** - Does it work?
2. **Usability Testing** - Is it easy to use?
3. **Integration Testing** - Do features work together?
4. **Edge Case Testing** - What happens when things go wrong?

## Pre-Testing Checklist

Before starting tests:
- [ ] OPM plugin is enabled and compiled
- [ ] All Editor Utility Widgets are created
- [ ] Test level with various actors is set up
- [ ] Undo history is clear (Ctrl+Z should be empty)
- [ ] Output Log is visible (Window → Developer Tools → Output Log)

## Test Environment Setup

### Create Test Level

```
Test Level Contents:
├── 10 StaticMeshActor instances (cubes)
├── 5 PointLight instances
├── 3 Blueprint actor instances
├── Empty actor (for parent testing)
├── Actors with various scales
├── Actors with rotations
└── Actors with tags
```

**Quick Setup:**
1. Create new level
2. Place actors as listed above
3. Name them sequentially (Cube_1, Cube_2, etc.)
4. Save as "OPM_TestLevel"

## Section 1: Main Widget Tests

### Test 1.1: Widget Opening
**Objective:** Verify widget opens correctly

**Steps:**
1. Content Browser → Plugins → OPM → UI
2. Right-click `EUW_OPM_Main`
3. Select "Run Editor Utility Widget"

**Expected Result:**
- ✓ Widget window opens
- ✓ Default tab (Placement) is active
- ✓ Status bar shows "Ready"
- ✓ Window is resizable
- ✓ Window can be docked

**Pass/Fail:** ______

### Test 1.2: Tab Navigation
**Objective:** Verify all tabs are accessible

**Steps:**
1. Click each tab button in order
2. Verify content changes

**Expected Result:**
- ✓ Placement tab shows placement controls
- ✓ Alignment tab shows alignment buttons
- ✓ Naming tab shows naming controls
- ✓ Replacement tab shows replacement controls
- ✓ Organization tab shows organization controls
- ✓ Active tab is visually highlighted
- ✓ Tab switching is smooth

**Pass/Fail:** ______

### Test 1.3: Window Behavior
**Objective:** Test window interactions

**Steps:**
1. Resize window to minimum size
2. Resize to maximum size
3. Dock window to side panel
4. Undock window
5. Close and reopen widget

**Expected Result:**
- ✓ Minimum size maintained (400x500)
- ✓ Maximum size respected (1200x1000)
- ✓ Docking works properly
- ✓ Layout adjusts to size
- ✓ Settings persist (if implemented)

**Pass/Fail:** ______

## Section 2: Placement Panel Tests

### Test 2.1: Grid Pattern - Basic
**Objective:** Place actors in grid pattern

**Steps:**
1. Open Placement tab
2. Select "Grid" pattern
3. Set Rows: 3, Columns: 3
4. Set Spacing: 200 (all axes)
5. Click "Place Actors"

**Expected Result:**
- ✓ 9 actors placed in 3×3 grid
- ✓ Spacing is 200 units
- ✓ Actors are properly aligned
- ✓ Status message confirms placement
- ✓ Undo (Ctrl+Z) removes all placed actors

**Pass/Fail:** ______

### Test 2.2: Grid Pattern - Edge Cases
**Objective:** Test grid with unusual values

**Test Cases:**
| Rows | Columns | Spacing | Expected Behavior |
|------|---------|---------|-------------------|
| 1 | 1 | 100 | Single actor |
| 10 | 10 | 50 | 100 actors (dense) |
| 5 | 1 | 200 | Single column |
| 1 | 5 | 200 | Single row |
| 3 | 3 | -100 | Negative spacing |
| 3 | 3 | 0 | Zero spacing (all at origin) |

**Expected Result:**
- ✓ All cases handled correctly
- ✓ No crashes or errors
- ✓ Negative spacing works as expected
- ✓ Zero spacing creates overlapping actors

**Pass/Fail:** ______

### Test 2.3: Circular Pattern
**Objective:** Place actors in circle

**Steps:**
1. Select "Circular" pattern
2. Set Count: 12
3. Set Radius: 500
4. Set Start Angle: 0
5. Click "Place Actors"

**Expected Result:**
- ✓ 12 actors in circular formation
- ✓ Radius is 500 units
- ✓ First actor at 0° (to the right)
- ✓ Even spacing around circle
- ✓ Undo works

**Pass/Fail:** ______

### Test 2.4: Circular Pattern - Variations
**Objective:** Test circular pattern options

**Test Cases:**
- Half circle (Start Angle: 0, End Angle: 180)
- Full rotation (Start Angle: 0, End Angle: 360)
- Offset start (Start Angle: 90)
- Large radius (1000+)
- Small radius (50)
- Height offset (100 units up)

**Expected Result:**
- ✓ All variations work correctly
- ✓ Angles calculated properly
- ✓ Height offset applied

**Pass/Fail:** ______

### Test 2.5: Line Pattern
**Objective:** Place actors in line

**Steps:**
1. Select "Line" pattern
2. Set Count: 10
3. Define start and end points
4. Click "Place Actors"

**Expected Result:**
- ✓ 10 actors in straight line
- ✓ Even spacing between actors
- ✓ First actor at start point
- ✓ Last actor at end point
- ✓ Intermediate actors evenly distributed

**Pass/Fail:** ______

### Test 2.6: Random Pattern
**Objective:** Place actors randomly

**Steps:**
1. Select "Random" pattern
2. Set Count: 50
3. Define bounds (min: -500, max: 500 for X, Y, Z)
4. Set Seed: 123
5. Click "Place Actors"
6. Undo and repeat with same seed
7. Repeat with different seed

**Expected Result:**
- ✓ 50 actors placed randomly
- ✓ All actors within bounds
- ✓ Same seed produces same result
- ✓ Different seed produces different result
- ✓ Distribution looks random

**Pass/Fail:** ______

### Test 2.7: Actor Class Selection
**Objective:** Test different actor classes

**Test Cases:**
- StaticMeshActor
- PointLight
- SpotLight
- Blueprint actors
- Camera actors

**Expected Result:**
- ✓ All actor types can be placed
- ✓ Class picker works correctly
- ✓ Browse dialog functions
- ✓ Invalid classes are rejected

**Pass/Fail:** ______

### Test 2.8: Preview Mode (if implemented)
**Objective:** Test preview functionality

**Steps:**
1. Enable "Show Preview" checkbox
2. Change settings
3. Observe preview update
4. Click "Place Actors"

**Expected Result:**
- ✓ Preview shows ghost actors
- ✓ Preview updates with settings changes
- ✓ Preview actors are removed after placement
- ✓ Preview doesn't interfere with undo

**Pass/Fail:** ______

## Section 3: Alignment Panel Tests

### Test 3.1: Horizontal Alignment
**Objective:** Test left/center/right alignment

**Setup:**
1. Place 5 actors at random X positions
2. Select all 5 actors

**Steps:**
1. Click "Align Left"
2. Undo
3. Click "Align Center"
4. Undo
5. Click "Align Right"

**Expected Result:**
- ✓ Align Left: All actors at leftmost X position
- ✓ Align Center: All actors at center X position
- ✓ Align Right: All actors at rightmost X position
- ✓ Y and Z positions unchanged
- ✓ Each operation undoable

**Pass/Fail:** ______

### Test 3.2: Vertical Alignment
**Objective:** Test front/center/back alignment

**Setup:**
1. Place 5 actors at random Y positions
2. Select all 5 actors

**Steps:**
1. Click "Align Front"
2. Undo
3. Click "Align Center" (Y)
4. Undo
5. Click "Align Back"

**Expected Result:**
- ✓ Align Front: All actors at frontmost Y position
- ✓ Align Center: All actors at center Y position
- ✓ Align Back: All actors at backmost Y position
- ✓ X and Z positions unchanged
- ✓ Each operation undoable

**Pass/Fail:** ______

### Test 3.3: Height Alignment
**Objective:** Test top/center/bottom alignment

**Setup:**
1. Place 5 actors at random Z positions
2. Select all 5 actors

**Steps:**
1. Click "Align Bottom"
2. Undo
3. Click "Align Center" (Z)
4. Undo
5. Click "Align Top"

**Expected Result:**
- ✓ Align Bottom: All actors at lowest Z position
- ✓ Align Center: All actors at center Z position
- ✓ Align Top: All actors at highest Z position
- ✓ X and Y positions unchanged
- ✓ Each operation undoable

**Pass/Fail:** ______

### Test 3.4: Distribution - Horizontal
**Objective:** Test even horizontal distribution

**Setup:**
1. Place 5 actors at irregular X positions
2. Note leftmost and rightmost positions
3. Select all 5 actors

**Steps:**
1. Click "Distribute Horizontally"
2. Measure spacing between actors

**Expected Result:**
- ✓ Leftmost and rightmost actors don't move
- ✓ Middle actors redistributed evenly
- ✓ Spacing is equal between all actors
- ✓ Y and Z positions unchanged
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 3.5: Distribution - Vertical
**Objective:** Test even vertical distribution

**Setup:**
1. Place 5 actors at irregular Y positions
2. Select all 5 actors

**Steps:**
1. Click "Distribute Vertically"
2. Measure spacing

**Expected Result:**
- ✓ Front and back actors don't move
- ✓ Middle actors redistributed evenly
- ✓ Equal spacing between actors
- ✓ X and Z positions unchanged
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 3.6: Snap to Grid
**Objective:** Test grid snapping

**Setup:**
1. Place actors at irregular positions (e.g., X=156.7, Y=283.4)
2. Select actors

**Steps:**
1. Set Grid Size: 100
2. Click "Snap to Grid"
3. Check actor positions

**Expected Result:**
- ✓ Positions rounded to grid (X=200, Y=300)
- ✓ All axes snapped
- ✓ Grid size respected
- ✓ Operation undoable

**Test with different grid sizes:**
- Grid 50: Snap to nearest 50 units
- Grid 10: Snap to nearest 10 units
- Grid 500: Snap to nearest 500 units

**Pass/Fail:** ______

### Test 3.7: Selected Actor Count
**Objective:** Test real-time selection feedback

**Steps:**
1. Deselect all actors
2. Select 1 actor
3. Select 5 actors
4. Select 20 actors
5. Deselect all

**Expected Result:**
- ✓ "0 actors selected" when none selected
- ✓ "1 actor selected" for single selection
- ✓ "N actors selected" for multiple
- ✓ Count updates in real-time
- ✓ Updates on every selection change

**Pass/Fail:** ______

### Test 3.8: Alignment with Different Actor Types
**Objective:** Test alignment with various actors

**Setup:**
1. Select mix of actor types (meshes, lights, blueprints)
2. Mix of scales and rotations

**Steps:**
1. Test each alignment function
2. Verify correct behavior

**Expected Result:**
- ✓ Works with all actor types
- ✓ Scale doesn't affect alignment
- ✓ Rotation doesn't affect alignment
- ✓ Bounds calculated correctly

**Pass/Fail:** ______

## Section 4: Naming Panel Tests

### Test 4.1: Prefix and Suffix
**Objective:** Add prefix and suffix to names

**Setup:**
1. Select 5 actors named: Actor1, Actor2, Actor3, Actor4, Actor5

**Steps:**
1. Set Prefix: "Prop_"
2. Set Suffix: "_LOD0"
3. Click "Preview"
4. Verify preview
5. Click "Apply"

**Expected Result:**
- ✓ Preview shows: Prop_Actor1_LOD0, etc.
- ✓ Apply changes names correctly
- ✓ All 5 actors renamed
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 4.2: Numbering
**Objective:** Add sequential numbers

**Setup:**
1. Select 5 actors

**Steps:**
1. Enable "Add Numbers"
2. Set Start Number: 1
3. Set Padding: 3
4. Click "Apply"

**Expected Result:**
- ✓ Names become: Actor001, Actor002, Actor003, Actor004, Actor005
- ✓ Padding is correct (3 digits)
- ✓ Numbers increment correctly
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 4.3: Numbering Variations
**Objective:** Test different numbering options

**Test Cases:**
| Start | Padding | Expected Format |
|-------|---------|----------------|
| 1 | 2 | 01, 02, 03 |
| 1 | 4 | 0001, 0002, 0003 |
| 10 | 3 | 010, 011, 012 |
| 0 | 3 | 000, 001, 002 |
| 100 | 2 | 100, 101, 102 |

**Expected Result:**
- ✓ All formats work correctly
- ✓ Padding applied properly
- ✓ Start number respected

**Pass/Fail:** ______

### Test 4.4: Find and Replace - Basic
**Objective:** Replace text in names

**Setup:**
1. Select actors with names containing "Cube"

**Steps:**
1. Set Find: "Cube"
2. Set Replace: "Box"
3. Click "Apply"

**Expected Result:**
- ✓ "Cube" replaced with "Box" in all names
- ✓ Case matches original
- ✓ Only matching text replaced
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 4.5: Find and Replace - Case Sensitivity
**Objective:** Test case-sensitive replacement

**Setup:**
1. Actors named: "CUBE_1", "Cube_2", "cube_3"

**Steps:**
1. Set Find: "Cube"
2. Set Replace: "Box"
3. Test with case-sensitive OFF
4. Undo
5. Test with case-sensitive ON

**Expected Result:**
- ✓ Case-insensitive: All replaced (BOX_1, Box_2, box_3)
- ✓ Case-sensitive: Only exact match replaced (CUBE_1, Box_2, cube_3)
- ✓ Checkbox works correctly

**Pass/Fail:** ______

### Test 4.6: Combined Operations
**Objective:** Test prefix, suffix, and numbering together

**Setup:**
1. Select 5 actors

**Steps:**
1. Set Prefix: "SM_"
2. Set Suffix: "_Inst"
3. Enable Numbering (Start: 1, Padding: 2)
4. Click "Apply"

**Expected Result:**
- ✓ Result: SM_01_Inst, SM_02_Inst, etc.
- ✓ All components applied correctly
- ✓ Order is: Prefix + Number + Suffix
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 4.7: Preview Accuracy
**Objective:** Verify preview matches actual result

**Steps:**
1. Configure any naming operation
2. Click "Preview"
3. Note preview names
4. Click "Apply"
5. Compare actual names to preview

**Expected Result:**
- ✓ Preview exactly matches result
- ✓ All actors shown in preview
- ✓ Preview updates when settings change
- ✓ Preview list is scrollable

**Pass/Fail:** ______

### Test 4.8: Reset Functionality
**Objective:** Test reset button

**Steps:**
1. Configure all naming options
2. Click "Reset"

**Expected Result:**
- ✓ All text boxes cleared
- ✓ Checkboxes unchecked
- ✓ Spin boxes reset to default
- ✓ Preview cleared
- ✓ Status updated

**Pass/Fail:** ______

## Section 5: Replacement Panel Tests

### Test 5.1: Basic Replacement
**Objective:** Replace actors with new class

**Setup:**
1. Place 3 StaticMeshActors
2. Select all 3

**Steps:**
1. Choose PointLight as new class
2. Enable all preservation options
3. Click "Replace"
4. Confirm dialog

**Expected Result:**
- ✓ 3 new PointLight actors created
- ✓ Original StaticMeshActors removed
- ✓ Positions preserved
- ✓ Rotations preserved
- ✓ Scales preserved
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 5.2: Transform Preservation
**Objective:** Test transform preservation options

**Setup:**
1. Place actor at specific location, rotation, scale
2. Note exact transforms

**Steps:**
1. Replace with different class
2. Test with preservation ON
3. Undo
4. Test with preservation OFF

**Expected Result:**
- ✓ With preservation: Exact transforms maintained
- ✓ Without preservation: Default transforms used
- ✓ Location precision maintained (no rounding errors)

**Pass/Fail:** ______

### Test 5.3: Tag Preservation
**Objective:** Test tag preservation

**Setup:**
1. Add tags to actors: "prop", "static", "test"
2. Select tagged actors

**Steps:**
1. Enable "Preserve Tags"
2. Replace actors
3. Check new actors' tags

**Expected Result:**
- ✓ New actors have all original tags
- ✓ Tag order preserved (if applicable)
- ✓ No duplicate tags created

**Pass/Fail:** ______

### Test 5.4: Attachment Preservation
**Objective:** Test child attachment preservation

**Setup:**
1. Create parent actor
2. Attach 3 child actors
3. Select parent

**Steps:**
1. Enable "Preserve Attachments"
2. Replace parent
3. Check hierarchy

**Expected Result:**
- ✓ Children still attached to new parent
- ✓ Attachment transforms maintained
- ✓ Hierarchy structure preserved
- ✓ Socket attachments maintained (if applicable)

**Pass/Fail:** ______

### Test 5.5: Confirmation Dialog
**Objective:** Test user confirmation

**Steps:**
1. Select actors
2. Click "Replace"
3. Click "No" in dialog
4. Repeat and click "Yes"

**Expected Result:**
- ✓ Confirmation dialog appears
- ✓ Shows accurate count
- ✓ "No" cancels operation
- ✓ "Yes" proceeds with replacement
- ✓ Status updated appropriately

**Pass/Fail:** ______

### Test 5.6: Selected Actors List
**Objective:** Test actor list display

**Steps:**
1. Select no actors
2. Select 1 actor
3. Select 10 actors
4. Select 50 actors

**Expected Result:**
- ✓ List updates in real-time
- ✓ Shows actor name and class
- ✓ List is scrollable
- ✓ List clears when selection cleared
- ✓ Performance is acceptable with many actors

**Pass/Fail:** ______

### Test 5.7: Different Actor Types
**Objective:** Test replacement between different types

**Test Cases:**
- StaticMesh → Light
- Light → Blueprint
- Blueprint → StaticMesh
- Actor → Custom Blueprint
- Custom Blueprint → Another Blueprint

**Expected Result:**
- ✓ All conversions work
- ✓ No type-specific errors
- ✓ Appropriate properties preserved

**Pass/Fail:** ______

## Section 6: Organization Panel Tests

### Test 6.1: Folder Assignment
**Objective:** Move actors to folder

**Setup:**
1. Select 5 actors

**Steps:**
1. Enter folder path: "/Environment/Props"
2. Click "Move to Folder"
3. Check World Outliner

**Expected Result:**
- ✓ Actors moved to specified folder
- ✓ Folder created if doesn't exist
- ✓ Actors visible in outliner under folder
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 6.2: Tag Addition
**Objective:** Add tags to actors

**Setup:**
1. Select 5 actors with no tags

**Steps:**
1. Enter tags: "prop, environment, static"
2. Click "Add Tags"
3. Check actor tags

**Expected Result:**
- ✓ All 3 tags added to all actors
- ✓ Tags parsed correctly (split by comma)
- ✓ Whitespace trimmed
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 6.3: Tag Removal
**Objective:** Remove specific tags

**Setup:**
1. Select actors with tags: "prop, environment, static, test"

**Steps:**
1. Enter tags to remove: "test, static"
2. Click "Remove Tags"
3. Check remaining tags

**Expected Result:**
- ✓ Specified tags removed
- ✓ Other tags remain
- ✓ Non-existent tags ignored (no error)
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 6.4: Clear All Tags
**Objective:** Remove all tags from actors

**Setup:**
1. Select actors with multiple tags

**Steps:**
1. Click "Clear All Tags"
2. Confirm if prompted
3. Check actors

**Expected Result:**
- ✓ All tags removed from all actors
- ✓ Confirmation dialog appears (if implemented)
- ✓ Status shows success
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 6.5: Group by Type
**Objective:** Auto-organize by actor type

**Setup:**
1. Select 15 actors (5 StaticMesh, 5 Lights, 5 Blueprints)

**Steps:**
1. Click "Group by Type"
2. Check hierarchy in outliner

**Expected Result:**
- ✓ Parent actors created for each type
- ✓ Actors attached to appropriate parent
- ✓ Parent naming is clear (e.g., "StaticMeshActors")
- ✓ Original transforms maintained
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 6.6: Attach to Parent
**Objective:** Manually create hierarchy

**Setup:**
1. Select 1 parent actor + 3 child actors

**Steps:**
1. Click "Attach to Parent"
2. Check hierarchy

**Expected Result:**
- ✓ First selected actor becomes parent
- ✓ Remaining actors attached as children
- ✓ Relative transforms calculated correctly
- ✓ Outliner shows correct hierarchy
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 6.7: Detach from Parent
**Objective:** Break hierarchy

**Setup:**
1. Create parent-child hierarchy
2. Select child actors

**Steps:**
1. Click "Detach from Parent"
2. Check hierarchy

**Expected Result:**
- ✓ Actors detached from parents
- ✓ World transforms maintained
- ✓ Actors appear at root level in outliner
- ✓ Operation undoable

**Pass/Fail:** ______

### Test 6.8: Auto Organize
**Objective:** Test automatic organization

**Setup:**
1. Select many unsorted actors

**Steps:**
1. Click "Auto Organize"
2. Review organization applied

**Expected Result:**
- ✓ Actors grouped by type
- ✓ Folders created appropriately
- ✓ Tags applied based on type
- ✓ Naming conventions applied
- ✓ Operation undoable

**Pass/Fail:** ______

## Section 7: Integration Tests

### Test 7.1: Placement + Alignment
**Objective:** Use multiple features in sequence

**Steps:**
1. Place 5×5 grid of actors
2. Select all placed actors
3. Align them to center
4. Distribute horizontally

**Expected Result:**
- ✓ All operations work together
- ✓ Final result is correct
- ✓ Each step undoable independently

**Pass/Fail:** ______

### Test 7.2: Placement + Naming
**Objective:** Place and name in workflow

**Steps:**
1. Place circular pattern (12 actors)
2. Select all placed actors
3. Rename with prefix "Light_" and numbering
4. Verify names

**Expected Result:**
- ✓ Actors named: Light_01 through Light_12
- ✓ Circular pattern intact
- ✓ Both operations undoable

**Pass/Fail:** ______

### Test 7.3: Complete Workflow
**Objective:** Use all features together

**Steps:**
1. Place grid of actors
2. Align them
3. Rename them
4. Add tags
5. Move to folder
6. Group by type

**Expected Result:**
- ✓ All operations complete successfully
- ✓ Final state is correct
- ✓ Undo history maintains all steps
- ✓ No conflicts between features

**Pass/Fail:** ______

### Test 7.4: Multiple Undo/Redo
**Objective:** Test undo/redo through multiple operations

**Steps:**
1. Perform 5 different operations
2. Undo all 5 (Ctrl+Z × 5)
3. Redo all 5 (Ctrl+Y × 5)

**Expected Result:**
- ✓ Each undo reverses one operation
- ✓ Level returns to original state after all undos
- ✓ Redo restores operations correctly
- ✓ Final state matches before undo

**Pass/Fail:** ______

## Section 8: Edge Case & Error Tests

### Test 8.1: No Selection
**Objective:** Test behavior with no actors selected

**Steps:**
1. Deselect all actors
2. Try each feature that requires selection

**Expected Result:**
- ✓ Appropriate error message shown
- ✓ "No actors selected" displayed
- ✓ No crash or freeze
- ✓ UI remains responsive

**Pass/Fail:** ______

### Test 8.2: Invalid Inputs
**Objective:** Test with invalid values

**Test Cases:**
- Negative grid size
- Zero count
- Empty text boxes
- Very large numbers (10000+)
- Special characters in names

**Expected Result:**
- ✓ Invalid inputs rejected or handled gracefully
- ✓ Clear error messages
- ✓ No crashes
- ✓ UI remains stable

**Pass/Fail:** ______

### Test 8.3: Large Selections
**Objective:** Test performance with many actors

**Steps:**
1. Place 100 actors
2. Select all 100
3. Perform alignment operation
4. Perform naming operation

**Expected Result:**
- ✓ Operations complete successfully
- ✓ Performance is acceptable (<5 seconds)
- ✓ No stuttering or freezing
- ✓ Progress indication shown (if long)

**Pass/Fail:** ______

### Test 8.4: Mixed Selections
**Objective:** Test with different actor types

**Setup:**
1. Select mix: Meshes, Lights, Blueprints, Volumes

**Steps:**
1. Test each operation

**Expected Result:**
- ✓ Operations work with mixed types
- ✓ No type-specific errors
- ✓ Appropriate handling of incompatible actors

**Pass/Fail:** ______

### Test 8.5: Rapid Operations
**Objective:** Test rapid successive operations

**Steps:**
1. Click placement button rapidly (5 times fast)
2. Click alignment buttons in quick succession
3. Spam reset button

**Expected Result:**
- ✓ No crashes
- ✓ Operations queue properly or reject duplicates
- ✓ UI remains responsive
- ✓ No memory leaks

**Pass/Fail:** ______

## Section 9: Usability Tests

### Test 9.1: First-Time User
**Objective:** Test intuitiveness for new users

**Steps:**
1. Give widget to new user (no instructions)
2. Ask them to place actors in a grid
3. Ask them to align some actors
4. Note difficulties

**Expected Result:**
- ✓ User can figure out basic operations
- ✓ Tooltips are helpful
- ✓ Labels are clear
- ✓ Workflow makes sense

**Pass/Fail:** ______

### Test 9.2: Tooltip Quality
**Objective:** Verify all tooltips are helpful

**Steps:**
1. Hover over every button and control
2. Read each tooltip

**Expected Result:**
- ✓ All controls have tooltips
- ✓ Tooltips are descriptive
- ✓ No typos or errors
- ✓ Tooltips appear after 1s hover

**Pass/Fail:** ______

### Test 9.3: Visual Feedback
**Objective:** Test user feedback mechanisms

**Checklist:**
- [ ] Button hover states work
- [ ] Active tab is highlighted
- [ ] Status messages appear
- [ ] Selection count updates
- [ ] Preview updates in real-time
- [ ] Disabled states are clear

**Pass/Fail:** ______

### Test 9.4: Error Messages
**Objective:** Test error message clarity

**Steps:**
1. Trigger each type of error
2. Read error messages

**Expected Result:**
- ✓ Errors are clear and specific
- ✓ Suggest how to fix the problem
- ✓ No technical jargon
- ✓ No generic "Error occurred" messages

**Pass/Fail:** ______

## Section 10: Performance Tests

### Test 10.1: Widget Opening Time
**Objective:** Measure widget load time

**Steps:**
1. Close widget
2. Time opening process
3. Repeat 3 times, average results

**Expected Result:**
- ✓ Opens in <2 seconds
- ✓ No visible lag or stutter

**Pass/Fail:** ______ (Time: _____s)

### Test 10.2: Large Grid Placement
**Objective:** Test performance with large grids

**Steps:**
1. Place 20×20 grid (400 actors)
2. Measure time taken

**Expected Result:**
- ✓ Completes in <10 seconds
- ✓ Progress indication shown
- ✓ Editor remains responsive

**Pass/Fail:** ______ (Time: _____s)

### Test 10.3: Memory Usage
**Objective:** Check for memory leaks

**Steps:**
1. Note starting memory usage
2. Perform 50 operations
3. Undo all operations
4. Check memory usage

**Expected Result:**
- ✓ Memory returns to near-starting level
- ✓ No significant memory increase
- ✓ No unreleased resources

**Pass/Fail:** ______

## Test Summary

### Overall Results

- **Total Tests:** _____ / _____
- **Passed:** _____
- **Failed:** _____
- **Pass Rate:** _____%

### Critical Issues Found

1. _____________________________________
2. _____________________________________
3. _____________________________________

### Minor Issues Found

1. _____________________________________
2. _____________________________________
3. _____________________________________

### Recommendations

_________________________________________
_________________________________________
_________________________________________

### Sign-Off

**Tester Name:** _____________________
**Date:** ___________________________
**Version:** _________________________

**Ready for Release:** [ ] Yes  [ ] No  [ ] With fixes

---

## Automated Testing (Future)

For automated testing, consider creating Python scripts:

```python
# Example automated test
def test_grid_placement():
    # Clear level
    # Place 5x5 grid
    # Assert 25 actors exist
    # Assert positions are correct
    # Undo
    # Assert actors removed
```

## Continuous Testing

For ongoing development:
- Run critical path tests daily
- Full test suite before each release
- Automated tests in CI/CD pipeline
- User acceptance testing before launch

---

**This guide should be updated as new features are added.**
