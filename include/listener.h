#ifndef LISTENER_H_
#define LISTENER_H_

#include "basic.h"

class Listener {
private:
    CState m_state;
public:
    Listener();

    std::function<void()> Run;

    CState get_state();
};

#endif
