//
// Created by teeebor on 2017-10-24.
//

#pragma once

#include "../utility.h"
#include <glm/gtc/type_ptr.hpp>
#include "Component.h"

namespace proton {
    class PROTON_API Transform : public Component {
        glm::quat mRotation;
        glm::vec3 mTransform;
        glm::vec3 mScale;
        glm::mat4 mModel;
        float pitch = 0;
        float yaw = 0;
        float roll = 0;
        bool mDirty;
    public:
        Transform();

        void update() override;

        void end() override;

        void start() override;

        void move(double x, double y, double z);

        void move(double x, double y);

        void move(glm::vec3 pos);


        void scale(double x, double y, double z);

        void scale(double factor);

        void scale(double x, double y);

        void scale(glm::vec3 factor);

//        void rotate(glm::quat quaternion);
        void rotate(glm::vec3 rotation);

        glm::vec3 eulerRotation();

        glm::quat rotation();

        glm::mat4 rotationMat();

        glm::vec3 position();

        glm::mat4 getTransformationMatrix(bool reversed);

        glm::mat4 getTransformationMatrix();

    private:
        void setDirty();
    };
};

