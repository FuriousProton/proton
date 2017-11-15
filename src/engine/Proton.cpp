//
// Created by teeebor on 2017-10-24.
//

#include "Proton.h"

#include "DisplaySettings.h"

#include "../interface/display/Display.h"
#include "Scene.h"
#include "entity/Entity.h"
#include "component/Renderer.h"

void Proton::createDisplay(DisplaySettings &displaySettings) {
    mDisplay=new proton::Display(displaySettings.width,displaySettings.height,displaySettings.title);
    mDisplay->prepare();
    mDisplay->setFullscreenType(displaySettings.fullScreenType);
}

void Proton::startLoop() {
    using namespace proton;
    while (!mDisplay->closed()){
        Scene *scene = Scene::activeScene;
        mDisplay->clear();
        for(Entity *e : scene->mpEntityList){
            LOG("LOOP",&e);
            e->mpRenderer->render();
        }
        mDisplay->update();
    }
}
