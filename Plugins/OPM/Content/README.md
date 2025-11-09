# OPM Content Assets

This folder contains the Blueprint and UI assets for the Object Placement Manager plugin.

## Folder Structure

```
Content/
├── UI/                    # Editor Utility Widgets
│   ├── EUW_OPM_Main      # Main plugin interface (to be created)
│   ├── EUW_Placement     # Placement panel widget (to be created)
│   ├── EUW_Alignment     # Alignment panel widget (to be created)
│   ├── EUW_Naming        # Naming utilities panel (to be created)
│   ├── EUW_Replacement   # Actor replacement panel (to be created)
│   └── EUW_Organization  # Organization tools panel (to be created)
├── Utilities/            # Blueprint helper functions
│   └── BP_OPMHelpers     # Blueprint utility library (to be created)
├── Icons/                # UI icons and graphics
│   └── (Icon assets)
└── Documentation/        # In-editor documentation
    └── (Help assets)
```

## Creating Editor Utility Widgets

Editor Utility Widgets are binary assets that must be created in the Unreal Engine Editor. Follow the implementation guide in `UI_IMPLEMENTATION_GUIDE.md` for step-by-step instructions.

## Asset Naming Conventions

- **Editor Utility Widgets:** Prefix with `EUW_`
- **Blueprint Classes:** Prefix with `BP_`
- **Widget Blueprints:** Prefix with `WBP_`
- **Textures:** Prefix with `T_`
- **Materials:** Prefix with `M_`

## Integration with C++ API

All UI widgets should use the `UOPMBlueprintLibrary` class functions to interact with the plugin's core functionality. See `USAGE_EXAMPLES.md` in the plugin root for API documentation.
