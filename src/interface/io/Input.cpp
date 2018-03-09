//
// Created by teeebor on 2018-03-08.
//

#include "../../../include/io/Input.h"
#include <GLFW/glfw3.h>
Input *Input::instance=nullptr;
InputState PROTON_API GLFW_INPUT_TO_PROTON(int action) {
    switch (action) {
        case GLFW_RELEASE:
            return InputState::RELEASE;
        case GLFW_REPEAT:
            return InputState::DOWN;
        case GLFW_PRESS:
            return InputState::PRESS;
        default:
            return InputState::NONE;
    }
}

BaseInput::BaseInput(int input) {
    m_Input = input;
    m_State = InputState::NONE;
}

InputState BaseInput::state() {
    return m_State;
}

void BaseInput::setState(InputState state) {
    m_State = state;
}

bool BaseInput::is(int state) {
    return m_State & state;
}


void Input::setInput(int input, InputState state) {
    BaseInput *inp = nullptr;
    for (BaseInput *i : inputs) {
        if (i->m_Input == input) {
            inp = i;
        }
    }
    if (!inp) {
        inp = new BaseInput(input);
        inputs.push_back(inp);
    }
    inp->setState(state);
}

void Input::update() {
    for (StateChange s : change) {
//            if (s.input->state() == InputState::PRESS) {
//                s.input->setState(InputState::DOWN);
//            }
        if (s.input->state() == InputState::RELEASE) {
            s.input->setState(InputState::NONE);
        }
    }
    change.clear();
}

InputState Input::State(int input) {
    for (BaseInput *i : inputs) {
        if (i->m_Input == input) {
            return i->state();
        }
    }
    return InputState::NONE;
}

BaseInput* Input::Get(int input) {
    for(BaseInput *i : inputs){
        if(i->m_Input == input){
            return i;
        }
    }
    BaseInput *inp = new BaseInput(input);
    inputs.push_back(inp);
    return inp;
}

Input *Input::getInstance() {
    if(!Input::instance){
        Input::instance = new Input();
    }
    return Input::instance;
}

Input::Input() {
    LOG("input","init");
}
