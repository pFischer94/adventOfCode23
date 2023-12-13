#include <map>
#include <sstream>
#include "Hand.h"
using namespace std;

ostream& operator<<(ostream& os, const Hand& hand) {
    os << "Hand [ cards: " << hand.cards 
        << ", handType: " << hand.handType 
        << ", bid: " << setw(4) << hand.bid 
        << ", rank: " << setw(4) << hand.rank 
        << ", winning: " << setw(6) << hand.winning 
        << " ]"
        << endl;
    return os;
}

bool operator<(const Hand &hand1, const Hand &hand2) {
    if (hand1.handType > hand2.handType) {
        return true;
    } else if (hand1.handType < hand2.handType) {
        return false;
    } else {
        for (int i = 0; i < 5; i++) {
            if (hand1.getRankOfCardAtIndex(i) > hand2.getRankOfCardAtIndex(i)) {
                return true;
            } else if (hand1.getRankOfCardAtIndex(i) < hand2.getRankOfCardAtIndex(i)) {
                return false;
            }
        }
    }
    return false;
}

int Hand::getRankOfCardAtIndex(int index) const {
    char card = this->cards[index];
    switch (card) {
        case 'A': return 1;
        case 'K': return 2;
        case 'Q': return 3;
        case 'J': return 13;
        case 'T': return 4;
    }
    if (card < 50 || card > 57) {
        throw runtime_error("invalid card");
    }
    return 14 - (card - 48);
}

HandType Hand::getHandType() {
    HandType handType;

    map<char, int> cardsWithAmounts;
    for (char card : cards) {
        if (cardsWithAmounts.contains(card)) {
            cardsWithAmounts[card]++;
        } else {
            cardsWithAmounts[card] = 1;
        }
    }

    int amountOfJacks = 0;
    if (cardsWithAmounts.contains('J')) {
        amountOfJacks = cardsWithAmounts['J'];
    }

    int size = cardsWithAmounts.size();
    stringstream errS;
    errS << this << "   ";

    if (size == 1) {
        handType = HandType::FIVE_OF_A_KIND;

    } else if (size == 2) {
        handType = get4oakOrFH(cardsWithAmounts);

        if (handType == HandType::FOUR_OF_A_KIND) {
            if (amountOfJacks == 1) {
                handType = HandType::FIVE_OF_A_KIND;
            } else if (amountOfJacks == 4) {
                handType = HandType::FIVE_OF_A_KIND;
            } else if (amountOfJacks != 0) {
                errS << "invalid 4oak Jacks: " << amountOfJacks;
                throw runtime_error(errS.str());
            }

        } else if (handType == HandType::FULL_HOUSE) {
            if (amountOfJacks == 1) {
                handType = HandType::FOUR_OF_A_KIND;
            } else if (amountOfJacks == 2) {
                handType = HandType::FIVE_OF_A_KIND;
            } else if (amountOfJacks == 3) {
                handType = HandType::FIVE_OF_A_KIND;    //5JJ5J
            } else if (amountOfJacks != 0) {
                errS << "invalid Fh Jacks: " << amountOfJacks;
                throw runtime_error(errS.str());
            }

        } else {
            errS << "invalid handType for size = 2: " << handType;
            throw runtime_error(errS.str());
        }

    } else if (size == 3) {
        handType = get3oakOr2P(cardsWithAmounts);

        if (handType == HandType::THREE_OF_A_KIND) {
            if (amountOfJacks == 1) {
                handType = HandType::FOUR_OF_A_KIND;
            } else if (amountOfJacks == 2) {
                handType = HandType::FIVE_OF_A_KIND;
            } else if (amountOfJacks == 3) {
                handType = HandType::FOUR_OF_A_KIND;
            } else if (amountOfJacks != 0) {
                errS << "invalid 3oak Jacks: " << amountOfJacks;
                throw runtime_error(errS.str());
            }

        } else if (handType == HandType::TWO_PAIR) {
            if (amountOfJacks == 1) {
                handType = HandType::FULL_HOUSE;
            } else if (amountOfJacks == 2) {
                handType = HandType::FOUR_OF_A_KIND;
            } else if (amountOfJacks != 0) {
                errS << "invalid 2p Jacks: " << amountOfJacks;
                throw runtime_error(errS.str());
            }

        } else {
            errS << "invalid handType for size = 3: " << handType;
            throw runtime_error(errS.str());
        }

    } else if (size == 4) {
        handType = HandType::ONE_PAIR;
        if (amountOfJacks == 1) {
            handType = HandType::THREE_OF_A_KIND;
        } else if (amountOfJacks == 2) {
            handType = HandType::THREE_OF_A_KIND;
        } else if (amountOfJacks != 0) {
            errS << "invalid 1p Jacks: " << amountOfJacks;
            throw runtime_error(errS.str());
        }

    } else if (size == 5) {
        handType = HandType::HIGH_CARD;
        if (amountOfJacks == 1) {
            handType = HandType::ONE_PAIR;
        } else if (amountOfJacks != 0) {
            errS << "invalid Hc Jacks: " << amountOfJacks;
            throw runtime_error(errS.str());
        }

    } else {
        errS << "cardsWithAmounts.size() is invalid";
        throw runtime_error(errS.str());
    }

    return handType;
}

HandType Hand::get4oakOrFH(const map<char, int> &cardsWithAmounts) {
    auto it = cardsWithAmounts.begin();
    int amountOfFirstCard = it->second;
    int amountOfSecondCard = (++it)->second;
    if (amountOfFirstCard == 4 || amountOfSecondCard == 4) {
        return HandType::FOUR_OF_A_KIND;
    } else {
        return HandType::FULL_HOUSE;
    }
}

HandType Hand::get3oakOr2P(const map<char, int> &cardsWithAmounts) {
    auto it = cardsWithAmounts.begin();
    int amountOfFirstCard = it->second;
    int amountOfSecondCard = (++it)->second;
    int amountOfThirdCard = (++it)->second;
    if (amountOfFirstCard == 3 || amountOfSecondCard == 3 || amountOfThirdCard == 3) {
        return HandType::THREE_OF_A_KIND;
    } else {
        return HandType::TWO_PAIR;
    }
}

Hand::Hand(string cards, int bid) : cards(cards), bid(bid), rank(0), winning(0) {
    this->handType = getHandType();
}

vector<Hand> Hand::readHands(vector<string> lines) {
    vector<Hand> hands;
    for (string line : lines) {
        char* cards = strtok((char*) line.c_str(), " ");
        char* bidStr = strtok(NULL, " ");
        int bid = stoi(bidStr);
        hands.emplace_back(Hand(cards, bid));
    }
    return hands;
}

void Hand::rankHands(vector<Hand> &hands) {
    sort(hands.begin(), hands.end());
    for (int i = 0; i < hands.size(); i++) {
        hands[i].rank = i + 1;
    }
}

void Hand::writeWinnings(vector<Hand> &hands) {
    for (Hand& hand : hands) {
        hand.winning = hand.bid * hand.rank;
    }
}

int Hand::calculateTotalWinnings(const vector<Hand> &hands) {
    int sum = 0;
    for (const Hand& hand : hands) {
        sum += hand.winning;
    }
    return sum;
}
