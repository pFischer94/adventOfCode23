#ifndef TXTREADER_H
#define TXTREADER_H

#include <fstream>
#include <iostream>
using namespace std;

class TxtReader {

    string path;
    vector<string> lines;

public:
    TxtReader(string path);
    vector<string> getLines();

};

TxtReader::TxtReader(string path) : path(path) {
    ifstream inStream(this->path);
    string line;
    while (getline(inStream, line)) {
        this->lines.emplace_back(line);
    }
    inStream.close();
}

vector<string> TxtReader::getLines() {
    return this->lines;
}

#endif