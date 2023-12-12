#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "Hand.cpp"

void printHands(const vector<Hand>& hands);

int main() {
    MethodFrame mF("Day7.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input7.txt").getLines();

    vector<Hand> hands = Hand::readHands(lines);
    printHands(hands);
    cout << endl;

    Hand::rankHands(hands);
    Hand::writeWinnings(hands);
    printHands(hands);
    cout << endl;

    int sum = Hand::calculateTotalWinnings(hands);
    cout << "Total Winnings: " << sum << endl;

    mF.printEnd();
    return 0;
}

void printHands(const vector<Hand>& hands) {
    for (const Hand& hand : hands) {
        cout << hand << endl;
    }
}
