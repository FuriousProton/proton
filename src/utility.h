//
// Created by teeebor on 2017-10-13.
//

#pragma once

#include <iostream>
#define LOG(type, message) std::cout<<"["<<type<<"]\t"<<message<<std::endl
#define errorCheck(c)({GLenum err; err = glGetError();if(err!=GL_NO_ERROR)std::cout<<"_______________________________________________________________"<<std::endl<<"["<<c<<"] THERE WAS AN ERROR: "<<err<<std::endl<<"_______________________________________________________________"<<std::endl;})

#define FULLSCREEN 0x00
#define FULLSCREEN_WINDOWED 0x01
#define WINDOWED 0x02

#define aiVectorToArray(vector,array){\
array[0]=vector.x;\
array[1]=vector.y;\
array[2]=vector.z;\
}
#define copyArray3(a,b){\
b[0]=a[0];\
b[1]=a[1];\
b[2]=a[2];\
}
enum EVENT {
    UPDATE,
    RENDER,

    KEYUP,
    KEYDOWN,
    KEYPRESS,
    MOUSEUP,
    MOUSEDOWN,
    MOUSEPRESS,
    MOUSEMOVE
};