//
// Created by teeebor on 2017-10-24.
//

#pragma once
#include "../utility.h"


struct DisplaySettings{
/***
 * @TODO: Event for changing values
 */
    int width;
    int height;
    char fullScreenType;
    const char* title;
    DisplaySettings():fullScreenType(),width(800),height(600),title("Game"){
        fullScreenType=WINDOWED;
    };
};