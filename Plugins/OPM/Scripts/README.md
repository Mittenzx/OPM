# OPM Automation Scripts

This folder contains automation scripts for setting up and maintaining the OPM plugin.

## Scripts

### create_editor_utility_widgets.py

**Purpose:** Automatically creates the basic Editor Utility Widget assets for the OPM plugin.

**Requirements:**
- Unreal Engine 5.3+ with Python plugin enabled
- OPM plugin installed and enabled in your project
- Must be run from within the Unreal Editor (not commandlet mode)

**Usage:**

#### Method 1: Python Console (Recommended)
1. Open your Unreal Engine project
2. Enable Python plugin if not already enabled:
   - Edit → Plugins
   - Search for "Python Editor Script Plugin"
   - Check the box and restart editor
3. Open Python console:
   - Window → Developer Tools → Python Console
4. Navigate to the script location
5. Execute the script:
   ```python
   exec(open('path/to/Plugins/OPM/Scripts/create_editor_utility_widgets.py').read())
   ```
   Or with absolute path:
   ```python
   import os
   script_path = os.path.join(os.getcwd(), 'Plugins', 'OPM', 'Scripts', 'create_editor_utility_widgets.py')
   exec(open(script_path).read())
   ```

#### Method 2: Startup Script
1. Edit → Project Settings → Plugins → Python
2. Add script to "Startup Scripts" list:
   - Path: `$(ProjectDir)/Plugins/OPM/Scripts/create_editor_utility_widgets.py`
3. Restart the editor
4. Widgets will be created automatically on startup

#### Method 3: Init Script
1. Create an `init_unreal.py` file in your project root
2. Add this line:
   ```python
   import unreal
   exec(open('Plugins/OPM/Scripts/create_editor_utility_widgets.py').read())
   ```
3. Set as startup script in Project Settings

**What It Does:**

The script will:
1. Create the Content folder structure if it doesn't exist:
   - `/OPM/UI` - For Editor Utility Widgets
   - `/OPM/Utilities` - For helper Blueprints
   - `/OPM/Icons` - For UI icons
   - `/OPM/Documentation` - For help assets

2. Create these Editor Utility Widget assets:
   - `EUW_OPM_Main` - Main plugin interface
   - `EUW_Placement` - Placement tools panel
   - `EUW_Alignment` - Alignment tools panel
   - `EUW_Naming` - Naming utilities panel
   - `EUW_Replacement` - Actor replacement panel
   - `EUW_Organization` - Organization tools panel

3. Save all created assets

**Output:**

Check the Output Log for messages:
```
[OPM Widget Creator] Creating folder structure...
[OPM Widget Creator] Created folder: /OPM/UI
[OPM Widget Creator] Creating Editor Utility Widgets...
[OPM Widget Creator] Created Editor Utility Widget: /OPM/UI/EUW_OPM_Main
...
[OPM Widget Creator] Widget Creation Complete
[OPM Widget Creator] Created 6 Editor Utility Widgets
```

**Next Steps After Running:**

1. Navigate to Content Browser → Plugins → OPM Content → UI
2. You should see all created Editor Utility Widget assets
3. Double-click any widget to open it in the UMG Designer
4. Follow the `UI_IMPLEMENTATION_GUIDE.md` to configure each widget
5. Add widget hierarchy and Blueprint logic as documented

**Troubleshooting:**

**Error: "Module 'unreal' not found"**
- Solution: Python plugin not enabled. Enable in Edit → Plugins → Python

**Error: "SystemLibrary not in editor mode"**
- Solution: Script must be run from Unreal Editor, not commandlet

**Error: "Permission denied" or "Cannot create asset"**
- Solution: Check that Content folder is writable
- Solution: Try running Editor as administrator (Windows)

**Widgets not appearing in Content Browser**
- Solution: Click "View Options" (eye icon) → Show Plugin Content
- Solution: Refresh Content Browser (right-click → Refresh)

**Script runs but creates nothing**
- Solution: Check Output Log for error messages
- Solution: Verify plugin is properly installed and enabled
- Solution: Check that Content folder path is correct

## Additional Scripts (Coming Soon)

### validate_api_bindings.py
- Validates that all C++ functions are properly exposed to Blueprint
- Checks for missing categories or documentation
- Reports API coverage

### generate_api_documentation.py
- Auto-generates Blueprint API documentation
- Creates markdown reference from C++ headers
- Updates API reference docs

### create_default_presets.py
- Creates default placement presets
- Sets up common configurations
- Saves preset files

### ui_testing_suite.py
- Automated UI widget testing
- Validates widget hierarchy
- Checks for missing bindings

## Contributing

To add new automation scripts:

1. Create Python script in this folder
2. Follow the naming convention: `verb_noun.py`
3. Include docstring with:
   - Purpose
   - Requirements
   - Usage instructions
   - Example output
4. Add error handling and logging
5. Update this README with script description

## Python API Resources

- [Unreal Python API Docs](https://docs.unrealengine.com/en-US/ProductionPipelines/ScriptingAndAutomation/Python/)
- [Python Editor Script Plugin](https://docs.unrealengine.com/en-US/ProductionPipelines/ScriptingAndAutomation/Python/PythonEditorScriptPlugin/)
- [Unreal Python Examples](https://github.com/20tab/UnrealEnginePython)

## Support

For issues with automation scripts:
- Check Output Log for error messages
- Enable verbose Python logging in Project Settings
- Report issues on GitHub: https://github.com/Mittenzx/OPM/issues
- Include script name, error message, and UE version

## Version History

**v1.0 (November 2025)**
- Initial release
- `create_editor_utility_widgets.py` - Basic widget creation

**Planned for v1.1:**
- API validation script
- Documentation generator
- Preset creation tool
- UI testing suite
