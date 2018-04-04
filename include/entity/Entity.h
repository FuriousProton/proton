//
// Created by teeebor on 2017-10-05.
//

#pragma once
#include "../utility.h"

#include <vector>

class Input;
namespace proton{
    class Transform;
    class Component;
    class Renderer;
    class PROTON_API Entity {
    protected:
        Entity *mpParent;
        Transform *mpTransform;
        Input *mpInput;
        virtual void setup();

    public:
        std::vector<Entity*> mpChildList;
        std::vector<Component*> mpComponentList;
        Renderer *mpRenderer;
        Entity();
        virtual ~Entity();
        Entity * parent();
        Transform &transform();
        void addComponent(Component *comp);
        void addChild(Entity *child);
        Input *getInput();
    };

}
