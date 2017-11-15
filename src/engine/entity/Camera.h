//
// Created by teeebor on 2017-11-03.
//

#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "Entity.h"

namespace proton {
    class Camera : public Entity {
    private:
        float mFrameWidth, mFrameHeight, mFov, mNear, mFar;
        glm::mat4 mProjectionMatrix;
    public:
        Camera(float frameWidth, float frameHeight, float fov, float near, float far);
        ~Camera() override;
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        void setCulling(bool enabled);
        void setBlend(bool enabled);


    private:
        void createProjectionMatrix();
        void setup() override;
    };

}

