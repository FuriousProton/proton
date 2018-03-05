//
// Created by teeebor on 2017-12-26.
//

#pragma once

#include "utility.h"

class PROTON_API CustomEvent {
public:
    int a;
    void *classPointer;
    CustomEvent() {}
};

class PROTON_API KeyEvent : public CustomEvent {
public:
    const int key;
    const int scanCode;
    const int action; //up, press, down
    const int mods; //shift, ctrl, alt

    KeyEvent(int key, int scanCode, int action, int mods)
            : CustomEvent(), key(key), scanCode(scanCode), action(action), mods(mods) {}
};

class PROTON_API MoveEvent : public CustomEvent {
public:
    const double posX, posY;

    MoveEvent(double posX, double posY) : CustomEvent(), posX(posX), posY(posY) {}
};
