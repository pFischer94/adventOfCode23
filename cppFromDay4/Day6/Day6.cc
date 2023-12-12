#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "Race.cc"
#include "Boat.cc"

long solvePart2(vector<string> lines);
long solvePart1(vector<string> lines);
void printRaces(const vector<Race>& races);

int main() {
    MethodFrame mF("Day6.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input6.txt").getLines();
    
    long productOfWays = solvePart2(lines);

    mF.printEnd();
    return 0;
}

long solvePart2(vector<string> lines) {
    Race race = Race::readRacePart2(lines);

    cout.imbue(locale(""));
    cout << race << endl;

    long amountOfWaysToBeatTheRecord = race.calculateWaysToBeatRecord();
    cout.imbue(locale("C"));
    cout << "amountOfWaysToBeatTheRecord: " << amountOfWaysToBeatTheRecord << endl;

    return amountOfWaysToBeatTheRecord;
}

long solvePart1(vector<string> lines) {
    long productOfWays = 1;
    vector<Race> races = Race::readRaces(lines);

    printRaces(races);
    cout << endl;

    for (Race race : races) {
        productOfWays *= race.getAmountOfWaysToBeatRecord();
    }

    cout << "productOfWays: " << productOfWays << endl;

    return productOfWays;
}

void printRaces(const vector<Race> &races) {
    for (Race race : races) {
        cout << race << endl;
    }
}
