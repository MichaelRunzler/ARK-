#pragma once

#include <thread>
#include <chrono>
#include <vector>
#include "console.h"
#include "interact.h"

using namespace std;

/*
* Displays the provided string one character at a time to STDOUT.
* Blocks until output is complete.
* string text: the text to write to STDOUT.
* int speed: the speed to display the text in characters per second (CPS).
* bool ignoreSpaces: if true, spaces and other nonprinting characters will be printed to the console instantly with no delay, avoiding percieved
*                    "lag" from seemingly missing output. If false, spaces will obey the same timing as all other characters.
*/
void crawltext(string text, int delay, bool ignoreSpaces);

/*
* Displays the provided string one character at a time to STDOUT.
* Blocks until output is complete.
* Calls the above definition of crawltext() with ignoreSpaces set to FALSE.
* string text: the text to write to STDOUT.
* int speed: the speed to display the text in characters per second (CPS).
*/
void crawltext(string text, int delay);

/*
* Generates a string of ASCII 'glitchtext' characters by randomly generating codepoints from the non-control
* character range (34-126).
* int len: the number of characters to generate.
* returns: a glitchtext string of the desired length.
*/
string glitchtext(int len);

/*
* Automatically wraps a section of text at word boundaries, if there are any.
* The routine will attempt to wrap the provided text at the closest space. If
* there are no spaces suitable for use as wrapping points, the string will be wrapped
* at the exact point where it exceeds the maximum width, with optional hyphenation inserted.
* If the input text is shorter than the maximum width, no action will be taken.
* string text: the text to autowrap
* int width: the maximum number of characters before a newline is inserted
* string newline: a section of text to insert after the newline character. Provide a pointer to NULL (0x0h) if no text should be inserted.
* bool hyphenation: if true, a hyphen will be inserted at the breakpoint if the breakpoint was in the middle of a word
* returns: the input text, reformatted to fit within the provided text width
*/
string autowrap(string text, int width, string newline, bool hyphenation);

/*
* Automatically wraps a section of text at word boundaries, if there are any.
* The routine will attempt to wrap the provided text at the closest space. If
* there are no spaces suitable for use as wrapping points, the string will be wrapped
* at the exact point where it exceeds the maximum width, with optional hyphenation inserted.
* If the input text is shorter than the maximum width, no action will be taken.
* Calls autowrap(string, int, string, bool) with NULL as the newline prepend argument.
* string text: the text to autowrap
* int width: the maximum number of characters before a newline is inserted
* bool hyphenation: if true, a hyphen will be inserted at the breakpoint if the breakpoint was in the middle of a word
* returns: the input text, reformatted to fit within the provided text width
*/
string autowrap(string text, int width, bool hyphenation);

/*
* Automatically wraps a section of text at word boundaries, if there are any.
* The routine will attempt to wrap the provided text at the closest space. If
* there are no spaces suitable for use as wrapping points, the string will be wrapped
* at the exact point where it exceeds the maximum width.
* If the input text is shorter than the maximum width, no action will be taken.
* Calls autowrap(string, int, string, bool) with no hyphenation and NULL as the newline prepend argument.
* string text: the text to autowrap
* int width: the maximum number of characters before a newline is inserted
* returns: the input text, reformatted to fit within the provided text width
*/
string autowrap(string text, int width);

/*
* Prints a section of text to the console as if it were being displayed to text box in a VN.
* The text is prepended by the provided name, followed by a colon and a space. The text body is
* sized to the console width by calling autowrap() on it, and then justified to ensure that it is even with
* the displayed character name. Finally, the text body is displayed to the console with crawltext()
* at the specified speed. This method blocks until output is complete.
* string text: the text body that should be displayed after the character name
* string name: the name of the character that should 'speak' the text body
* int speed: the speed at which the body text should be printed to the console, in CPS.
*/
void VNText(string text, string name, int speed);

/*
* Clears the previous X lines of the console, including the current one.
* Specifying 1 as the number of lines will only clear the current line.
* Clears lines by getting the current console width, and printing a sequence of space characters
* equal to said width to each line that should be cleared.
* bool returnToStart: if true, returns the cursor to its original position when done. 
                      If false, sets the cursor position to the highest line cleared when done.
*/
void clear(int lines, bool returnToStart);

/*
* Clears all lines in the console from the current cursor position to the specified Y coordinate (inclusive).
* Specifying 1 as the number of lines will only clear the current line.
* Clears lines by getting the current console width, and printing a sequence of space characters
* equal to said width to each line that should be cleared.
* bool returnToStart: if true, returns the cursor to its original position when done.
* If false, sets the cursor position to the highest line cleared when done.
*/
void clearTo(int y, bool returnToStart);

/*
* Scrolls the console window the specified amount of lines.
* int lines: the number of lines to scroll the console.
*/
void scroll(int lines);

/*
* Displays multiple successive instances of VN-style text to the console in sequence.
* Calls VNText() for each provided text body, followed by clear().
* string name: the character name to use while displaying text lines.
* vector<string> lines: the text bodies to be displayed in sequence.
* int speed: the speed at which the text bodies should be printed to the console, in CPS.
* int mwaxWait: the amount of time to wait after displaying each line before displaying the next one.
                This delay may be truncated by pressing a key. Delays of 0 or less will immediately display the next line.
* bool clearLast: if true, the last text body will be cleared, leaving the console as it was when the sequence started.
*/
void multiVNText(string name, vector<string> lines, int speed, int maxWait, bool clearLast);