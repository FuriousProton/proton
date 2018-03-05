//
// Created by teeebor on 2017-10-05.
//

#include "../../../include/component/Component.h"
#include "../../../include/Proton.h"

namespace proton{
    void Component::update() {
    }

    void Component::end() {
    }

    void Component::start() {
    }

    void Component::setEntity(Entity *e) {
        mpEntity=e;
    }

    Entity &Component::getEntity() {
        return *mpEntity;
    }

    bool Component::getKeyDown(int key) {
        if(Proton::keyStates.count(key)){
            return Proton::keyStates[key]==2;
        }
        return false;
    }

    bool Component::getKeyUp(int key) {
        if(Proton::keyStates.count(key)){
            return Proton::keyStates[key]==0;
        }
        return false;
    }

    bool Component::getKeyPress(int key) {
        if(Proton::keyStates.count(key)){
            return Proton::keyStates[key]==1;
        }
        return false;
    }
}