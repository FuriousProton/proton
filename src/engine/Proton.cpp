//
// Created by teeebor on 2017-10-24.
//

#include "../../include/Proton.h"

#include <glbinding/gl/gl.h>

#include "../../include/interface/Display.h"
#include "../../include/Scene.h"
#include "../../include/entity/Entity.h"
#include "../../include/component/Transform.h"
#include "../../include/DisplaySettings.h"
#include "../../include/component/Renderer.h"
#include "../../include/EventManager.h"


std::map<int, int>Proton::keyStates;

bool Proton::createDisplay(DisplaySettings &displaySettings) {
    using namespace gl;

    mDisplay=new proton::Display(displaySettings.width,displaySettings.height,displaySettings.title);
    if(mDisplay->prepare()){
        mDisplay->setFullscreenType(displaySettings.fullScreenType);
        return true;
    }
    errorCheck("Before GL_TEXTURE_2D");

    glEnable(GL_TEXTURE_2D);

    errorCheck("AFTER GL_TEXTURE_2D");
    return false;
}

void Proton::loopChilds(proton::Entity *e) {
    e->transform().update();
    for(proton::Component *c : e->mpComponentList){
        c->update();
    }
    errorCheck("Before render");
    if(e->mpRenderer) {
        e->mpRenderer->render();
    }
    errorCheck("After render");
    if(e->mpChildList.size()>0){
        for(auto ce : e->mpChildList){
            loopChilds(ce);
        }
    }
}

void Proton::startLoop() {
    using namespace proton;
    using namespace gl;
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
