//
// Created by teeebor on 2017-11-18.
//

#include "DemoComponent.h"
#include "Transform.h"

void proton::DemoComponent::start() {
    Component::start();
}

void proton::DemoComponent::update() {
    mpEntity->transform().rotate(glm::vec3(0,.005f,0));
    Component::update();
}

void proton::DemoComponent::end() {
    Component::end();
}
