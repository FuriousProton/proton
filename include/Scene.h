//
// Created by teeebor on 2017-11-03.
//

#pragma once

#include "utility.h"
#include "Proton.h"

#include <vector>

namespace proton{
    class Entity;
    class Camera;
    class Display;
}

class PROTON_API Scene {
private:
    Proton *proton;
    proton::Display *mpDisplay;
public:
    int mMainCamera;
    std::vector<proton::Entity *> mpEntityList;
    std::vector<proton::Camera *> mpCameraList;
    static Scene *activeScene;

public:
    void start(proton::Display *display);
    Scene();
    ~Scene();
    void activate();
    proton::Camera *mainCamera();
    void setMainCamera(proton::Camera *camera);
    void addCamera(proton::Camera *camera);
    double frameTime();
    void addEntity(proton::Entity *e);
    void removeEntity(proton::Entity *e);
};

