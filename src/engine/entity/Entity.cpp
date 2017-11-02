//
// Created by teeebor on 2017-10-05.
//

#include "Entity.h"
#include "../component/Component.h"
#include "../component/Transform.h"
#include "../component/Renderer.h"

namespace proton {

    Entity::Entity() = default {
        mpRenderer= nullptr;
        mpTransform = new Transform();
    }

    Entity::~Entity() = default {
        delete mpTransform;
        delete[] mpComponentList;
    }

    void Entity::addComponent(Component &comp) {
        if(nullptr != dynamic_cast<Renderer*>(&comp)){
            mpRenderer= static_cast<Renderer*>(&comp);
        }else{
            mpComponentList.push_back(&comp);
        }
    }

    Transform &Entity::transform() {
        return *mpTransform;
    }

    Entity * Entity::parent() {
        return mpParent;
    }

    void Entity::addChild(Entity &child) {
        child.mpParent = this;
        mpChildList.push_back(&child);
    }
}