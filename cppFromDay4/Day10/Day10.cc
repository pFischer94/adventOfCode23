#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "Pipe.cpp"

int main() {
    MethodFrame mF("Day10.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input10.txt").getLines();

    Pipe* s = Pipe::findS(lines);
    Pipe* curr = s->findNextFromS(lines);

    while (curr->getDistance() < 100000 && curr->getForm() != 'S') {
        curr->setNext(curr->findNext(lines));
        curr = curr->getNext();
    }
    
    long loopDistance = curr->getDistance();
    long farthestDistance = loopDistance / 2;
    cout << "farthestDistance: " << farthestDistance << endl;

    delete s;
    mF.printEnd();
    return 0;
}
