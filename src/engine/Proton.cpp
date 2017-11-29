//
// Created by teeebor on 2017-10-24.
//

#include <GL/gl.h>
#include "Proton.h"

#include "DisplaySettings.h"

#include "../interface/display/Display.h"
#include "Scene.h"
#include "entity/Entity.h"
#include "component/Renderer.h"
#include "component/Transform.h"

std::map<int, int>Proton::keyStates;

bool Proton::createDisplay(DisplaySettings &displaySettings) {
    mDisplay=new proton::Display(displaySettings.width,displaySettings.height,displaySettings.title);
    if(mDisplay->prepare()){
        mDisplay->setFullscreenType(displaySettings.fullScreenType);
        return true;
    }
    return false;
}

void Proton::loopChilds(proton::Entity *e) {
    e->transform().update();
    for(proton::Component *c : e->mpComponentList){
        c->update();
    }
    if(e->mpRenderer) {
        e->mpRenderer->render();
    }
    if(e->mpChildList.size()>0){
        for(auto ce : e->mpChildList){
            loopChilds(ce);
        }
    }
}

void Proton::startLoop() {
    using namespace proton;
    while (!mDisplay->closed()){
        mDisplay->clear();
        Scene *scene = Scene::activeScene;
        for(Entity *e : scene->mpEntityList){
            loopChilds(e);
        }
        errorCheck("main loop");
        mDisplay->update();
    }
}

void Proton::cleanUp() {
    using namespace proton;
    //@TODO delete child objects too
    Scene *scene = Scene::activeScene;
    for(Entity *e : scene->mpEntityList){
        delete e;
    }
}
