#include "stdafx.h"
#include "console.h"

string _error;

string lastErrorMsg() {
    return _error;
}

boolean resizeConsole(int width, int height)
{
    _COORD coord;
    coord.X = width + 1;
    coord.Y = height + 1;

    _SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = height;
    rect.Right = width;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(handle == NULL) _error = "Could not get output handle.";
    else if(!SetConsoleWindowInfo(handle, TRUE, &rect)) _error = "Could not update window sizing.";
    else if(!SetConsoleScreenBufferSize(handle, coord)) _error = "Could not update screen buffer size.";
    else return true;

    return false;
}

_COORD getConsoleSize()
{
    _COORD result;
    CONSOLE_SCREEN_BUFFER_INFO info = getConsoleSizingInfo();

    // If the sizing retrieval function was unable to get the sizing info, everything will just be 0.
    result.X = info.srWindow.Right - info.srWindow.Left;
    result.Y = info.srWindow.Bottom - info.srWindow.Top;

    return result;
}

CONSOLE_SCREEN_BUFFER_INFO getConsoleSizingInfo()
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle == NULL) _error = "Could not get output handle.";
    else if (GetConsoleScreenBufferInfo(handle, &info) == NULL) _error = "Could not get buffer information:" + GetLastError();
    else return info;

    return CONSOLE_SCREEN_BUFFER_INFO();
}

_COORD getCursorPos()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle == NULL) _error = "Could not get output handle.";
    else if (!GetConsoleScreenBufferInfo(handle, &csbi))
        _error = "Could not get buffer info from console.";
    else return csbi.dwCursorPosition;

    return _COORD();
}

void setCursorPos(int x, int y) 
{
    _COORD conDims = getConsoleSize();
    _COORD targetCoords;

    if (x > conDims.X) targetCoords.X = conDims.X;
    else if (x < 0) targetCoords.X = 1;
    else targetCoords.X = x;

    if (y > conDims.Y) targetCoords.Y = conDims.Y;
    else if (y < 0) targetCoords.Y = 1;
    else targetCoords.Y = y;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle == NULL) _error = "Could not get output handle.";
    else if (!SetConsoleCursorPosition(handle, targetCoords))
        _error = "Unable to set cursor position";
}

_COORD getRelMouseCursorPos()
{
    //fixme not working, handle does not appear to be valid
    bool hasChangedTitle = true;
    POINT cCoords;
    _COORD cRelCoords = _COORD();
    HWND windowHandle;

    wchar_t cBuffer[128];
    wchar_t oBuffer[256];

    LPWSTR customTitle = cBuffer;
    LPTSTR oldTitle = oBuffer;

    // Get the old console title, cache it
    GetConsoleTitle(oldTitle, 256);
    // Assemble the temporary console title
    wsprintf(customTitle, L"%d/%d", GetTickCount(), GetCurrentProcessId());
    
    // Try to set the temporary title.
    if (!SetConsoleTitle(customTitle)) {
        _error = "Unable to set temporary console window title.";
        hasChangedTitle = false;
    }

    // Check to ensure that the console title has changed, return if it has not.
    if (!hasChangedTitle) return cRelCoords;
    Sleep(40);

    // Get the handle for the current console window
    windowHandle = FindWindow(NULL, customTitle);

    // Get the cursor position and convert to the relative coordinates
    if (!GetCursorPos(&cCoords))
        _error = "Unable to get absolute cursor position.";
    else if (ScreenToClient(windowHandle, &cCoords))
        _error = "Unable to convert absolute to relative coordinates.";
    else {
        cRelCoords.X = cCoords.x;
        cRelCoords.Y = cCoords.y;
    }

    // Restore the old window title
    SetConsoleTitle(oldTitle);

    return cRelCoords;
}

_COORD getMouseCursorPos()
{
    POINT cCoords;
    _COORD cRelCoords = _COORD();

    if (!GetCursorPos(&cCoords))
        _error = "Unable to get cursor position.";
    else {
        cRelCoords.X = cCoords.x;
        cRelCoords.Y = cCoords.y;
    }

    return cRelCoords;
}