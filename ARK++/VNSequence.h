#pragma once
#include <vector>
#include "format_tools.h"
#include "console.h"

using namespace std;

/*
* Contains multiple text bodies, also known as 'lines', along
* with a character name, used to display VN-style text
* through the VNText() method.
*/
class VNSequence
{
private:
    vector<string> lines;
    string name;
    vector<string>::iterator iter;

public:
    /*
    * Default constructor. Initializes the set name and
    * internal line storage to empty values.
    */
    VNSequence();

    VNSequence(string name);

    VNSequence(string name, vector<string> lines);

    ~VNSequence();

    /*
    * Adds a line of dialogue to the internal storage.
    * Lines are added to the front of the line storage vector array,
    * as such, they will be displayed last.
    */
    void addLine(string line);

    /*
    * Adds multiple lines of dialogue to the internal storage.
    * Lines are added to the front of the line storage vector array,
    * as such, they will be displayed last.
    */
    void addLines(vector<string> lines);

    /*
    * Gets all available dialogue lines from the internal storage.
    */
    vector<string> getLines();

    /*
    * Sets the character name for this object to the specified value.
    */
    void setName(string name);

    /*
    * Gets the currently set character name.
    */
    string getName();

    /*
    * Displays this object's contents to the console.
    * Equivalent to calling multiVNText(string, vector<string>, int, bool) with this object's name and line
    * storage as arguments.
    * All parameters are equivalent to their documented counterparts for that method.
    */
    void display(int speed, int maxWait, bool clearLast);
};

