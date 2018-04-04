//
// Created by teeebor on 2018-03-25.
//

#include "../../include/interface/GUI.h"
#include <GLFW/glfw3.h>

void GUI::create(GLFWwindow *display) {
    window = display;
}

void GUI::updateViewPort() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    const float ortho_projection[4][4] =
            {
                    {2.0f / (float) width, 0.0f,                  0.0f,  0.0f},
                    {0.0f,                 2.0f / (float) height, 0.0f,  0.0f},
                    {0.0f,                 0.0f,                  -1.0f, 0.0f},
                    {-1.0f,                1.0f,                  0.0f,  1.0f},
            };
}
