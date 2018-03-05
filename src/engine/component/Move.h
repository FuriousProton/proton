//
// Created by teeebor on 2017-11-27.
//

#pragma once

#include "../../../include/component/Component.h"

namespace proton {
    class Move : public Component {

        void start() override;

        void update() override;

        void end() override;
    };
}