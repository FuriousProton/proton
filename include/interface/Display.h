//
// Created by teeebor on 2017-10-05.
//

#pragma once
#include "../utility.h"

class GLFWwindow;
class GLFWmonitor;
namespace proton {
    class PROTON_API Display {
    private:
        GLFWwindow *mpWindow;
        GLFWmonitor **mpMonitors;
        int monitorCount;
        int activeMonitor;

        int mWidth;
        int mHeight;
        const char *mTitle;

    public:
        Display(int width, int height) : Display(width, height, "Window") {};

        Display(int width, int height, const char *title);
        ~Display();

        void update();

        bool closed();
        void clear();

        /**
         * Switching from fullscreen to windowed, or from windowed to fullscreen
         * @param fullscreen
         */
        void setFullscreenType(char fullscreenType);

        /**
         * Setting the cursor's visibility
         * @param enabled Mouse visibility (true=visible)
         */
        void setCursor(bool enabled);

        void setDisplay(int index);
        /**
         * Resizing the window (not the frame)
         * @param width Desired window width
         * @param height Desired window heignt
         */
        void resize(int width, int height);
        bool prepare();



    private:

        void window_resize(int width, int height);

        void key_callback(int key, int scancode, int action, int mods);

        void mouse_button_callback(int button, int action, int mods);

        void cursor_position_callback(double xpos, double ypos);
    };
}
