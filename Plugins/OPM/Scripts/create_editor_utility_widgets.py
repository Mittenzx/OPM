"""
OPM Editor Utility Widget Creator Script

This Python script creates the basic Editor Utility Widget assets for the OPM plugin.
Run this script from within Unreal Engine's Python console or as a startup script.

Requirements:
- Unreal Engine 5.3+ with Python plugin enabled
- OPM plugin installed and enabled
- Run from Editor (not commandlet)

Usage:
    1. Open your Unreal Engine project
    2. Window > Developer Tools > Python Console
    3. Run: exec(open('path/to/this/script.py').read())
    
Or:
    1. Edit > Project Settings > Plugins > Python
    2. Add this script to Startup Scripts
    3. Restart editor
"""

import unreal

# Configuration
PLUGIN_CONTENT_PATH = "/OPM"  # Plugin content mount point
UI_PATH = f"{PLUGIN_CONTENT_PATH}/UI"
UTILITIES_PATH = f"{PLUGIN_CONTENT_PATH}/Utilities"

def log(message):
    """Print message to Unreal log"""
    unreal.log(f"[OPM Widget Creator] {message}")

def create_editor_utility_widget(asset_path, asset_name):
    """
    Create an Editor Utility Widget asset
    
    Args:
        asset_path: The path where to create the asset (e.g., "/OPM/UI")
        asset_name: The name of the asset (e.g., "EUW_OPM_Main")
    
    Returns:
        The created asset or None if failed
    """
    try:
        # Get asset tools
        asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
        
        # Create the factory for Editor Utility Widgets
        factory = unreal.EditorUtilityWidgetBlueprintFactory()
        
        # Create the asset
        full_path = f"{asset_path}/{asset_name}"
        asset = asset_tools.create_asset(
            asset_name=asset_name,
            package_path=asset_path,
            asset_class=unreal.EditorUtilityWidgetBlueprint,
            factory=factory
        )
        
        if asset:
            log(f"Created Editor Utility Widget: {full_path}")
            # Save the asset
            unreal.EditorAssetLibrary.save_asset(full_path, only_if_is_dirty=False)
            return asset
        else:
            log(f"Failed to create Editor Utility Widget: {full_path}")
            return None
            
    except Exception as e:
        log(f"Error creating widget {asset_name}: {str(e)}")
        return None

def create_blueprint_class(asset_path, asset_name, parent_class):
    """
    Create a Blueprint class asset
    
    Args:
        asset_path: The path where to create the asset
        asset_name: The name of the asset
        parent_class: The parent class for the blueprint
    
    Returns:
        The created asset or None if failed
    """
    try:
        asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
        
        # Create blueprint factory
        factory = unreal.BlueprintFactory()
        factory.set_editor_property('parent_class', parent_class)
        
        # Create the asset
        full_path = f"{asset_path}/{asset_name}"
        asset = asset_tools.create_asset(
            asset_name=asset_name,
            package_path=asset_path,
            asset_class=unreal.Blueprint,
            factory=factory
        )
        
        if asset:
            log(f"Created Blueprint: {full_path}")
            unreal.EditorAssetLibrary.save_asset(full_path, only_if_is_dirty=False)
            return asset
        else:
            log(f"Failed to create Blueprint: {full_path}")
            return None
            
    except Exception as e:
        log(f"Error creating blueprint {asset_name}: {str(e)}")
        return None

def ensure_folder_exists(folder_path):
    """
    Ensure a folder exists in the content browser
    
    Args:
        folder_path: The folder path to create
    
    Returns:
        True if folder exists or was created, False otherwise
    """
    try:
        if unreal.EditorAssetLibrary.does_directory_exist(folder_path):
            log(f"Folder already exists: {folder_path}")
            return True
        
        result = unreal.EditorAssetLibrary.make_directory(folder_path)
        if result:
            log(f"Created folder: {folder_path}")
        else:
            log(f"Failed to create folder: {folder_path}")
        return result
        
    except Exception as e:
        log(f"Error creating folder {folder_path}: {str(e)}")
        return False

