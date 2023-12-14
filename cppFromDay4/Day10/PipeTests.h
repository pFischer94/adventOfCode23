#ifndef PIPE_TESTS_H
#define PIPE_TESTS_H

#include "Pipe.cpp"
using namespace std;

class PipeTests {

    static const int WIDTH = 30;
    inline static const string GREEN = "\033[32m";
    inline static const string RED = "\033[31m";
    inline static const string RESET = "\033[0m";

    void static testFindSColInRow();
    void static testFindDirectionOfNext();
    void static testFindNext();
    void static testFindNextUntilS();
    void static testFindNextFromS();
    void static testFindS();
    // deprecated
    void static testGetAdjacents();
    
    friend int main();

};

#endif