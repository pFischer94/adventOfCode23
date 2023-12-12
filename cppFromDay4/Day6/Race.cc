#include <iostream>
#include <iomanip>
#include "Race.h"
#include "Boat.h"
using namespace std;

ostream& operator<<(ostream& os, const Race& race) {
    os << "Race [ time: " << race.time << "    record: " << setw(4) << race.record << "    amountOfWaysToBeatRecord: " << race.amountOfWaysToBeatRecord << " ]";
    return os;
}

vector<Race> Race::readRaces(const vector<string>& lines) {
    vector<Race> races;
    vector<string> timeStrings;
    vector<string> recordStrings;

    char* timeStr = strtok((char*) lines[0].c_str(), " ");
    while ((timeStr = strtok(NULL, " ")) != NULL) {
        timeStrings.emplace_back(timeStr);
    }
    char* recordStr = strtok((char*) lines[1].c_str(), " ");
    while ((recordStr = strtok(NULL, " ")) != NULL) {
        recordStrings.emplace_back(recordStr);
    }

    for (int index = 0; index < timeStrings.size(); index++) {
        long time = stol(timeStrings[index]);
        long record = stol(recordStrings[index]);
        races.emplace_back(Race(time, record));
    }

    return races;
}

Race Race::readRacePart2(const vector<string> &lines) {
    string timeStr = "";
    string recordStr = "";

    char* timePart = strtok((char*) lines[0].c_str(), " ");
    while ((timePart = strtok(NULL, " ")) != NULL) {
        timeStr += timePart;
    }
    char* recordPart = strtok((char*) lines[1].c_str(), " ");
    while ((recordPart = strtok(NULL, " ")) != NULL) {
        recordStr += recordPart;
    }

    return Race(stol(timeStr), stol(recordStr));
}

long Race::countWaysToBeatRecord() {
    long counter = 0;

    for (long chargingTime = 0; chargingTime <= this->time; chargingTime++) {
        Boat boat(chargingTime);
        long distanceTravelled = boat.absolve(*this);
        if (distanceTravelled > this->record) {
            counter++;
        }
    }

    return counter;
}

long Race::calculateWaysToBeatRecord() {
    long lowestWinningCharge = 0.5 * this->time - sqrt(0.25 * this->time * this->time - this->record);
    cout << "lowestWinningCharge: " << lowestWinningCharge << endl;
    long highestWinningCharge = 0.5 * this->time + sqrt(0.25 * this->time * this->time - this->record);
    cout << "highestWinningCharge: " << highestWinningCharge << endl;
    long amountOfWinningCharges = highestWinningCharge - lowestWinningCharge;
    return amountOfWinningCharges;
}

long Race::getTime() {
    return this->time;
}

long Race::getAmountOfWaysToBeatRecord() {
    return this->amountOfWaysToBeatRecord;
}
