#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;

class Card {

    int id;
    string line;
    vector<int> winningNumbers;
    vector<int> ownNumbers;
    int numOfMatches;
    int points;

    int parseGameId(string gameStr);
    vector<int> parseWinningNumbers(string numbersStr);
    vector<int> parseOwnNumbers(string numbersStr);
    int calculateNumOfMatches();
    int calculatePoints();

public:
    Card(string line);
    static int countCopies(vector<string> lines);
    static int countCopies(vector<string> lines, int index);
    static int getNumOfMatches(string line);
    static vector<Card> createCardAndCopies(vector<string> lines, int index);
    int getNumOfMatches();
    int getPoints();
    void print();

};

Card::Card(string line) : line(line) {
    string gameStr = strtok((char*) this->line.c_str(), ":");
    string numbersStr = strtok(NULL, ":");
    string winningNumbersStr = strtok((char*) numbersStr.c_str(), "|");
    string ownNumbersStr = strtok(NULL, "|");

    this->id = this->parseGameId(gameStr);
    this->winningNumbers = this->parseWinningNumbers(winningNumbersStr);
    this->ownNumbers = this->parseOwnNumbers(ownNumbersStr);
    this->numOfMatches = calculateNumOfMatches();
    this->points = calculatePoints();
}

int Card::getNumOfMatches(string line) {
    string gameStr = strtok((char*) line.c_str(), ":");
    string numbersStr = strtok(NULL, ":");
    string winningNumbersStr = strtok((char*) numbersStr.c_str(), "|");
    string ownNumbersStr = strtok(NULL, "|");

    vector<int> winningNumbers;
    char* winningNumberStr = strtok((char*) winningNumbersStr.c_str(), " ");
    while (winningNumberStr != NULL) {
        winningNumbers.emplace_back(stoi(winningNumberStr));
        winningNumberStr = strtok(NULL, " ");
    }
    
    vector<int> ownNumbers;
    char* ownNumberStr = strtok((char*) ownNumbersStr.c_str(), " ");
    while (ownNumberStr != NULL) {
        ownNumbers.emplace_back(stoi(ownNumberStr));
        ownNumberStr = strtok(NULL, " ");
    }

    int numOfMatches = 0;
    for (int num : winningNumbers) {
        if (find (ownNumbers.begin(), ownNumbers.end(), num) != ownNumbers.end()) {
            numOfMatches++;
        }
    }

    return numOfMatches;
}

// int Card::countCopies(vector<string> lines) {
//     int numOfCopies = 0;

//     for (int index = 0; index < lines.size(); index++) {
//         string line = lines[index];
//         for (int addIndex = 1; addIndex <= Card::getNumOfMatches(line); addIndex++) {
//             if (index + addIndex < lines.size()) {

//                 cout << "index: " << index << ", numOfMatches: " << Card::getNumOfMatches(line) << ", index + addIndex: " << index + addIndex << ", lines.size(): " << lines.size() << endl;

//                 numOfCopies += Card::countCopies(lines, index + addIndex);
//             }
//         }
//     }
    
//     return numOfCopies;
// }

int Card::countCopies(vector<string> lines, int index) {
    int numOfCopies = 0;
    
    string line = lines[index];
    for (int addIndex = 1; addIndex <= Card::getNumOfMatches(line); addIndex++) {
        if (index + addIndex < lines.size()) {
            numOfCopies += Card::countCopies(lines, index + addIndex);
        }
    }
    
    return numOfCopies;
}

vector<Card> Card::createCardAndCopies(vector<string> lines, int index){
    vector<Card> cardAndCopies;
    Card originalCard(lines[index]);

    cardAndCopies.emplace_back(originalCard);
    for (int addIndex = 1; addIndex <= originalCard.getNumOfMatches(); addIndex++) {
        if (index + addIndex < lines.size()) {
            vector<Card> copies = Card::createCardAndCopies(lines, index + addIndex);
            cardAndCopies.insert(cardAndCopies.end(), copies.begin(), copies.end());
        }
    }

    return cardAndCopies;
}

int Card::parseGameId(string gameStr) {
    strtok((char*) gameStr.c_str(), " ");
    string idStr = strtok(NULL, " ");

    return stoi(idStr);
}

vector<int> Card::parseWinningNumbers(string winningNumbersStr) {
    vector<int> winningNumbers;
    char* numberStr = strtok((char*) winningNumbersStr.c_str(), " ");

    while (numberStr != NULL) {
        winningNumbers.emplace_back(stoi(numberStr));
        numberStr = strtok(NULL, " ");
    }

    return winningNumbers;
}

vector<int> Card::parseOwnNumbers(string ownNumbersStr) {
    vector<int> ownNumbers;
    char* numberStr = strtok((char*) ownNumbersStr.c_str(), " ");

    while (numberStr != NULL) {
        ownNumbers.emplace_back(stoi(numberStr));
        numberStr = strtok(NULL, " ");
    }

    return ownNumbers;
}

int Card::calculateNumOfMatches(){
    int numOfMatches = 0;

    for (int num : this->winningNumbers) {
        if (find(this->ownNumbers.begin(), this->ownNumbers.end(), num) != this->ownNumbers.end()) {
            numOfMatches++;
        }
    }

    return numOfMatches;
}

int Card::calculatePoints() {
    return this->numOfMatches == 0 ? 0 : pow(2, this->numOfMatches - 1);
}

int Card::getNumOfMatches() {
    return this->numOfMatches;
}

int Card::getPoints() {
    return this->points;
}

void Card::print() {
    cout << "Card [" << endl
            << " id: " << this->id << endl 
            << " line: " << this->line << endl
            << " winningNumbers: ";
    for (int num : this->winningNumbers) {
        cout << num << ", ";
    }
    cout << endl << " ownNumbers: ";
    for (int num : this->ownNumbers) {
        cout << num << ", ";
    }
    cout << endl << " points: " << this->points << endl
            << "]" << endl;
}

#endif