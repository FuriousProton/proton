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
    public:
        std::vector<Entity*> mpChildList;
        std::vector<Component*> mpComponentList;
        Renderer *mpRenderer;
        Entity();
        ~Entity();
        Entity * parent();
        Transform &transform();
        void addComponent(Component *comp);
        void addChild(Entity &child);

    };

}
