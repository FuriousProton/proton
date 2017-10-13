//
// Created by teeebor on 2017-10-05.
//

#include "Display.h"
#include <glbinding/Binding.h>
#include <GLFW/glfw3.h>
#include "../../utility.h"
#include <math.h>

namespace proton {
    Display::Display(int width, int height, const char *title) : mWidth(width), mHeight(height), mTitle(title),
                                                                 mWindow(nullptr) {

    }

    Display::~Display() {
        glfwTerminate();
    }

    bool Display::prepare() {
        using namespace gl;

        if (!glfwInit()) {
            LOG("ERROR", "Failed to initialize GLFW!");
            return false;
        }

        mMonitors = glfwGetMonitors(&monitorCount);
        activeMonitor = 0;
        //@TODO create manager for the monitor and share parameter
        mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);
        if (!mWindow) {
            LOG("ERROR", "Failed to create the window!");
            return false;
        }
        glfwMakeContextCurrent(mWindow);
        glfwSetWindowUserPointer(mWindow, this);
//region event callbacks
        auto mousecallback = [](GLFWwindow *w, int a, int b, int c) {
            static_cast<Display *>(glfwGetWindowUserPointer(w))->mouse_button_callback(a, b, c);
        };

        auto keycallback = [](GLFWwindow *w, int a, int b, int c, int d) {
            static_cast<Display *>(glfwGetWindowUserPointer(w))->key_callback(a, b, c, d);
        };

        auto winresize = [](GLFWwindow *w, int a, int b) {
            static_cast<Display *>(glfwGetWindowUserPointer(w))->window_resize(a, b);
        };
//
//        auto monitorcallback = [](GLFWmonitor* monitor, int event) {
//            static_cast<Display *>(glfwGetWindowUserPointer(w))->window_resize(a, b);
//        };

        auto cursorcallback = [](GLFWwindow *w, double a, double b) {
            static_cast<Display *>(glfwGetWindowUserPointer(w))->cursor_position_callback(a, b);
        };

//        glfwSetMonitorCallback(monitorcallback);
        glfwSetMouseButtonCallback(mWindow, mousecallback);
        glfwSetWindowSizeCallback(mWindow, winresize);
        glfwSetKeyCallback(mWindow, keycallback);
        glfwSetCursorPosCallback(mWindow, cursorcallback);
//endregion

        glbinding::Binding::initialize();

        return true;
    }


    void Display::update() {
        glFlush();
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }


    bool Display::closed() {
        return glfwWindowShouldClose(mWindow) == 1;
    }

    void Display::cursor_position_callback(double xpos, double ypos) {
        LOG("MOUSE", "MOVE X: " << xpos << "; Y: " << ypos);
    }

    void Display::key_callback(int key, int scancode, int action, int mods) {
        LOG("KEYBOARD", "KEY: " << key << " SCAN: " << scancode << " ACTION: " << action);
    }

    void Display::mouse_button_callback(int button, int action, int mods) {
        LOG("MOUSE", "CLICK");
    }

    void Display::window_resize(int width, int height) {
        resize(width, height);
        LOG("WINDOW", "RESIZE WIDTH: " << width << "; HEIGHT: " << height);
    }

    void Display::setCursor(bool enabled) {
        glfwSetInputMode(mWindow, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }

    void Display::resize(int width, int height) {
        mWidth = width;
        mHeight = height;
        glViewport(0, 0, width, height);
    }

    void Display::setFullscreenType(char fullscreenType) {
        const GLFWvidmode *mode = glfwGetVideoMode(mMonitors[activeMonitor]);

        switch (fullscreenType) {
            case FULLSCREEN:
                LOG("ERROR","Fullscreen mode not implemented...yet...");
                break;
            case WINDOWED:
                glfwSetWindowSize(mWindow, mWidth, mHeight);
                glfwSetWindowPos(mWindow, (int)floor((mode->width-mWidth)/2.0), (int)floor((mode->height-mHeight)/2.0));
                break;
            case FULLSCREEN_WINDOWED:
                glfwSetWindowSize(mWindow, mode->width, mode->height);
                resize(mode->width,mode->height);
                glfwSetWindowPos(mWindow, 0, 0);
                break;
        }
    }

    void Display::setDisplay(int index) {
        if (monitorCount < index || index < 0) {
            LOG("ERROR", "Cannot set monitor to " << index);
        } else {
            const GLFWvidmode *mode = glfwGetVideoMode(mMonitors[index]);
            glfwSetWindowMonitor(mWindow, mMonitors[index], 0, 0, mode->width, mode->height, mode->refreshRate);
        }
    }

}