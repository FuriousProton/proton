#include "../../../include/io/InputManager.h"

InputManager *InputManager::instance = nullptr;

bool InputManager::isButtonPressed(int index) {
    auto k = getOrCreateButton(index);
    return k->press;
}

bool InputManager::isButtonReleased(int index) {
    auto k = getOrCreateButton(index);
    return k->release;
}

bool InputManager::isButtonDown(int index) {
    auto k = getOrCreateButton(index);
    return k->down;
}

bool InputManager::isPointerMoved(int index) {
    auto p = getOrCreatePointer(index);
    return p->distance.x != 0 && p->distance.y != 0;
}

Point InputManager::getPointerMove(int index) {
    auto p = getOrCreatePointer(index);
    return p->distance;
}

Point InputManager::getPointerPosition(int index) {
    auto p = getOrCreatePointer(index);
    return p->pos;
}

void InputManager::update() {
    for (auto x : pointers) {
        x->distance = {0, 0};
    }

    //TODO: add key state reset
}

void InputManager::setPointer(int index, double x, double y) {
    auto p = getOrCreatePointer(index);
    p->distance.x = x - p->pos.x;
    p->distance.y = y - p->pos.y;
    p->pos.x = x;
    p->pos.y = y;
}

void InputManager::setKeyPressed(int key, bool pressed) {
    auto k = getOrCreateButton(key);
    k->press = pressed;
}

void InputManager::setKeyReleased(int key, bool released) {
    auto k = getOrCreateButton(key);
    k->release = released;
}

void InputManager::setKeyDown(int key, bool down) {
    auto k = getOrCreateButton(key);
    k->down = down;
}

Key *InputManager::getOrCreateButton(int k) {
    for (auto i :keys) {
        if (i->key == k) {
            return i;
        }
    }
    auto *p = new Key;
    p->key = k;
    keys.push_back(p);
    return keys[keys.size() - 1];
}

Pointer *InputManager::getOrCreatePointer(int k) {
    for (auto i :pointers) {
        if (i->index == k)
            return i;
    }
    auto *p = new Pointer;
    p->index = k;
    pointers.push_back(p);
    return pointers[pointers.size() - 1];
}



