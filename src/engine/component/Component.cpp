//
// Created by teeebor on 2017-10-05.
//

#include "Component.h"
namespace proton{
    void Component::update() {
    }

    void Component::end() {
    }

    void Component::start() {
    }

    void Component::addEntity(Entity *e) {
        mpEntity=e;
    }

    Entity &Component::getEntity() {
        return *mpEntity;
    }
}