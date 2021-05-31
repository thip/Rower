#ifndef JSONPRESENTER_H
#define JSONPRESENTER_H

#include "stringPresenter.h"
#include "rowerPresenter.h"


class JsonPresenter : public RowerPresenter, public StringPresenter {
    public:
        void Distance(float distance) override;
        void Velocity(float velocity) override;
        void Acceleration(float acceleration) override;
        void Present(stringCallback callback) override;

    private:
        float distance;
        float velocity;
        float acceleration;
};

#endif