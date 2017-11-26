//
// Created by teeebor on 2017-10-05.
//

#include "Entity.h"
#include "../component/Component.h"
#include "../component/Transform.h"
#include "../component/Renderer.h"
#include "../../utility.h"

namespace proton {

    Entity::Entity():mpParent(nullptr) {
        setup();
    }

    void Entity::setup(){
        mpRenderer= nullptr;
        mpTransform = new Transform();
        mpTransform->setEntity(this);
    }


    Entity::~Entity() {
        delete mpTransform;
        delete mpRenderer;
        for(Component *c : mpComponentList){
            delete(c);
        }
        for(Entity *e : mpChildList){
            delete(e);
        }
    }

    void Entity::addComponent(Component *comp) {
        comp->setEntity(this);
        LOG("ENTITY","ADDING COMPONENT");
        if(nullptr != dynamic_cast<Renderer*>(comp)){
            LOG("ENTITY","Renderer");
            mpRenderer= dynamic_cast<Renderer*>(comp);
        }else{
            LOG("ENTITY","Other");
            mpComponentList.push_back(comp);
        }
    }

    Transform &Entity::transform() {
        return *mpTransform;
    }

    Entity * Entity::parent() {
        if(mpParent)
            return mpParent;
        return nullptr;
    }

    void Entity::addChild(Entity &child) {
        child.mpParent = this;
        mpChildList.push_back(&child);
    }
}