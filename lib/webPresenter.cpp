#include "../lib/webPresenter.h"


void WebPresenter::Distance(float distance) {
    this->distance = distance;
}

void WebPresenter::Velocity(float velocity) {
    if (velocity > 100 || velocity < 0){
        this->velocity = 0;
        return;
    }
    this->velocity = velocity;
}