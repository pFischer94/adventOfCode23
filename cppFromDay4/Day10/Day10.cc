#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "Pipe.cpp"

int main() {
    MethodFrame mF("Day10.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input10.txt").getLines();

    Pipe* s = Pipe::findS(lines);
    Pipe* curr = s->findNextFromS(lines);

    delete s;
    mF.printEnd();
    return 0;
}
