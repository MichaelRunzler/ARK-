#include "stdafx.h"
#include "VNSequence.h"

VNSequence::VNSequence(){
    lines = vector<string>();
    name = "";
}

VNSequence::VNSequence(string name) {
    lines = vector<string>();
    this->name = name;
}

VNSequence::VNSequence(string name, vector<string> lines) {
    this->name = name;
    this->lines = vector<string>();

    // Copy all elements in order
    for (iter = lines.begin(); iter != lines.end(); iter++) 
        this->lines.push_back(*iter);
}

void VNSequence::addLine(string line){
    lines.push_back(line);
}

void VNSequence::addLines(vector<string> lines) {
    for (iter = lines.begin(); iter != lines.end(); iter++)
        this->lines.push_back(*iter);
}

vector<string> VNSequence::getLines() {
    return lines;
}

void VNSequence::setName(string name) {
    this->name = name;
}

string VNSequence::getName() {
    return name;
}

void VNSequence::display(int speed, int delay, bool clearLast){
    multiVNText(this->name, this->lines, speed, delay, clearLast);
}

VNSequence::~VNSequence()
{
}
