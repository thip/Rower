#include "rower.h"

Rower::Rower(RowerConfig config) {
    this->pulseRatio = config.pulseRatio;
}

void Rower::AddPulse(int pulseTime) {
    time.add(pulseTime);
    distance.add(pulseTime, time.count()/this->pulseRatio);
    velocity.add(pulseTime, distance.delta()/time.delta());
    acceleration.add(pulseTime, velocity.delta()/time.delta());
}

void Rower::Update(RowerPresenter* presenter){
    presenter->Distance(distance.current());
    presenter->Velocity(velocity.average(10000)*1000.0f);
    presenter->Acceleration(acceleration.average()*1000000.0f);
}