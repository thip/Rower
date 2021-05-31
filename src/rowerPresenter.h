#ifndef ROWERPRESENTER_H
#define ROWERPRESENTER_H


class RowerPresenter {
    public:
        virtual void Distance(float distance) = 0;
        virtual void Velocity(float velocity) = 0;
};

#endif