#include "stdafx.h"
#include "cli_menu.h"

// Static property fields
static int max_input_tries = -1; // Maximum number of consecutive input attempts before exiting the current submenu, <= 0 for infinite
static map<string, vector<MenuItem>> menu_presets; // Preset menu selections for ease-of-use, starts empty, shared cross-class

// Static methods

int display_menu(vector<MenuItem> options)
{
    string compiled;

    //todo add priority sorting
    vector<MenuItem>::iterator iter;
    int pos = 1;
    for (iter = options.begin(); iter != options.end(); iter++) {
        MenuItem item = *iter;
        compiled += (to_string(pos) + ". ");
        compiled += item.text;
        compiled += NEW_LINE;
        pos++;
    }

    compiled += NEW_LINE;
    compiled += MENU_SELECTION_PROMPT;

    cout << compiled;
    
    int returnedValue = -1;
    string buf;
    stringstream sst;

    while (returnedValue <= 0) {
        cin >> buf;
        sst << buf;
        sst >> returnedValue;

        if (returnedValue <= 0) cout << GENERIC_INVALID_INPUT << endl;
    }

    return returnedValue;
}

void add_preset(vector<MenuItem> options, string name)
{
    if (options.size() <= 0 || name == "") return;
    menu_presets[name] = options;
}

int display_preset(string name)
{
    vector<MenuItem> preset;
    try {
        preset = menu_presets.at(name);
    } catch (out_of_range e) {
        return -1;
    }

    return display_menu(preset);
}

MenuItem generate_menu_entry(string text, int priority)
{
    MenuItem item;
    item.text = text;
    item.priority = priority;

    return item;
}

MenuItem generate_menu_entry(string text) {
    return generate_menu_entry(text, 0);
}

void remove_preset(string name) {
    menu_presets.erase(name);
}