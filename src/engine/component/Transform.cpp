//
// Created by teeebor on 2017-10-24.
//
#define GLM_ENABLE_EXPERIMENTAL
#include "../../../include/entity/Entity.h"

#include "../../../include/component/Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>
namespace proton {

    Transform::Transform():mTransform(glm::vec3(0,0,0)),mScale(glm::vec3(1,1,1)),mRotation(glm::vec3(0,0,0)) {
        mDirty=true;
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

/*
    void Transform::rotate(glm::quat quaternion) {
        setDirty();
        mRotation += quaternion;
    }
*/

    void Transform::rotate(glm::vec3 rotation) {
        setDirty();
        mRotation.x+=rotation.x;
        mRotation.y+=rotation.y;
        mRotation.z+=rotation.z;
        mRotation.x=(mRotation.x<0?360-mRotation.x:(mRotation.x>=360?mRotation.x-360:mRotation.x));
        mRotation.y=(mRotation.y<0?360-mRotation.y:(mRotation.y>=360?mRotation.y-360:mRotation.y));
        mRotation.z=(mRotation.z<0?360-mRotation.z:(mRotation.z>=360?mRotation.z-360:mRotation.z));
    }

    glm::vec3 Transform::rotation() {
        return mRotation;
    }
/*    glm::vec3 Transform::eulerRotation() {
        return glm::eulerAngles(mRotation);
    }*/

    void Transform::setDirty() {
        mDirty = true;
            for (auto child : mpEntity->mpChildList) {
                child->transform().setDirty();
            }
    }


    glm::mat4 Transform::getTransformationMatrix(bool reversed) {

        mDirty = true;
        if (mDirty) {
            mDirty = false;
            glm::mat4 rotation = rotationMat();
            glm::vec3 transform = mTransform;
            if(reversed){
                transform.x*=-1;
                transform.y*=-1;
                transform.z*=-1;
            }
            glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform);
            glm::mat4 scale = glm::scale(glm::mat4(1.0f),mScale);
            mModel=  translate * rotation * scale;

            if(mpEntity->parent() != nullptr){
                mModel=mpEntity->parent()->transform().getTransformationMatrix(reversed)*mModel;
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
//        return glm::rotate(glm::mat4(1.f),1.f,mRotation);
        return glm::rotate(mRotation.x,glm::vec3(1,0,0)) *
                glm::rotate(mRotation.y,glm::vec3(0,1,0))*
                glm::rotate(mRotation.z,glm::vec3(0,0,1));
    }


}
