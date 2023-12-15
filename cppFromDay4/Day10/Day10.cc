#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "Pipe.cpp"

int main() {
    MethodFrame mF("Day10.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input10.txt").getLines();

    Pipe* s = Pipe::findS(lines);
    Pipe* curr = s->getNext();

    while (curr->getForm() != 'S') {
        curr->setNext(curr->findNext(lines));
        lines[curr->getRow()][curr->getCol()] = 'X';
        curr = curr->getNext();
    }
    cout << "curr: " << *curr << endl;
    s->setDirectionFrom(curr->getDirectionFrom());
    cout << "s:    " << *s << endl << endl;
    
    long loopDistance = curr->getDistance();
    long farthestDistance = loopDistance / 2;
    cout << "farthestDistance: " << farthestDistance << endl;

    for (string& line : lines) {
        for (char& c : line) {
            c = ' ';
        }
    }
    
    Pipe* loop = s;
    while (loop->getNext() != nullptr) {
        loop = loop->getNext();
        lines[loop->getRow()][loop->getCol()] = loop->getForm();
    }

    for (string& line : lines) {
        cout << line << endl;
    }

    long enclosedTiles = s->countEnclosedTiles(lines);
    cout << "enclosedTiles: " << enclosedTiles << endl;

    delete s;
    delete curr;
    mF.printEnd();
    return 0;
}
