//
// Created by teeebor on 2017-11-18.
//

#pragma once


#include "Component.h"

namespace proton {
    class DemoComponent : public Component {

        void start() override;

        void update() override;

        void end() override;
    };
}