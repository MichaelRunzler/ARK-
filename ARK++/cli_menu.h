#pragma once

#include <vector>
#include <sstream>
#include <map>

// Datatypes and structures

using namespace std;
struct MenuItem {
    string text;
    int priority;
};

// Constant fields
static const string MENU_SELECTION_PROMPT = "Please select an option: ";
static const string GENERIC_INVALID_INPUT = "Invalid entry. Please try again.";
static const string NEW_LINE = "\r\n";

// Method declarations

/*
* Displays a menu interface and returns the user's choice.
* vector<MenuItem> options: the list of MenuItem data pairs to display
* returns: an integer number representing the user's choice of item
*/
int display_menu(vector<MenuItem> options);

/*
* Adds a menu preset value to the list of stored presets.
* vector<MenuItem> options: the list of MenuItem data pairs to display
* string name: the name under which this preset should be stored
*/
void add_preset(vector<MenuItem> options, string name);

/*
* Displays a preset from the list of stored presets.
* string name: the name of the preset to display
* returns: an integer number representing the user's choice of item,
*          or -1 if the specified preset does not exist
*/
int display_preset(string name);

/*
* Removes a menu preset value from the list of stored presets.
* string name: the name under which this preset was stored
*/
void remove_preset(string name);

/*
* Generates a MenuItem value from the specified arguments. Shortcut/utility method.
* returns: a MenuItem value equivalent to the specified arguments
*/
MenuItem generate_menu_entry(string text, int priority);

/*
* Generates a MenuItem value from the specified arguments. Shortcut/utility method.
* Uses the default priority value of 0.
* returns: a MenuItem value equivalent to the specified arguments
*/
MenuItem generate_menu_entry(string text);