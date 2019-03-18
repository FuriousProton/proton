//
// Created by teeebor on 2017-10-05.
//
#include <glbinding/Binding.h>
#include "../../../include/utility.h"
#include "../../../include/interface/Display.h"
#include <GLFW/glfw3.h>
#include "../../../include/Proton.h"
#include "../../../include/EventManager.h"
#include "../../../include/io/InputManager.h"

#include <cmath>

//#ifdef IMGUI
#include "../../../lib/imgui/imgui.h"
#include "../../../lib/imgui/imgui_impl_opengl3.h"
#include "../../../lib/imgui/imgui_impl_glfw.h"
//#endif

namespace proton {
    Display::Display(int width, int height, const char *title) : mWidth(width), mHeight(height), mTitle(title),
                                                                 mpWindow(nullptr) {
        updateTime();
    }

    Display::~Display() {
//#ifdef IMGUI
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
//#endif
        glfwTerminate();
    }

    bool Display::prepare() {
        using namespace gl;
        INFO("before init");

        if (!glfwInit()) {
            LOG("ERROR", "Failed to initialize GLFW!");
            return false;
        }
        INFO("after init");

//        mpMonitors = glfwGetMonitors(&monitorCount);
        INFO("after monitor");


        activeMonitor = 0;
        //@TODO create manager for the monitor and share parameter

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        mpWindow = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);
        INFO("after glfwCreateWindow");


        if (!mpWindow) {
            LOG("ERROR", "Failed to create the window!");
            return false;
        }
        glfwMakeContextCurrent(mpWindow);
        glfwSetWindowUserPointer(mpWindow, this);
//        glfwSwapInterval(60);

#define Events
#ifdef Events
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
//        auto monitorcallback = [](GLFWmonitor* w, int event) {
//            static_cast<Display *>(glfwGetWindowUserPointer(w))->window_resize(a, b);
//        };

        auto cursorcallback = [](GLFWwindow *w, double a, double b) {
            static_cast<Display *>(glfwGetWindowUserPointer(w))->cursor_position_callback(a, b);
        };
#ifdef IMGUI

        auto scrollCallback = [](GLFWwindow *w, double x, double y) {
            ImGui_ImplGlfw_ScrollCallback(w, x, y);
        };
        auto charCallback = [](GLFWwindow *w, unsigned int c) {
            ImGui_ImplGlfw_CharCallback(w, c);
        };
#endif
//        glfwSetMonitorCallback(monitorcallback);
        glfwSetMouseButtonCallback(mpWindow, mousecallback);
        glfwSetWindowSizeCallback(mpWindow, winresize);
        glfwSetKeyCallback(mpWindow, keycallback);
        glfwSetCursorPosCallback(mpWindow, cursorcallback);
#ifdef IMGUI
        glfwSetScrollCallback(mpWindow, scrollCallback);
        glfwSetCharCallback(mpWindow, charCallback);
#endif
//VSYNC OFF
        glfwSwapInterval(0);
//endregion
#endif
        Proton::errorcheck("after glfwMakeContextCurrent");
        glbinding::Binding::initialize(glfwGetProcAddress);
        INFO("after glbinding include");

//#ifdef IMGUI

        LOG("OpenGL version", glGetString(GL_VERSION));
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        mp_IO = io;

