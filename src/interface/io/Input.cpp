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
    auto inp = Get(input);
    inp->setState(state);
}
void Input::setMouseInput(int button, InputState state) {
    auto inp = GetMouseButton(button);
//    if(state==RELEASE){
//        change.push_back({inp, NONE});
//    }
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
    mouseMove->dX=0;
    mouseMove->dY=0;
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

BaseInput* Input::GetMouseButton(int input) {
    for(BaseInput *i : mouseButtons){
        if(i->m_Input == input){
            return i;
        }
    }
    BaseInput *inp = new BaseInput(input);
    mouseButtons.push_back(inp);
    return inp;
}

Input *Input::getInstance() {
    if(!Input::instance){
        Input::instance = new Input();
    }
    return Input::instance;
}

Input::Input() {
    mouseMove = new MouseMove();
    mouseMove->dX=0;
    mouseMove->dY=0;
    mouseMove->x=0;
    mouseMove->y=0;
    LOG("input","init");
}

void Input::setMouse(double x, double y){
    mouseMove->dX = x-mouseMove->x;
    mouseMove->dY = y-mouseMove->y;
    mouseMove->x=x;
    mouseMove->y=y;
}

MouseMove Input::Cursor() {
    return *mouseMove;
}

