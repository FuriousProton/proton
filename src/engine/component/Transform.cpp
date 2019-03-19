//
// Created by teeebor on 2017-10-24.
//
#define GLM_ENABLE_EXPERIMENTAL

#include "../../../include/entity/Entity.h"

#include "../../../include/component/Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>

namespace proton {

    Transform::Transform() : mTransform(glm::vec3(0, 0, 0)), mScale(glm::vec3(1, 1, 1)), mRotation(glm::vec3(0, 0, 0)) {
        mDirty = true;
    }

    void Transform::move(double x, double y, double z) {
        setDirty();
        mTransform.x += x;
        mTransform.y += y;
        mTransform.z += z;
    }


    void Transform::move(double x, double y) {
        setDirty();
        move(x, y, 0);
    }

    void Transform::move(glm::vec3 pos) {
        setDirty();
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
//
//    void Transform::rotate(glm::quat quaternion) {
//        setDirty();
//        mRotation = mRotation*quaternion;
//    }


    void Transform::rotate(glm::vec3 rotation) {
        setDirty();
        pitch += rotation.x;
        yaw += rotation.y;
        roll += rotation.z;
        glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1, 0, 0));
        glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
        glm::quat qRoll = glm::angleAxis(roll,glm::vec3(0,0,1));
        mRotation = (qPitch * qYaw * qRoll);
    }

    glm::quat Transform::rotation() {
        return mRotation;
    }

    glm::vec3 Transform::eulerRotation() {
        // roll (x-axis rotation)
        glm::vec3 rot(0);
        double sinr_cosp = +2.0 * (mRotation.w * mRotation.x + mRotation.y * mRotation.z);
        double cosr_cosp = +1.0 - 2.0 * (mRotation.x * mRotation.x + mRotation.y * mRotation.y);
        rot.x = atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        double sinp = +2.0 * (mRotation.w * mRotation.y - mRotation.z * mRotation.x);
        if (fabs(sinp) >= 1)
            rot.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        else
            rot.y = asin(sinp);

        // yaw (z-axis rotation)
        double siny_cosp = +2.0 * (mRotation.w * mRotation.z + mRotation.x * mRotation.y);
        double cosy_cosp = +1.0 - 2.0 * (mRotation.y * mRotation.y + mRotation.z * mRotation.z);
        rot.z = atan2(siny_cosp, cosy_cosp);

        return rot;
    }

    void Transform::setDirty() {
        mDirty = true;
        for (auto child : mpEntity->mpChildList) {
            child->transform().setDirty();
        }
    }


    glm::mat4 Transform::getTransformationMatrix(bool forViewMatrix) {

        mDirty = true;
        if (mDirty) {
            mDirty = false;
            glm::mat4 rotation = rotationMat();
            glm::vec3 transform = mTransform;
            if (forViewMatrix) {
                transform.x *= -1;
                transform.y *= -1;
                transform.z *= -1;
            }
            glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform);
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), mScale);
            if(forViewMatrix){
                mModel = rotation * translate ;
            }else{
                mModel = translate * rotation * scale;
            }

            if (mpEntity->parent() != nullptr) {
                mModel = mpEntity->parent()->transform().getTransformationMatrix(forViewMatrix) * mModel;
            }
        }
        return mModel;
    }

    glm::mat4 Transform::getTransformationMatrix() {
        return getTransformationMatrix(false);
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

    glm::vec3 Transform::position() {
        return mTransform;
    }

//@TODO this is wrong for the camera
    glm::mat4 Transform::rotationMat() {
        float qw = mRotation.w;
        float qx = mRotation.x;
        float qy = mRotation.y;
        float qz = mRotation.z;

        float n = 1.0f / sqrt(qx * qx + qy * qy + qz * qz + qw * qw);
        qx *= n;
        qy *= n;
        qz *= n;
        qw *= n;
        glm::mat4 rotation(1.0f - 2.0f * qy * qy - 2.0f * qz * qz, 2.0f * qx * qy - 2.0f * qz * qw,
                           2.0f * qx * qz + 2.0f * qy * qw, 0.0f,
                           2.0f * qx * qy + 2.0f * qz * qw, 1.0f - 2.0f * qx * qx - 2.0f * qz * qz,
                           2.0f * qy * qz - 2.0f * qx * qw, 0.0f,
                           2.0f * qx * qz - 2.0f * qy * qw, 2.0f * qy * qz + 2.0f * qx * qw,
                           1.0f - 2.0f * qx * qx - 2.0f * qy * qy, 0.0f,
                           0.0f, 0.0f, 0.0f, 1.0f);
        return rotation;
    }


}
