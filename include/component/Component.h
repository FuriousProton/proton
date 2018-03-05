//
// Created by teeebor on 2017-10-05.
//

#pragma once

#include "../utility.h"
#include "../entity/Entity.h"

namespace proton {
    class PROTON_API Component {
    protected:
        Entity *mpEntity{};
    public:

        virtual void start();

        virtual void update();

        virtual void end();

        Entity &getEntity();

        void setEntity(Entity *e);

        bool getKeyDown(int key);
        bool getKeyUp(int key);
        bool getKeyPress(int key);
    };

}

