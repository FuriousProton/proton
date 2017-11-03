//
// Created by teeebor on 2017-11-03.
//

#include "Scene.h"

#include "entity/Entity.h"
#include "entity/Camera.h"
#include "../utility.h"

Scene::Scene() {
    mMainCamera = -1;
}

Scene::~Scene() {
    for (Camera *c:mpCameraList) {
        delete (c);
    }
    for (Entity *e:mpEntityList) {
        delete (e);
    }
}

void Scene::activate() {
    LOG("Scene", "Scene activated");
    activeScene = this;
}

void Scene::addEntity(proton::Entity *e) {
    if (nullptr != dynamic_cast<Camera *>(e)) {
        if (mMainCamera < 0) {
            mMainCamera = 0;
        }
        mpCameraList.push_back(dynamic_cast<Camera *>(e));
    } else {
        mpEntityList.push_back(e);
    }
}

void Scene::removeEntity(proton::Entity *e) {
    if (nullptr != dynamic_cast<Camera *>(e)) {
        if (mpCameraList.size() == 1) {
            mMainCamera = -1;
            LOG("Warning", "The main camera has been removed");
            mpCameraList.pop_back();
        } else {
            for (int i = 0; i < mpCameraList.size(); i++) {
                if (&(mpCameraList[i]) == &e) {
                    LOG("Info", "Camera removed");
                    mpCameraList.erase(mpCameraList.begin() + i);
                    break;
                }
            }
        }
    } else {
        for (int i = 0; i < mpEntityList.size(); i++) {
            if (&(mpEntityList[i]) == &e) {
                LOG("Info", "Entity removed");
                mpEntityList.erase(mpEntityList.begin() + i);
                break;
            }
        }
    }
}
