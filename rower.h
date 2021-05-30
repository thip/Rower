#ifndef ROWER_H
#define ROWER_H

#include "rowerPresenter.h"

class RowerConfig {
    public:
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
        RowerPresenter* presenter;
};

#endif