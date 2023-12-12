#ifndef BOAT_H
#define BOAT_H

#include "Race.h"

class Boat {

    int speed;

public:
    Boat(int speed) : speed(speed) {}
    int absolve(Race race);

};

#endif