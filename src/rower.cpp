#include "rower.h"

Rower::Rower(RowerConfig config) {
    this->pulseRatio = config.pulseRatio;
    this->presenter = config.presenter;
}

void Rower::AddPulse(int pulseTime) {
    time.add(pulseTime);
    distance.add(pulseTime, time.count()/this->pulseRatio);
    velocity.add(pulseTime, distance.delta()/time.delta());
    acceleration.add(pulseTime, velocity.delta()/time.delta());

    this->presenter->Distance(distance.current());
    this->presenter->Velocity(velocity.average(10000)*1000.0f);
    this->presenter->Acceleration(acceleration.average()*1000000.0f);
}