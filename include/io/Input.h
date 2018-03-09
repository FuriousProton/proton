//
// Created by teeebor on 2018-03-06.
//

#pragma once

#include <vector>
#include "../EventManager.h"


enum InputState {
    NONE=0x01, PRESS=0x02, RELEASE=0x04, DOWN=0x08, MOVE=0x16
};

InputState PROTON_API GLFW_INPUT_TO_PROTON(int action);

struct PROTON_API BaseInput {
    int m_Input;
protected:
    InputState m_State;
public:
    BaseInput(int input);

    InputState state();
///
/// \param state
/// \return
    bool is(int state);
    void setState(InputState state);
};


class PROTON_API Input {
    struct StateChange {
        BaseInput *input;
        int newState;
    };
    std::vector<StateChange> change;
    std::vector<BaseInput *> inputs;
    static Input *instance;
    Input();
public:
    static Input *getInstance();
    void setInput(int input, InputState state);

    void update();

    InputState State(int input);

    BaseInput *Get(int input);
};