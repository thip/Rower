#include "rower.h"

Rower::Rower(RowerConfig config) {
    this->pulseRatio = config.pulseRatio;
    this->presenter = config.presenter;
}

void Rower::AddPulse(int pulseTime) {
    this->pulseCount++;

    time.add(pulseTime);
    distance.add(this->pulseCount/this->pulseRatio);
    velocity.add(distance.delta()/time.delta());
    acceleration.add(velocity.delta()/time.delta());

    this->presenter->Distance(distance.current());
    this->presenter->Velocity(velocity.average()*1000.0f);
    this->presenter->Acceleration(acceleration.average()*1000000.0f);
}