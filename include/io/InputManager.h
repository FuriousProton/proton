#pragma once

#include "../utility.h"
#include <vector>

struct PROTON_API Point {
    double x = 0;
    double y = 0;
};

struct PROTON_API Key {
    int key=0;
    bool press = false;
    bool release = false;
    bool down = false;
    ~Key(){
        LOG("DESTRUCTED",key);
    }
};

struct PROTON_API Pointer {
    int index=0;
    Point pos = {0, 0};
    Point distance = {0, 0};
};

class PROTON_API InputManager {
    std::vector<Key*> keys;
    std::vector<Pointer*> pointers;
    static InputManager *instance;
    InputManager(){}
public:
    static InputManager *getInstance() {
        if (!instance)
            instance = new InputManager;
        return instance;
    }
    bool isPointerMoved(int pointer);

    Point getPointerMove(int pointer);

    Point getPointerPosition(int pointer);

    void setPointer(int pointer, double x, double y);


    bool isButtonPressed(int key);

    bool isButtonReleased(int key);

    bool isButtonDown(int key);

    void setKeyPressed(int key, bool pressed);

    void setKeyReleased(int key, bool released);

    void setKeyDown(int key, bool down);

    void update();

private:
    Key *getOrCreateButton(int k);
    Pointer *getOrCreatePointer(int k);
};
