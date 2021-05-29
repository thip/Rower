#ifndef WEBPRESENTER_H
#define WEBPRESENTER_H

#include "rowerPresenter.h"

class WebPresenter : public RowerPresenter {
    public:
        void Distance(float distance) override;
        float distance;
};

#endif