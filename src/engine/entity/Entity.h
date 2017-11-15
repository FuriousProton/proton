//
// Created by teeebor on 2017-10-05.
//

#pragma once

#include <vector>

namespace proton{
    class Transform;
    class Component;
    class Renderer;
    class Entity {
    protected:
        Entity *mpParent;
        Transform *mpTransform;

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
        void addChild(Entity &child);

    };

}
