#include <map>
#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "Card.h"

int main() {
    MethodFrame mF = MethodFrame("Day4.cpp -> main");
    mF.printStart();

    // vector<Card> cards;
    int sumOfPoints = 0;

    TxtReader reader("../../inputs/input4.txt");
    vector<string> lines = reader.getLines();

    for (int index = 0; index < lines.size(); index++) {
        // Part 1
        sumOfPoints += Card(lines[index]).getPoints();

        // Part 2 slow
        // vector<Card> cardWithCopies = Card::createCardAndCopies(lines, index);
        // cards.insert(cards.end(), cardWithCopies.begin(), cardWithCopies.end());
    }
    
    // Part 2 quick
    int amountOfCards = lines.size();
    map<int, int> copiesByLines;

    for (int index = lines.size() - 1; index >= 0; index--) {
        int numOfCopies = 0;
        int matches = Card::getNumOfMatches(lines[index]);

        for (int addIndex = 1; addIndex <= matches; addIndex++) {
            int copyIndex = index + addIndex;
            if (copyIndex < lines.size()) {
                numOfCopies += 1 + copiesByLines[copyIndex];
            }
        }
        copiesByLines[index] = numOfCopies;
        amountOfCards += numOfCopies;

        cout << "index: " << index << ", matches: " << matches << ", numOfCopies: " << numOfCopies << endl;
    }


    // Part 1
    cout << "sumOfPoints: " << sumOfPoints << endl;
    // Part 2 slow
    // cout << "amountOfCards: " << cards.size() << endl;
    // Part 2 quick
    cout << "amountOfCards: " << amountOfCards << endl;

    mF.printEnd();
    return 0;
}

// Dozenten für kommende Themen

// Danny
// Pascal Azure
// DBs Pascal Sarah
// neuer Bredex Alex Azure

// kein Moritz, kein Christian
// Jonas, Danny, Julian, Pascal, SARAH, Dominik vdH oder Olli Hock
// nach Möglichkeit wer das Skript geschrieben hat
// sarah.pagliar

// 1 Musterlösung pro Aufgabe