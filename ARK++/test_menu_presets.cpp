
#include "stdafx.h"
#include "test_menu_presets.h"

static const string IDENTIFIER_MAIN = "menu_main";
static const string IDENTIFIER_OPTIONS = "menu_opt";
static const string IDENTIFIER_INDEX_MAIN = "menu_index_main";

void init_menus()
{
    vector<MenuItem> storage;

    storage.push_back(generate_menu_entry("Generate..."));
    storage.push_back(generate_menu_entry("Index Management"));
    storage.push_back(generate_menu_entry("Program Settings"));
    storage.push_back(generate_menu_entry("Exit"));

    add_preset(storage, IDENTIFIER_MAIN);

    storage.clear();

    storage.push_back(generate_menu_entry("View current configuration"));
    storage.push_back(generate_menu_entry("Change Setting..."));
    storage.push_back(generate_menu_entry("Export Config"));
    storage.push_back(generate_menu_entry("Import Config"));
    storage.push_back(generate_menu_entry("Reset to Defaults"));
    storage.push_back(generate_menu_entry("Return to Main Menu"));

    add_preset(storage, IDENTIFIER_OPTIONS);

    storage.clear();

    storage.push_back(generate_menu_entry("View Index Contents"));
    storage.push_back(generate_menu_entry("Add Entry..."));
    storage.push_back(generate_menu_entry("Remove Entry..."));
    storage.push_back(generate_menu_entry("Import Index"));
    storage.push_back(generate_menu_entry("Export Index"));
    storage.push_back(generate_menu_entry("Clear Index"));
    storage.push_back(generate_menu_entry("Return to Main Menu"));

    add_preset(storage, IDENTIFIER_INDEX_MAIN);

    storage.clear();
}

void clear_menu_presets()
{
    remove_preset(IDENTIFIER_MAIN);
    remove_preset(IDENTIFIER_OPTIONS);
    remove_preset(IDENTIFIER_INDEX_MAIN);
}