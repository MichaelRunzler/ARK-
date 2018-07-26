#include "stdafx.h"
#include "format_tools.h"

void crawltext(string text, int speed, bool ignoreSpaces) 
{
    long delay = 1000L / speed;

    for (char c : text) {
        cout << c;
        if (c == ' ' || c == '\r' || c == '\t' || c == '\n' && ignoreSpaces) continue;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void crawltext(string text, int speed) {
    crawltext(text, speed, false);
}

string glitchtext(int len)
{
    string result;
    int time = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(time);

    // The range of ASCII characters after the initial control character set (0x00-0x21, 0-33) and before the second control set
    // (0x7F-0xA0, 127-160) is 94 wide. The char datatype stores its ID as an integer number between -128 and 127 (range 256, including 0).
    // Thus, 128 must be subtracted to ensure valid ranging.

    for(int i = 0; i < len; i++) result += (rand() % 94) - 128;

    return result;
}

string autowrap(string text, int width, string newline, bool hyphenation) 
{
    string buffer;

    // The postfix string cannot be larger than the width, since this will cause infinite recursion
    if (&newline == NULL || newline.size() > width) throw std::invalid_argument("Newline postfix string cannot be larger than the maximum width.");

    // Check postfix string for newlines or tabs, since those will screw up the line counting algorithm
    for (char c : newline)
        if(c == '\n' || c == '\t' || c == '\r') throw std::invalid_argument("Newline postfix string cannot contain control characters.");

    int counter = 0;
    int lastSpaceIndex = -1;
    int cacheSize = -1;
    // until we run out of characters in the input:
    for (char c : text)
    {
        cacheSize = -1;

        // add character to buffer
        buffer += c;
        // increment line width counter
        counter++;
        // if the current character is a newline or carriage return, reset line width counter to 0 and continue
        if (c == '\n' || c == '\t' || c == '\r') counter = 0;
        // otherwise, check if the line width is outside the max width
        else if (counter >= width) {
            // if we have a space to wrap at, wrap there
            if (lastSpaceIndex > 0) {
                // replace last space with a newline
                buffer[lastSpaceIndex] = '\n';

                // if we need to insert a newline postfix:
                if (&newline != NULL) {
                    // save all characters that follow that space to cache
                    string cache;
                    for (int i = lastSpaceIndex + 1; i < buffer.size(); i++) cache += buffer[i];
                    // 'delete' all characters after the insertion point
                    buffer = buffer.substr(0, lastSpaceIndex + 1);

                    // append newline postfix and cached following characters, save cache size so that it can be calculated later
                    buffer += newline;
                    buffer += cache;
                    cacheSize = cache.size();
                }
            }
            // otherwise, there is no space to wrap at, we'll have to wrap in the middle of the text
            else {
                // replace current character with newline
                buffer[buffer.size() - 1] = '\n';
                if (hyphenation) {
                    // cache and replace the second-to-last character with a hyphen
                    char tmp = buffer[buffer.size() - 2];
                    buffer[buffer.size() - 2] = '-';
                    // append the postfix text if there is any, then the stored second-to-last character
                    if (&newline != NULL) buffer += newline;
                    buffer += tmp;
                    cacheSize = 1;
                }
                
                // append current character to buffer
                buffer += c;
            }

            // reset counter to 0, count all characters in the newline postfix if there is one, add cache size if caching was used
            counter = 0;
            if (&newline != NULL) {
                counter += newline.size();
                if (cacheSize > 0) counter += cacheSize;
            }
        }

        // if the current character is a space, record its position to the spacing index
        if (c == ' ') lastSpaceIndex = buffer.size() - 1;
    }

    return buffer;
}

string autowrap(string text, int width, bool hyphenation) {
    return autowrap(text, width, "", hyphenation);
}

string autowrap(string text, int width) {
    return autowrap(text, width, NULL, true);
}

void VNText(string text, string name, int speed)
{
    string buffer;
    string justificationSpacer;
    string compiledName = name + ": ";

    // Compile facsimile of the final text
    buffer += compiledName;
    buffer += text;

    // Generate spacer of equal width to the name and its suffix
    justificationSpacer = string(compiledName.size(), ' ');

    // Autowrap to generate proper scaling for the final text
    buffer = autowrap(buffer, getConsoleSize().X - 1, justificationSpacer, true);
    // Remove name from the buffer, since it will be instantly printed to the console instead of crawled
    buffer = buffer.substr(compiledName.size(), string::npos);

    // Print the name and its suffix to the console
    cout << compiledName;

    // Crawltext the rest of the prespaced text body
    crawltext(buffer, speed, true);
}

void clear(int lines, bool returnToStart) 
{
    if (lines < 1) return;

    _COORD conDims = getConsoleSize();
    _COORD currentLine = getCursorPos();

    string blank = string(conDims.X + 1, ' ');
    bool overrun = false;

    for (int i = 0; i < lines; i++) {
        if (currentLine.Y - i < 0) {
            overrun = true;
            break;
        }
        setCursorPos(0, currentLine.Y - i);
        cout << blank;
    }

    if (returnToStart) setCursorPos(0, currentLine.Y);
    else if (overrun) setCursorPos(0, 0);
    else setCursorPos(0, currentLine.Y - (lines - 1));
}

void clearTo(int y, bool returnToStart)
{
    _COORD cursorPos = getCursorPos();
    if (cursorPos.Y < y) return;

    clear((y - cursorPos.Y) + 1, returnToStart);
}

void scroll(int lines) {
    // Scroll (n - 1) lines using \n, then scroll the final line using endl (to flush the buffer).
    for (int i = 1; i < lines; i++) 
        cout << '\n';
    cout << endl;
}

void multiVNText(string name, vector<string> lines, int speed, int maxWait, bool clearLast)
{
    vector<string>::iterator iter;
    _COORD cursorPos;
    for (iter = lines.begin(); iter != lines.end(); iter++) {
        cursorPos = getCursorPos();
        VNText(*iter, name, speed);
        if(maxWait > 0) waitForKeypress(maxWait);
        if ((iter != lines.end() - 1) || clearLast)
            clearTo(cursorPos.Y, false);
    }
}