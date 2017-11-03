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
    using namespace proton;
private:
    std::vector<Entity *> mpEntityList;
    std::vector<Camera *> mpCameraList;
    int mMainCamera;
public:
    static Scene *activeScene;

public:
    Scene();
    ~Scene();
    void activate();

    void addEntity(Entity *e);
    void removeEntity(Entity *e);
};

