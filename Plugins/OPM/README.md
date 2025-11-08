# Object Placement Manager (OPM)

**Version:** 1.0.0  
**Engine Compatibility:** Unreal Engine 5.3+  
**Platform:** Win64, Mac, Linux

## Overview

Object Placement Manager (OPM) is a powerful yet simple Unreal Engine editor plugin designed to streamline your level design workflow. Whether you're placing hundreds of props, organizing complex scenes, or maintaining naming conventions across your project, OPM provides intuitive tools to save hours of manual work.

## 🎯 Why OPM?

Based on extensive research of the Fab marketplace, we identified that **workflow automation tools** are consistently missing or poorly developed. Developers spend countless hours on repetitive tasks like:

- Manually placing objects in grids or patterns
- Aligning and distributing actors one by one
- Renaming assets with consistent naming conventions
- Replacing multiple actors with different meshes
- Organizing level hierarchies

**OPM solves these problems with simple, intuitive tools built directly into the Unreal Engine editor.**

## ✨ Key Features

### 1. **Batch Object Placement**
- Place multiple objects in customizable patterns:
  - Grid patterns (specify rows, columns, spacing)
  - Circular/radial arrangements
  - Line distributions
  - Random scatter within bounds
- Preview placement before applying
- Support for Static Meshes, Blueprints, and other actor types

### 2. **Smart Alignment & Distribution**
- Align selected actors (Left, Right, Top, Bottom, Center)
- Distribute evenly (Horizontal, Vertical, Circular)
- Match rotation and scale across selections
- Snap to grid with custom grid sizes
- Align to surface normals

### 3. **Batch Naming Utilities**
- Add prefixes/suffixes to multiple actors
- Auto-numbering with customizable formats
- Find and replace in actor names
- Apply naming conventions based on actor type
- Search and filter by name patterns

### 4. **Quick Actor Replacement**
- Replace selected actors with different mesh/blueprint
- Preserve transform (location, rotation, scale)
- Batch replacement for entire selections
- Maintain hierarchy and parent relationships

### 5. **Level Organization Tools**
- Auto-group related actors
- Create hierarchical folder structures
- Batch parenting operations
- Clean up outliner organization
- Tag-based organization systems

### 6. **Editor Utility Widget Interface**
- Clean, intuitive UI built with UMG
- Dockable panels in the editor
- Keyboard shortcuts for common operations
- Undo/Redo support for all operations
- Real-time preview and feedback

## 🚀 Getting Started

### Installation

1. Download the OPM plugin from the Fab marketplace
2. Copy the `OPM` folder to your project's `Plugins` directory
3. Restart Unreal Engine
4. Enable the plugin from Edit → Plugins → Editor → Object Placement Manager
5. Access OPM tools from the Editor toolbar or Window menu

### Quick Start Guide

**Batch Placement:**
1. Select an actor type in the Content Browser
2. Open OPM → Batch Placement tool
3. Configure your pattern (grid, circle, etc.)
4. Click "Place Objects"

**Alignment:**
1. Select multiple actors in the viewport
2. Open OPM → Alignment tools
3. Choose alignment type (left, center, distribute, etc.)
4. Click "Align"

**Batch Rename:**
1. Select actors in the outliner
2. Open OPM → Naming Utilities
3. Enter prefix, suffix, or numbering format
4. Click "Apply Names"

## 📋 Use Cases

### Architectural Visualization
- Place windows, columns, or tiles in perfect grids
- Align furniture and props consistently
- Organize scene hierarchy by rooms or floors

### Game Development
- Scatter vegetation or debris procedurally
- Place collectibles or spawn points in patterns
- Organize level sections and streaming volumes

### Environment Design
- Create fence lines, walls, or barriers quickly
- Distribute rocks, trees, or foliage
- Align modular building pieces perfectly

### Technical Art
- Set up lighting rigs in patterns
- Place audio sources or trigger volumes
- Organize blueprint instances

## 🛠️ Technical Details

### System Requirements
- Unreal Engine 5.3 or higher
- Windows 10/11, macOS 11+, or Linux
- No additional dependencies

### Performance
- Lightweight plugin with minimal overhead
- Operates directly in the editor (no runtime impact)
- Efficient batch operations using Unreal's API
- Supports undo/redo for all operations

### Blueprint Integration
- All functionality accessible via Blueprint
- Create custom workflows combining OPM tools
- Extend with your own editor utilities

## 📖 Documentation

Full documentation is available at: [https://github.com/Mittenzx/OPM/wiki](https://github.com/Mittenzx/OPM/wiki)

### Topics Covered:
- Detailed feature guides
- Video tutorials
- Blueprint scripting examples
- Troubleshooting
- FAQ

## 🐛 Support & Bug Reports

- Report issues: [GitHub Issues](https://github.com/Mittenzx/OPM/issues)
- Feature requests welcome!
- Community discussions on Epic Developer Forums

## 📝 Changelog

### Version 1.0.0 (Initial Release)
- Batch object placement with grid, circle, and line patterns
- Smart alignment and distribution tools
- Batch naming utilities with auto-numbering
- Quick actor replacement functionality
- Level organization tools
- Editor Utility Widget interface
- Full undo/redo support

## 🎓 Learning Resources

### Video Tutorials
- Getting Started with OPM (5 minutes)
- Batch Placement Deep Dive (10 minutes)
- Advanced Workflows (15 minutes)

### Example Projects
- Included demo level showcasing all features
- Blueprint examples for custom workflows

## 💡 Tips & Tricks

1. **Use Keyboard Shortcuts**: Set up custom shortcuts for frequently used tools
2. **Preview First**: Always preview placements before applying to avoid mistakes
3. **Naming Conventions**: Establish consistent naming early in your project
4. **Combine Tools**: Chain multiple operations for complex workflows
5. **Save Presets**: Create and save pattern presets for reusable configurations

## 🤝 Contributing

OPM is open for community contributions! Visit our GitHub repository to:
- Submit bug fixes
- Propose new features
- Improve documentation
- Share your workflows

## 📄 License

This plugin is provided as-is for use in Unreal Engine projects. See LICENSE file for details.

## 🌟 Why Choose OPM?

- **Small & Focused**: Does one thing really well - saves you time
- **Easy to Use**: Intuitive interface, minimal learning curve
- **Well Documented**: Comprehensive guides and video tutorials
- **Actively Maintained**: Regular updates and bug fixes
- **Community Driven**: Open to feedback and feature requests
- **Professional Quality**: Built following Epic's best practices

---

**Made with ❤️ for the Unreal Engine community**

Transform your workflow. Save hours. Build better games.

*Download OPM today and experience the difference!*
