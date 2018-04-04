//
// Created by teeebor on 2017-11-03.
//

#include <glbinding/gl/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../../../include/entity/Camera.h"
#include "../../../include/component/Transform.h"
#include "../../../include/Scene.h"
#include "../../../include/utility.h"

namespace proton {
    using namespace gl;


    Camera::Camera(float frameWidth, float frameHeight, float fov, float near, float far)
            :mFrameWidth(frameWidth), mFrameHeight(frameHeight), mFov(fov), mNear(near), mFar(far) {
        createProjectionMatrix();
        if(Scene::activeScene){
            Scene::activeScene->addCamera(this);
        }
        glEnable(GL_DEPTH_TEST);
    }

    glm::mat4 Camera::getViewMatrix() {
        glm::mat4 rotationMat = mpTransform->rotationMat();
        glm::mat4 transform = mpTransform->getTransformationMatrix(true);
        return transform;
    }

    void Camera::createProjectionMatrix() {
        float aspectRatio = mFrameWidth / mFrameHeight;
        mProjectionMatrix = glm::perspective(mFov, aspectRatio, mNear, mFar);
    }

    void Camera::setCulling(bool enabled) {
        if (enabled) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        } else {
            glDisable(GL_CULL_FACE);
        }
    }

    void Camera::setBlend(bool enabled) {
        if (enabled) {
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }
    }

    glm::mat4 Camera::getProjectionMatrix() {
        return mProjectionMatrix;
    }

    Camera::~Camera() {

    }

    void Camera::setup() {
        Entity::setup();
    }

}