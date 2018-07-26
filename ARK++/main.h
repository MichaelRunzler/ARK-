#pragma once

#include <vector>
#include "cli_menu.h"
#include "console.h"
#include "format_tools.h"
#include "interact.h"
#include "VNSequence.h"

using namespace std;

// Constants
static const string MAIN_MENU_PKEY = "main>menu_main";

// Non-constant reference variables
string null_buffer; // Used as a target for 'waiting for user input' prompt entries, never read, only written to


// Test methods
int test_cli_menu();
int test_console_tools();
int test_format_tools();
int test_VN_tools();