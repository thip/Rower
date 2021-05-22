#include "rower.h"

void Rower::AddPulse(int time) {
    this->pulseCount++;
}

float Rower::GetDistance() {
    return this->pulseCount/4.805f;
}