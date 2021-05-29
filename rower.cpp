#include "rower.h"

Rower::Rower(RowerConfig config) {
    this->pulseRatio = config.pulseRatio;
    this->presenter = config.presenter;
}

void Rower::AddPulse(int time) {
    this->pulseCount++;
    float distance = this->pulseCount/this->pulseRatio;
    this->presenter->Distance(distance);
}