//
// Created by teeebor on 2017-10-05.
//
#include <glbinding/Binding.h>
#include "../../../include/utility.h"
#include "../../../include/interface/Display.h"
#include <GLFW/glfw3.h>
#include "../../../include/Proton.h"
#include "../../../include/CustomEvent.h"
#include "../../../include/EventManager.h"
#include <cmath>

namespace proton {
    Display::Display(int width, int height, const char *title) : mWidth(width), mHeight(height), mTitle(title),
                                                                 mpWindow(nullptr) {
        mpInput=Input::getInstance();
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

        mpMonitors = glfwGetMonitors(&monitorCount);
        activeMonitor = 0;
        //@TODO create manager for the monitor and share parameter

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
        mpWindow = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);
        if (!mpWindow) {
            LOG("ERROR", "Failed to create the window!");
            return false;
        }
        glfwMakeContextCurrent(mpWindow);
        glfwSetWindowUserPointer(mpWindow, this);
//        glfwSwapInterval(60);
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
        glfwSetMouseButtonCallback(mpWindow, mousecallback);
        glfwSetWindowSizeCallback(mpWindow, winresize);
        glfwSetKeyCallback(mpWindow, keycallback);
        glfwSetCursorPosCallback(mpWindow, cursorcallback);
//endregion
        EventManager::getInstance().createEvent("CURSOR");
        EventManager::getInstance().createEvent("INPUT");
        glbinding::Binding::initialize();
        LOG("OpenGL version",glGetString(GL_VERSION));
        return true;
    }


    void Display::update() {
        for(std::pair<const int, int> & state : Proton::keyStates){
            if(state.second==0){
                Proton::keyStates.erase(state.first);
            }
        }
        glFlush();
        glfwSwapBuffers(mpWindow);
        glfwPollEvents();
    }


    bool Display::closed() {
        return glfwWindowShouldClose(mpWindow) == 1;
    }

    void Display::cursor_position_callback(double xpos, double ypos) {
        MoveEvent *e = new MoveEvent(xpos,ypos);
        EventManager::getInstance().fire("CURSOR", e );
 //       LOG("MOUSE", "MOVE X: " << xpos << "; Y: " << ypos);
    }

    void Display::key_callback(int key, int scancode, int action, int mods) {
        Proton::keyStates[key]=action;
        KeyEvent *e = new KeyEvent(key, scancode, action, mods);

        Input::getInstance()->setInput(key,GLFW_INPUT_TO_PROTON(action));

        EventManager::getInstance().fire("INPUT", e );
//        LOG("KEYBOARD", "KEY: " << key << " SCAN: " << scancode << " ACTION: " << action);
    }

    void Display::mouse_button_callback(int button, int action, int mods) {
 //       LOG("MOUSE", "CLICK");
    }

    void Display::window_resize(int width, int height) {
        resize(width, height);
   //     LOG("WINDOW", "RESIZE WIDTH: " << width << "; HEIGHT: " << height);
    }

    void Display::setCursor(bool enabled) {
        glfwSetInputMode(mpWindow, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }

    void Display::resize(int width, int height) {
        mWidth = width;
        mHeight = height;
        glViewport(0, 0, width, height);
    }

    void Display::setFullscreenType(char fullscreenType) {
        const GLFWvidmode *mode = glfwGetVideoMode(mpMonitors[activeMonitor]);

        switch (fullscreenType) {
            case FULLSCREEN:
                LOG("ERROR","Fullscreen mode not implemented...yet...");
                break;
            default:
            case WINDOWED:
                glfwSetWindowSize(mpWindow, mWidth, mHeight);
                glfwSetWindowPos(mpWindow, (int)floor((mode->width-mWidth)/2.0), (int)floor((mode->height-mHeight)/2.0));
                break;
            case FULLSCREEN_WINDOWED:
                glfwSetWindowSize(mpWindow, mode->width, mode->height);
                resize(mode->width,mode->height);
                glfwSetWindowPos(mpWindow, 0, 0);
                break;
        }
    }

    void Display::setDisplay(int index) {
        if (monitorCount < index || index < 0) {
            LOG("ERROR", "Cannot set monitor to " << index);
        } else {
            const GLFWvidmode *mode = glfwGetVideoMode(mpMonitors[index]);
            glfwSetWindowMonitor(mpWindow, mpMonitors[index], 0, 0, mode->width, mode->height, mode->refreshRate);
        }
    }

    void Display::clear() {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }

    Input *Display::input() {
        return mpInput;
    }

}