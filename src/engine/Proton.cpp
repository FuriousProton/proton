//
// Created by teeebor on 2017-10-24.
//

#include "../../include/Proton.h"

#include <glbinding/gl/gl.h>
#include <GL/gl.h>

#include "../../include/interface/Display.h"
#include "../../include/Scene.h"
#include "../../include/entity/Entity.h"
#include "../../include/component/Transform.h"
#include "../../include/DisplaySettings.h"
#include "../../include/component/Renderer.h"
#include "../../include/EventManager.h"


std::map<int, int>Proton::keyStates;
Proton *Proton::activeInstance = nullptr;

bool Proton::createDisplay(DisplaySettings &displaySettings) {
    using namespace gl;

    mDisplay = new proton::Display(displaySettings.width, displaySettings.height, displaySettings.title);
    if (mDisplay->prepare()) {
        mDisplay->setFullscreenType(displaySettings.fullScreenType);
        return true;
    }
    Proton::errorcheck("Before GL_TEXTURE_2D");

    glEnable(GL_TEXTURE_2D);

    Proton::errorcheck("AFTER GL_TEXTURE_2D");
    return false;
}

void Proton::loopChilds(proton::Entity *e) {
    e->transform().update();
    for (proton::Component *c : e->mpComponentList) {
        c->update();
    }
    Proton::errorcheck("Before render");
    if (e->mpRenderer) {
        e->mpRenderer->render();
    }
    Proton::errorcheck("After render");
    if (e->mpChildList.size() > 0) {
        for (auto ce : e->mpChildList) {
            loopChilds(ce);
        }
    }
}

void Proton::startLoop() {
    using namespace proton;
    using namespace gl;
    activeInstance = this;
    while (!mDisplay->closed()) {
        mDisplay->clear();
        Scene *scene = Scene::activeScene;
        for (Entity *e : scene->mpEntityList) {
            loopChilds(e);
        }
        Proton::errorcheck("main loop");
        mDisplay->update();
    }
}

void Proton::cleanUp() {
    using namespace proton;
    //@TODO delete child objects too
    Scene *scene = Scene::activeScene;
    for (Entity *e : scene->mpEntityList) {
        delete e;
    }
}


void Proton::errorcheck(const char* label) {
    gl::GLenum err;
    err = gl::glGetError();
    if(err!=GL_NO_ERROR)
        std::cout<<"_______________________________________________________________"<<std::endl
                 <<"["<<label<<"] THERE WAS AN ERROR: "<<err<<std::endl
                 <<"_______________________________________________________________"<<std::endl;
}

