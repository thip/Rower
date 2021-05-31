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
        int pulseCount;
        float pulseRatio;
        int lastPulse;
        float lastDistance;
        float lastVelocity;
        RowerPresenter* presenter;
};

#endif