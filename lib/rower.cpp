#include "../lib/rower.h"

Rower::Rower(RowerConfig config) {
    this->pulseRatio = config.pulseRatio;
    this->presenter = config.presenter;
}

void Rower::AddPulse(int time) {
    this->pulseCount++;

    float deltaT = (time - this->lastPulse)/1000.0f;
    float distance = this->pulseCount/this->pulseRatio;
    this->lastPulse = time;

    float deltaS = distance - this->lastDistance;
    this->lastDistance = distance;


    float velocity = deltaS/deltaT;

    this->presenter->Distance(distance);
    this->presenter->Velocity(velocity);

    
}