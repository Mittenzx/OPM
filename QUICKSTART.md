# Quick Start Guide - Object Placement Manager

Get up and running with OPM in 5 minutes!

## Installation

### Method 1: From Fab Marketplace (Recommended)
1. Open Epic Games Launcher
2. Go to Fab Marketplace
3. Search for "Object Placement Manager"
4. Purchase and download
5. Install to your engine or project
6. Restart Unreal Engine
7. Enable plugin: Edit → Plugins → Search "OPM" → Enable

### Method 2: From GitHub (Development)
1. Clone or download this repository
2. Copy `Plugins/OPM` to your project's `Plugins` folder
3. Restart Unreal Engine
4. Enable plugin: Edit → Plugins → Search "OPM" → Enable
5. Rebuild project if prompted

## First Launch

After enabling OPM, you'll see:
- **OPM Toolbar**: New toolbar button in the editor
- **Window Menu**: Window → Object Placement Manager
- **Content Browser**: OPM content in Plugins folder

## Your First Placement

### Scenario: Place 10 columns in a grid

1. **Open OPM**
   - Click the OPM toolbar button
   - Or: Window → Object Placement Manager

2. **Select Asset**
   - In Content Browser, find a Static Mesh (e.g., SM_Column)
   - Keep it selected

3. **Configure Grid**
   - In OPM window, go to "Placement" tab
   - Pattern: Grid
   - Rows: 2
   - Columns: 5
   - Spacing X: 200
   - Spacing Y: 200
   - Spacing Z: 0

4. **Preview (Optional)**
   - Check "Show Preview"
   - See temporary outlines in viewport
   - Adjust spacing if needed

5. **Place Objects**
   - Click "Place Objects" button
   - 10 columns appear in a grid!
   - Use Ctrl+Z to undo if needed

**Congratulations!** You just saved yourself 5 minutes of manual placement.

## Common Workflows

### Quick Alignment

**Problem:** You have 5 objects that need to be aligned to the left

1. Select the objects in viewport (Ctrl+Click)
2. Open OPM → Alignment tab
3. Click "Align Left" button
4. Done! Objects are perfectly aligned

### Batch Rename

**Problem:** 20 props named "StaticMeshActor_1, StaticMeshActor_2..." need proper names

1. Select the actors in World Outliner
2. Open OPM → Naming tab
3. Prefix: "Props_"
4. Start Number: 1
5. Padding: 3 (for 001, 002, etc.)
6. Click "Apply"
7. Result: "Props_001, Props_002, Props_003..."

### Circular Placement

**Problem:** Need to place 12 lamps around a fountain

1. Select lamp mesh in Content Browser
2. OPM → Placement tab
3. Pattern: Circular
4. Count: 12
5. Radius: 500
6. Click location for center
7. Click "Place Objects"
8. 12 lamps in perfect circle!

### Replace Actors

**Problem:** 50 placeholder cubes need to be replaced with final props

1. Select all placeholder cubes
2. OPM → Replacement tab
3. Select new actor class (BP_Prop or StaticMesh)
4. Check "Preserve Transform"
5. Click "Replace"
6. All cubes replaced, positions preserved!

## Pro Tips

### Keyboard Shortcuts

Set up shortcuts for frequent operations:
- Edit → Editor Preferences → Keyboard Shortcuts → Search "OPM"
- Recommended shortcuts:
  - OPM Window: `Ctrl + Shift + O`
  - Quick Align: `Ctrl + Alt + A`
  - Quick Grid: `Ctrl + Alt + G`

### Preview Before Placing

Always enable preview for:
- Large numbers of objects
- Expensive actors (Blueprints with logic)
- Unfamiliar patterns

### Undo is Your Friend

- All OPM operations support Undo (Ctrl+Z)
- Don't be afraid to experiment!
- Undo entire batch operations with one keystroke

### Naming Conventions

Establish patterns early:
- Props: `Props_[Type]_[Number]`
- Lights: `Light_[Type]_[Location]_[Number]`
- Triggers: `Trigger_[Purpose]_[Number]`

Use OPM to apply these consistently!

### Combine Operations

Chain multiple operations:
1. Place objects in grid
2. Align to adjust positions
3. Rename for organization
4. Group for hierarchy

