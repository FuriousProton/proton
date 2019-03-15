//
// Created by teeebor on 2017-11-27.
//

#include "Move.h"
#include "../../../include/component/Transform.h"
#include "../../../include/utility.h"

void proton::Move::start() {
    Component::start();
}

void proton::Move::update() {
    Component::update();
    if(getKeyDown(KEY_W)){
        mpEntity->transform().move(glm::vec3(0,0,.01f));
    }
}

void proton::Move::end() {
    Component::end();
}