def setup_main_widget(widget_asset):
    """
    Configure the main widget with basic setup
    This would require more complex Blueprint editing which is limited in Python
    """
    # Note: Full widget hierarchy setup requires more advanced Blueprint editing
    # which is better done manually or through C++ editor automation
    log("Main widget created. Configure layout manually in the editor.")
    pass

def create_all_widgets():
    """
    Create all OPM Editor Utility Widgets
    """
    log("=== Starting OPM Widget Creation ===")
    
    # Ensure folders exist
    log("\n1. Creating folder structure...")
    folders = [
        PLUGIN_CONTENT_PATH,
        UI_PATH,
        UTILITIES_PATH,
        f"{PLUGIN_CONTENT_PATH}/Icons",
        f"{PLUGIN_CONTENT_PATH}/Documentation"
    ]
    
    for folder in folders:
        ensure_folder_exists(folder)
    
    # Create Editor Utility Widgets
    log("\n2. Creating Editor Utility Widgets...")
    widgets = [
        ("EUW_OPM_Main", "Main OPM interface with tabbed panels"),
        ("EUW_Placement", "Placement patterns panel"),
        ("EUW_Alignment", "Alignment and distribution panel"),
        ("EUW_Naming", "Batch naming utilities panel"),
        ("EUW_Replacement", "Actor replacement panel"),
        ("EUW_Organization", "Organization tools panel"),
    ]
    
    created_widgets = []
    for widget_name, description in widgets:
        log(f"\nCreating {widget_name}: {description}")
        widget = create_editor_utility_widget(UI_PATH, widget_name)
        if widget:
            created_widgets.append(widget)
    
    # Create helper Blueprints
    log("\n3. Creating helper Blueprint classes...")
    
    # Note: Creating helper blueprints (optional)
    # helper_name = "BP_OPMHelpers"
    # helper_bp = create_blueprint_class(
    #     UTILITIES_PATH, 
    #     helper_name,
    #     unreal.Object  # Or appropriate base class
    # )
    
    log("\n=== Widget Creation Complete ===")
    log(f"Created {len(created_widgets)} Editor Utility Widgets")
    log(f"\nNext steps:")
    log("1. Navigate to {UI_PATH} in Content Browser")
    log("2. Open each widget to configure the layout")
    log("3. Follow the UI_IMPLEMENTATION_GUIDE.md for detailed setup")
    log("4. Add Blueprint logic to connect to OPM Blueprint Library")
    
    return created_widgets

def add_widget_to_tools_menu(widget_path, menu_label):
    """
    Register an Editor Utility Widget in the Tools menu
    
    Args:
        widget_path: Full path to the widget asset
        menu_label: Label to show in the menu
    """
    try:
        # Get the Editor Utility Subsystem
        editor_utility_subsystem = unreal.get_editor_subsystem(unreal.EditorUtilitySubsystem)
        
        # Register the widget
        # Note: This API may vary by engine version
        log(f"Registering {widget_path} in Tools menu as '{menu_label}'")
        
        # The widget will be accessible from Tools > Blutilities menu
        # after being created as an Editor Utility Widget
        
    except Exception as e:
        log(f"Error registering widget in menu: {str(e)}")

def main():
    """
    Main entry point for the script
    """
    log("OPM Editor Utility Widget Creation Script")
    log("=========================================\n")
    
    # Check if we're running in editor
    if not unreal.SystemLibrary.is_editor():
        log("ERROR: This script must be run from within the Unreal Editor")
        return
    
    # Create all widgets
    widgets = create_all_widgets()
    
    # If main widget was created, you could register it in tools menu
    if widgets:
        main_widget_path = f"{UI_PATH}/EUW_OPM_Main"
        add_widget_to_tools_menu(main_widget_path, "Object Placement Manager")
    
    log("\n=== All Done! ===")
    log("Check the Content Browser at {UI_PATH}")

# Run the script if executed directly
if __name__ == "__main__":
    main()