        ImGui::StyleColorsDark();
        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        const char* glsl_version = "#version 130";

//        mpImGui = ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(mpWindow, true);
        bool ok = ImGui_ImplOpenGL3_Init(glsl_version);
        std::string r = ok ? "Yes" : "No";
        LOG("IMGUI created", r);
//#endif
        INFO("after version");
        return true;
    }


    void Display::clear() {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

    }

    void Display::update() {
        is_first = false;
//#ifdef IMGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (mp_IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
//#endif
        for (std::pair<const int, int> &state : Proton::keyStates) {
            if (state.second == 0) {
                Proton::keyStates.erase(state.first);
            }
        }
        glFlush();
        glfwSwapBuffers(mpWindow);
        updateTime();
    }


    bool Display::closed() {
        return glfwWindowShouldClose(mpWindow) == 1;
    }

    void Display::cursor_position_callback(double xpos, double ypos) {
//        MoveEvent *e = new MoveEvent(xpos, ypos);
//        LOG("Cursor", xpos<<" "<<ypos);
//        EventManager::getInstance().fire("CURSOR", e);
    }

    void Display::key_callback(int key, int scancode, int action, int mods) {
        auto Input = InputManager::getInstance();
        switch (action){
            case GLFW_RELEASE:
                Input->setKeyReleased(key, true);
                Input->setKeyDown(key, false);
                Input->setKeyPressed(key, false);
//                LOG("KEYBOARD", "KEY: " << key << " SCAN: " << scancode << " ACTION: RELEASE");
                break;
            case GLFW_PRESS:
                Input->setKeyReleased(key, false);
                Input->setKeyDown(key, false);
                Input->setKeyPressed(key, true);
//                LOG("KEYBOARD", "KEY: " << key << " SCAN: " << scancode << " ACTION: PRESS");
                break;
            case GLFW_REPEAT:
                Input->setKeyReleased(key, false);
                Input->setKeyDown(key, true);
                Input->setKeyPressed(key, false);
//                LOG("KEYBOARD", "KEY: " << key << " SCAN: " << scancode << " ACTION: DOWN");
                break;
        }

    }

    void Display::mouse_button_callback(int button, int action, int mods) {
#ifdef IMGUI
        auto io = ImGui::GetIO();
        if (io.WantCaptureMouse == 1) {
            ImGui_ImplGlfw_MouseButtonCallback(mpWindow, button, action, mods);
        } else {
            Input::getInstance()->setMouseInput(button, GLFW_INPUT_TO_PROTON(action));
        }
#endif
        //       LOG("MOUSE", "CLICK");
    }

    void Display::window_resize(int width, int height) {
        resize(width, height);
//        auto *e = new DisplayEvent(width, height);
//
//        EventManager::getInstance().fire("RESIZE", e);

        //     LOG("WINDOW", "RESIZE WIDTH: " << width << "; HEIGHT: " << height);
    }

    void Display::setCursor(bool enabled) {
        glfwSetInputMode(mpWindow, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }

    void Display::resize(int width, int height) {
        EventBus::getInstance().fire(new DisplayEvent(width,height));
        glViewport(0, 0, width, height);
    }

    void Display::setFullscreenType(char fullscreenType) {
/*
        const GLFWvidmode *mode = glfwGetVideoMode(mpMonitors[activeMonitor]);

        switch (fullscreenType) {
            case FULLSCREEN:
                LOG("ERROR", "Fullscreen mode not implemented...yet...");
                break;
            default:
            case WINDOWED:
                glfwSetWindowSize(mpWindow, mWidth, mHeight);
                glfwSetWindowPos(mpWindow, (int) floor((mode->width - mWidth) / 2.0),
                                 (int) floor((mode->height - mHeight) / 2.0));
                break;
            case FULLSCREEN_WINDOWED:
                glfwSetWindowSize(mpWindow, mode->width, mode->height);
                resize(mode->width, mode->height);
                glfwSetWindowPos(mpWindow, 0, 0);
                break;
        }*/
    }

    void Display::setDisplay(int index) {
        if (monitorCount < index || index < 0) {
            LOG("ERROR", "Cannot set monitor to " << index);
        } else {
            const GLFWvidmode *mode = glfwGetVideoMode(mpMonitors[index]);
            glfwSetWindowMonitor(mpWindow, mpMonitors[index], 0, 0, mode->width, mode->height, mode->refreshRate);
        }
    }


    double Display::FrameTime() {
        return frameTime;
    }

    void Display::updateTime() {
        clock_t now = clock();
        frameTime = (double) (now - time) / CLOCKS_PER_SEC;
        time = now;
    }


}