#ifndef HAND_H
#define HAND_H

#include <iomanip>
#include "HandType.h"
using namespace std;

class Hand {

    string cards;
    int bid;
    HandType handType;
    int rank;
    int winning;

    int getRankOfCardAtIndex(int index) const;
    HandType getHandType();
    static HandType get4oakOrFH(const map<char, int>& cardsWithAmounts);
    static HandType get3oakOr2P(const map<char, int>& cardsWithAmounts);

    friend ostream& operator<<(ostream& os, const Hand& hand);
    friend bool operator<(const Hand& hand1, const Hand& hand2);

public:
    Hand(string cards, int bid);
    static vector<Hand> readHands(vector<string> lines);
    static void rankHands(vector<Hand>& hands);
    static void writeWinnings(vector<Hand>& hands);
    static int calculateTotalWinnings(const vector<Hand>& hands);

};

#endif