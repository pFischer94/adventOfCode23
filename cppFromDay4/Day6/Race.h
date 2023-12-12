#ifndef RACE_H
#define RACE_H

class Race {

    long time;
    long record;
    long amountOfWaysToBeatRecord;

    friend ostream& operator<<(ostream& os, const Race& race);

public:
    Race(long time, long record) : time(time), record(record) {
        this->amountOfWaysToBeatRecord = this->countWaysToBeatRecord();
    }
    static vector<Race> readRaces(const vector<string>& lines);
    static Race readRacePart2(const vector<string>& lines);
    long countWaysToBeatRecord();
    long calculateWaysToBeatRecord();
    
    long getTime();
    long getAmountOfWaysToBeatRecord();

};

#endif