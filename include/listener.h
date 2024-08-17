#ifndef LISTENER_H_
#define LISTENER_H_

#include "basic.h"

class Listener {
private:
    CState snd_state, rcv_state;
public:
    Listener();

    std::function<void()> Run;

    void set_state(CState &);
    CState get_state();
};

#endif
