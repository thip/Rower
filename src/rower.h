#ifndef ROWER_H
#define ROWER_H

#include "rowerPresenter.h"
#include "aggregator.h"

struct RowerConfig {
    float pulseRatio;
};

class Rower {
    public:
        Rower(RowerConfig config);
        void AddPulse(int time);
        void Update(RowerPresenter* presenter);
    
    private:
        Aggregator<int, 2> time;
        Aggregator<float, 2> distance;
        Aggregator<float, 256> velocity;
        Aggregator<float, 6> acceleration;

        float pulseRatio;
};



#endif