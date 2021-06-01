#include  <stdio.h>
#include "jsonPresenter.h"


void JsonPresenter::Distance(float distance) {
    this->distance=distance;
}

void JsonPresenter::Velocity(float velocity) {
    this->velocity = velocity;
}

void JsonPresenter::Acceleration(float accceleration) {
    this->acceleration  = accceleration;
}

void JsonPresenter::Present(stringCallback callback) {
    char buffer[64];
    
    snprintf(buffer, sizeof buffer, 
        "{\"distance\":%.0f,\"velocity\":%.2f,\"acceleration\":%.2f}", 
        this->distance, this->velocity, this->acceleration);

    callback(buffer);
}