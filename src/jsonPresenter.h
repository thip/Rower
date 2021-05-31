#ifndef JSONPRESENTER_H
#define JSONPRESENTER_H

#include <functional>
#include "rowerPresenter.h"

typedef std::function<void(char *json)> jsonCallback;

class JsonPresenter : public RowerPresenter {
    public:
        void Distance(float distance) override;
        void Velocity(float velocity) override;
        void Present(jsonCallback callback);

    private:
        float distance;
        float velocity;
};

#endif