//
// Created by teeebor on 2017-10-24.
//

#include "Proton.h"

#include "DisplaySettings.h"

#include "../interface/display/Display.h"



void Proton::createDisplay(DisplaySettings &displaySettings) {
    mDisplay=new proton::Display(displaySettings.width,displaySettings.height,displaySettings.title);
    mDisplay->prepare();
    mDisplay->setFullscreenType(displaySettings.fullScreenType);
}

void Proton::startLoop() {
    while (!mDisplay->closed()){
        mDisplay->clear();

        mDisplay->update();
    }
}
