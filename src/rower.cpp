#include "rower.h"

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

    velocities[velocitiesHead] = deltaS/deltaT;    
    float deltaV = this->velocities[velocitiesHead]-this->velocities[(velocitiesHead+4)%5];
    velocitiesHead = (velocitiesHead+1)%5;

    accelerations[accelerationsHead] = deltaV/deltaT;
    accelerationsHead = (accelerationsHead+1)%3;

    float velocity = 0;
    for (int i = 0; i < 5; i++){
        velocity += velocities[i];
    }
    velocity = velocity/5;

    float acceleration = 0;
    for (int i = 0; i < 3; i++){
        acceleration += accelerations[i];
    }
    acceleration = acceleration/3;

    this->presenter->Distance(distance);
    this->presenter->Velocity(velocity);
    this->presenter->Acceleration(acceleration);
}