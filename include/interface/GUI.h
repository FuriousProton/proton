//
// Created by teeebor on 2018-03-25.
//

#pragma once

class GLFWwindow;

class GUI{
private:
    GLFWwindow *window;

public:
    void create(GLFWwindow *window);

    void setClearColor(float r, float g, float b, float a);
    void update();
    void updateViewPort();
};