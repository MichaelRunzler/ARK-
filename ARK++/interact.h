#pragma once

#include "format_tools.h"
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

/*
* Waits for any standard key to be pressed by the user (a-z, 0-9, enter, symbols).
* Will wait for up to the specified delay before skipping the prompt.
* Delays of 0 or less will wait indefinitely until a keypress is registered or the program is terminated.
* long maxDelayMS: the maximum amount of time (in milliseconds) that the program will wait for a keypress before skipping the prompt.
*                  Delay uses a granularity of 10ms to wait for input, as such maximum wait times may not be millisecond-precise.
* returns: the keycode for the key that was pressed, or -1 if the routine timed out
*/
char waitForKeypress(long maxDelayMS);

/*
* Waits for any standard key to be pressed by the user (a-z, 0-9, enter, symbols).
* Will wait indefinitely long until a keypress is registered or the program is terminated.
* Calls waitForKeypress(long) with -1 as the time argument.
*/
char waitForKeypress();