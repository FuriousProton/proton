//
// Created by teeebor on 2017-10-05.
//

#include "Entity.h"
#include "../component/Component.h"
#include "../component/Transform.h"
#include "../component/Renderer.h"
#include "../../utility.h"
#include "Camera.h"
#include "../Scene.h"

namespace proton {

    Entity::Entity():mpParent(nullptr) {
        setup();
    }

    void Entity::setup(){
        mpRenderer= nullptr;
        mpTransform = new Transform();
        mpTransform->setEntity(this);
        mpTransform->start();
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

        if (nullptr != dynamic_cast<Camera *>(&child)) {
            LOG("Scene","Adding camera");
            if (Scene::activeScene->mMainCamera < 0) {

                LOG("Scene","setting to main camera");
                Scene::activeScene->mMainCamera = 0;
            }
            Scene::activeScene->mpCameraList.push_back(dynamic_cast<Camera *>(&child));
        }

        mpChildList.push_back(&child);
    }
}