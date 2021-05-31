#ifndef ROWER_H
#define ROWER_H

#include "rowerPresenter.h"

struct RowerConfig {
    float pulseRatio;
    RowerPresenter* presenter;
};

class Rower {
    public:
        Rower(RowerConfig config);
        void AddPulse(int time);
    
    private:
        
        int lastPulse = 0;
        int pulseCount = 0;
        float lastDistance = 0;

        int velocitiesHead = 0;
        float velocities[5] = {};

        int accelerationsHead = 0;
        float accelerations[3] = {};

        float pulseRatio;
        RowerPresenter* presenter;
};

#endif