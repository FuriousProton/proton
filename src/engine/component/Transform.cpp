//
// Created by teeebor on 2017-10-24.
//

#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace proton{
    void Transform::move(double x, double y, double z) {
        mDirty = true;
        mTransform.x+=x;
        mTransform.y+=y;
        mTransform.z+=z;
    }


    void Transform::move(double x, double y) {
        move(x, y, 0);
    }

    void Transform::move(glm::vec3 pos) {
        move(pos.x, pos.y, pos.z);
    }



    void Transform::scale(double x, double y, double z) {
        mDirty = true;
        mScale.x+=x;
        mScale.y+=y;
        mScale.z+=z;
    }

    void Transform::scale(double factor) {
        scale(factor, factor, factor);
    }

    void Transform::scale(double x, double y) {
        scale(x, y, 1);
    }

    void Transform::scale(glm::vec3 factor) {
        mDirty = true;
        scale(factor.x, factor.y, factor.z);
    }

    void Transform::rotate(glm::quat quaternion) {
        mDirty = true;
        mRotation+=quaternion;
    }

    void Transform::rotate(glm::vec3 rotation) {
        mDirty = true;
        glm::quat quat = glm::quat(rotation);
        mRotation+=quat;
    }

    glm::vec3 Transform::eulerRotation() {
        return glm::eulerAngles(mRotation);
    }

    glm::mat4 Transform::getTransformationMatrix() {
        if(mDirty){
            mDirty = false;
            glm::mat4 model = glm::toMat4(mRotation);
            model*=glm::translate(glm::mat4(1.0f),mTransform);
            model*=glm::scale(glm::mat4(1.0f),mScale);
            mModel=model;
        }
        return mModel;
    }

    void Transform::update() {
        Component::update();
    }

    void Transform::end() {
        Component::end();
    }

    void Transform::start() {
        Component::start();
    }

}
