//
// Created by teeebor on 2017-11-03.
//

#include <glbinding/gl/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "../component/Transform.h"
#include "../Scene.h"
#include "../../utility.h"

namespace proton {
    using namespace gl;


    Camera::Camera(float frameWidth, float frameHeight, float fov, float near, float far)
            :mFrameWidth(frameWidth), mFrameHeight(frameHeight), mFov(fov), mNear(near), mFar(far) {
        createProjectionMatrix();

    }

    glm::mat4 Camera::getViewMatrix() {
        glm::mat4 rotationMat = mpTransform->rotationMat();

        glm::vec3 pos = mpTransform->position();
        pos.x*=-1;
        pos.y*=-1;
        pos.z*=-1;
        return glm::translate(glm::mat4(1.0f), pos) * rotationMat;
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