### Selection Tips

- Select by type: Right-click → Select All Actors of Class
- Select in bounds: Marquee select in viewport
- Add to selection: Ctrl + Click
- Remove from selection: Ctrl + Shift + Click

## Common Use Cases

### Architectural Visualization

**Windows in a Building:**
```
1. Place window mesh in grid pattern
2. Rows: 4 (floors)
3. Columns: 10 (windows per floor)
4. Spacing: Building dimensions
5. Adjust individual windows as needed
```

**Fence Line:**
```
1. Use Line pattern
2. Click start point
3. Click end point
4. Count: Auto-calculate for spacing
5. Place fence posts
```

### Game Level Design

**Collectibles on Path:**
```
1. Create spline path (future feature)
2. Or use Line pattern between waypoints
3. Place collectible actors
4. Name: Collectible_001, 002, etc.
```

**Enemy Spawn Points:**
```
1. Random Scatter pattern
2. Define arena bounds
3. Place spawn point actors
4. Name by zone: SpawnPoint_Zone1_001
```

### Environment Design

**Tree Line:**
```
1. Line pattern along terrain
2. Random variation in rotation
3. Adjust individual tree positions
4. Add random scatter for natural look
```

**Rock Clusters:**
```
1. Random Scatter in defined area
2. Different rock sizes
3. Slight rotation variation
4. Organize by cluster: Rocks_Cluster1_001
```

## Troubleshooting

### "Can't Place Objects"
- **Check:** Is an actor class selected?
- **Check:** Is the viewport in focus?
- **Check:** Do you have edit permissions?

### "Preview Not Showing"
- **Enable:** "Show Preview" checkbox
- **Check:** Preview color settings
- **Try:** Refresh viewport (F5)

### "Alignment Not Working"
- **Check:** Are actors selected?
- **Check:** Are actors movable (not static)?
- **Try:** Select at least 2 actors

### "Undo Not Working"
- **Note:** Some operations may not support undo
- **Check:** Transaction history
- **Report:** If consistently failing, report bug

### Performance Issues
- **Reduce:** Number of objects in preview
- **Disable:** Preview for large batches
- **Place:** In smaller groups
- **Consider:** Simpler actor types

## Next Steps

### Learn More
- Read full [Plugin Documentation](Plugins/OPM/README.md)
- Watch video tutorials (coming soon)
- Check out example project
- Join community discussions

### Get Help
- [GitHub Issues](https://github.com/Mittenzx/OPM/issues) for bugs
- [Discussions](https://github.com/Mittenzx/OPM/discussions) for questions
- Epic Developer Forums for community help

### Advanced Topics
- Creating custom patterns
- Blueprint automation
- Editor scripting with OPM
- Plugin customization

### Share Your Work
- Show us what you build with OPM!
- Share tips and workflows
- Request features you need
- Help other users

## FAQ

**Q: Does OPM affect runtime performance?**
A: No! OPM is editor-only. Zero runtime impact.

**Q: Can I use OPM in commercial projects?**
A: Yes! No additional licensing required.

**Q: Is Blueprint support available?**
A: Yes! All features accessible via Blueprint.

**Q: Can I customize patterns?**
A: Coming in future versions! Request this feature if important to you.

**Q: Does it work with UE4?**
A: Currently UE5.3+. UE4 support possible if requested.

**Q: Can I suggest features?**
A: Absolutely! Open an issue or discussion on GitHub.

**Q: How do I report bugs?**
A: GitHub Issues with details about your setup and steps to reproduce.

**Q: Is source code included?**
A: Yes! Full C++ source provided.

## Resources

- **Documentation:** [Full Docs](Plugins/OPM/README.md)
- **Implementation:** [Technical Guide](IMPLEMENTATION.md)
- **Contributing:** [Contribution Guide](CONTRIBUTING.md)
- **Support:** [GitHub Issues](https://github.com/Mittenzx/OPM/issues)

---

## Need Help?

If you're stuck:
1. Check this guide first
2. Review the FAQ
3. Search existing issues
4. Ask in discussions
5. Create a new issue

**We're here to help make your workflow better!**

---

**Ready to save hours of work? Let's go! 🚀**
