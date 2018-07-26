#pragma once

#include <Windows.h>

using namespace std;

/*
* Returns the last error message produced by an operation performed by this class, if any are available.
* returns: the last error message that a method in this class logged, or NULL if none are available
*/
string lastErrorMsg();

/*
* Sets the size of the current console window.
* int width: the width of the console window in columns
* int height: the height of the console window in rows
* returns: true if the resize completed successfully, false if an error was encountered.
*          Query the lastErrorMsg() method to get error details.
*/
boolean resizeConsole(int width, int height);

/*
* Gets the size of the current console window.
* Chain-calls getConsoleSizingInfo() to get its sizing information.
* Returns 0 for both width and height if the API call fails to execute properly.
* returns: a COORD data structure containing the X (width) and Y (height) dimensions of the current console window in characters.
*/
_COORD getConsoleSize();

/*
* Gets the sizing and buffer data of the current console window.
* Returns a construct populated with all zeros if the API call fails to execute properly.
* returns: a CONSOLE_SCREEN_BUFFER_INFO data structure containing the raw screen buffer and window sizing information for the current console window.
*/
CONSOLE_SCREEN_BUFFER_INFO getConsoleSizingInfo();

/*
* Sets the cursor position in the current console window to the specified X-Y coordinates.
* Setting a cursor position outside of the current window bounds will clip the position to
* the bounds of the window.
*/
void setCursorPos(int x, int y);

/*
* Gets the current console cursor position inside the active console window.
* returns: the current cursor position in a COORD struct
*/
_COORD getCursorPos();

/*
* Gets the current mouse cursor position relative to the current console window.
* returns: the current cursor position in a COORD struct
*/
_COORD getRelMouseCursorPos();

/*
* Gets the current mouse cursor position relative to the current monitor.
* returns: the current cursor position in a COORD struct
*/
_COORD getMouseCursorPos();