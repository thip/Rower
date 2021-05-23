#include "rower.h"

Rower::Rower() {
    this->pulseRatio = 4.805f;
}

void Rower::AddPulse(int time) {
    this->pulseCount++;
}

float Rower::GetDistance() {
    return this->pulseCount/this->pulseRatio;
}

int Rower::GetSplit(int index) {
    return this->pulseCount-(1202*index);
}