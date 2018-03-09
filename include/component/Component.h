//
// Created by teeebor on 2017-10-05.
//

#pragma once

#include "../utility.h"
#include "../entity/Entity.h"
#include "../io/Input.h"

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
        BaseInput *Input(int key);
        bool getKeyDown(int key);
        bool getKeyUp(int key);
        bool getKeyPress(int key);
    };

}

