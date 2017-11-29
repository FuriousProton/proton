//
// Created by teeebor on 2017-11-03.
//

#pragma once

#include <vector>

namespace proton{
    class Entity;
    class Camera;
}

class Scene {
public:
    int mMainCamera;
    std::vector<proton::Entity *> mpEntityList;
    std::vector<proton::Camera *> mpCameraList;
    static Scene *activeScene;

public:
    Scene();
    ~Scene();
    void activate();
    proton::Camera *mainCamera();

    void addEntity(proton::Entity *e);
    void removeEntity(proton::Entity *e);
};

