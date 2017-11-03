//
// Created by teeebor on 2017-10-24.
//

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../entity/Entity.h"

namespace proton {

    Transform::Transform() {
        mDirty=true;
    }

    void Transform::move(double x, double y, double z) {
        setDirty();
        mTransform.x += x;
        mTransform.y += y;
        mTransform.z += z;
    }


    void Transform::move(double x, double y) {
        move(x, y, 0);
    }

    void Transform::move(glm::vec3 pos) {
        move(pos.x, pos.y, pos.z);
    }


    void Transform::scale(double x, double y, double z) {
        setDirty();
        mScale.x += x;
        mScale.y += y;
        mScale.z += z;
    }

    void Transform::scale(double factor) {
        scale(factor, factor, factor);
    }

    void Transform::scale(double x, double y) {
        scale(x, y, 1);
    }

    void Transform::scale(glm::vec3 factor) {
        setDirty();
        scale(factor.x, factor.y, factor.z);
    }

    void Transform::rotate(glm::quat quaternion) {
        setDirty();
        mRotation += quaternion;
    }

    void Transform::rotate(glm::vec3 rotation) {
        setDirty();
        glm::quat quat = glm::quat(rotation);
        mRotation += quat;
    }

    glm::vec3 Transform::eulerRotation() {
        return glm::eulerAngles(mRotation);
    }

    void Transform::setDirty() {
        mDirty = true;
        for (auto &child : mpEntity->mpChildList) {
            child->transform().setDirty();
        }
    }

    glm::mat4 Transform::getTransformationMatrix() {
        if (mDirty) {
            mDirty = false;
            glm::mat4 model = glm::mat4_cast(mRotation);
            model *= glm::translate(glm::mat4(1.0f), mTransform);
            model *= glm::scale(glm::mat4(1.0f), mScale);
            if(mpEntity->parent()!= nullptr){
                mModel = mpEntity->parent()->transform().mModel;
                mModel *= model;
            }else{
                mModel=model;
            }
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
