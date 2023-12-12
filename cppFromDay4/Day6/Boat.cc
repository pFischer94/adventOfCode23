#include "Boat.h"

int Boat::absolve(Race race) {
    int chargingTime = this->speed;
    int timeLeft = race.getTime() - chargingTime;
    int travelDistance = timeLeft * this->speed;
    return travelDistance;
}