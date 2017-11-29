//
// Created by teeebor on 2017-11-03.
//

#include "Scene.h"

#include "entity/Entity.h"
#include "entity/Camera.h"
#include "../utility.h"
Scene *Scene::activeScene= nullptr;
Scene::Scene() {
    mMainCamera = -1;
}

Scene::~Scene() {
    using namespace proton;
    for (Camera *c:mpCameraList) {
        delete (c);
    }
    for (Entity *e:mpEntityList) {
        delete (e);
    }
}

void Scene::activate() {
    LOG("Scene", "Scene activated");
    Scene::activeScene = this;
}

void Scene::addEntity(proton::Entity *e) {
    using namespace proton;
    LOG("Scene","Adding entity");
    if (nullptr != dynamic_cast<Camera *>(e)) {
        LOG("Scene","Adding camera");
        if (mMainCamera < 0) {

            LOG("Scene","setting to main camera");
            mMainCamera = 0;
        }
        mpCameraList.push_back(dynamic_cast<Camera *>(e));
    }
    mpEntityList.push_back(e);
}

void Scene::removeEntity(proton::Entity *e) {
    using namespace proton;

    if (nullptr != dynamic_cast<Camera *>(e)) {
        if (mpCameraList.size() == 1) {
            mMainCamera = -1;
            LOG("Warning", "The main camera has been removed");
            mpCameraList.pop_back();
        } else {
            for (int i = 0; i < mpCameraList.size(); i++) {
                if ((mpCameraList[i]) == e) {
                    LOG("Info", "Camera removed");
                    mpCameraList.erase(mpCameraList.begin() + i);
                    break;
                }
            }
        }
    } else {
        for (int i = 0; i < mpEntityList.size(); i++) {
            if ((mpEntityList[i]) == e) {
                LOG("Info", "Entity removed");
                mpEntityList.erase(mpEntityList.begin() + i);
                break;
            }
        }
    }
}

proton::Camera *Scene::mainCamera() {
    if(mMainCamera>=0 && mpCameraList.size()>=mMainCamera){
        return mpCameraList[mMainCamera];
    }
    return nullptr;
}
