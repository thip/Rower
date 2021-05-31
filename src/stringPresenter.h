#ifndef STRINGPRESENTER_H
#define STRINGPRESENTER_H

#include <functional>

typedef std::function<void(char *string)> stringCallback;

class StringPresenter {
    public:
        virtual void Present(stringCallback callback) = 0;
};

#endif