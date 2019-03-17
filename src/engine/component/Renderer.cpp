//
// Created by teeebor on 2017-10-25.
//

#include <glbinding/gl/gl.h>

#include "../../../include/component/Renderer.h"
#include "../../../include/component/Component.h"
#include "../../../include/component/Transform.h"
#include "../../../include/io/FileLoader.h"
#include "../../../include/interface/Shader.h"
#include "../../../include/interface/VertexArray.h"
#include "../../../include/interface/IndexBuffer.h"
#include "../../../include/interface/Buffer.h"
#include "../../../include/Scene.h"
#include "../../../include/entity/Camera.h"
#include "../../../include/interface/Texture.h"
#include "../../../include/utility.h"

namespace proton {
    using namespace gl;

    Renderer::Renderer(const char *shader) : Component() {
        mpShader = FileLoader::readShader(shader);
    }

    Renderer::~Renderer() {
        delete mpVertexArray;
        delete mpIndexBuffer;
        delete mpShader;
    }

    void Renderer::render() {
        mpShader->bind();

        glDepthMask(1);
        if (Scene::activeScene) {
            if (Scene::activeScene->mainCamera()) {
                mpShader->loadUniformMat4f("mvp.view", Scene::activeScene->mainCamera()->getViewMatrix());
                mpShader->loadUniformMat4f("mvp.projection", Scene::activeScene->mainCamera()->getProjectionMatrix());
                mpShader->loadUniformMat4f("mvp.model", mpEntity->transform().getTransformationMatrix());
            } else {
                LOG("ERROR", "No main camera added");
            }
        } else {
            LOG("ERROR", "No scene loaded");
        }
        loadData();
        mpVertexArray->bind();
        mpIndexBuffer->bind();
        for(auto t : mpTextures){
            t->bind();
        }
        glDrawElements(renderMode, mpIndexBuffer->getCount(), GL_UNSIGNED_INT, 0);

        mpShader->unbind();
        for(auto t : mpTextures){
            t->unbind();
        }

        mpVertexArray->unbind();
        mpIndexBuffer->unbind();
    }

    void Renderer::setModel(IndexBuffer *ibo, VertexArray *vao) {
        renderMode = GL_TRIANGLES;
        mpIndexBuffer = ibo;
        mpVertexArray = vao;
    }

    void Renderer::addBuffer(Buffer *buffer, unsigned short location) {
        mpVertexArray->addBuffer(buffer, location);
    }

    void Renderer::setRendeMode(GLenum r) {
        renderMode = r;
    }

    void Renderer::loadData() {
        for (std::pair<const char *const, Uniform *> &x : mUniforms) {
            x.second->load(mpShader);
        }
    }


    void Renderer::set(const char *name, int v) {
        mUniforms[name] = new Uniform1i(name, mpShader, v);
    }

    void Renderer::set(const char *name, float v) {
        mUniforms[name] = new Uniform1f(name, mpShader, v);
    }

    void Renderer::set(const char *name, glm::vec2 &v) {
        mUniforms[name] = new Uniform2f(name, mpShader, v);
    }

    void Renderer::set(const char *name, glm::vec3 &v) {
        mUniforms[name] = new Uniform3f(name, mpShader, v);
    }

    void Renderer::set(const char *name, glm::vec4 &v) {
        mUniforms[name] = new Uniform4f(name, mpShader, v);
    }

    void Renderer::set(const char *name, glm::mat4 &v) {
        mUniforms[name] = new UniformMat4(name, mpShader, v);
    }

    void Renderer::setTexture(Texture *texture, int index) {
        if(mpTextures.size()<index){
            mpTextures[index] = texture;
        }
    }
    int Renderer::addTexture(Texture *texture){
        int id = mpTextures.size();
        mpTextures.push_back(texture);
        return id;
    }


    void Renderer::calculateNormals(unsigned int *indices, int indexLen, float* vertex, int count) {
        using namespace glm;
//        auto *vertex = static_cast<float *>(mpVertexArray->getBuffer(0)->getData());
        float *normals;
        normals = static_cast<float *>(calloc(count, sizeof(float)));
        for (int i = 0; i < indexLen; i += 3) {
            auto indexA = indices[i];
            auto indexB = indices[i + 1];
            auto indexC = indices[i + 2];
            vec3 vertexA(vertex[indexA * 3], vertex[indexA * 3 + 1], vertex[indexA * 3 + 2]);
            vec3 vertexB(vertex[indexB * 3], vertex[indexB * 3 + 1], vertex[indexB * 3 + 2]);
            vec3 vertexC(vertex[indexC * 3], vertex[indexC * 3 + 1], vertex[indexC * 3 + 2]);
            vec3 p = cross(vertexB - vertexA, vertexC - vertexA);

            normals[indexA*3] += p.x;
            normals[indexA*3+1] += p.y;
            normals[indexA*3+2] += p.z;

            normals[indexB*3] += p.x;
            normals[indexB*3+1] += p.y;
            normals[indexB*3+2] += p.z;

            normals[indexB*3] += p.x;
            normals[indexB*3+1] += p.y;
            normals[indexB*3+2] += p.z;
        }
        for (int i = 0; i < count; i +=3) {
            vec3 ve(normals[i], normals[i+1], normals[i+2]);
            ve = normalize(ve);
            normals[i] = ve.x;
            normals[i+1] = ve.y;
            normals[i+2] = ve.z;
        }

        auto *normalBuffer = new Buffer(normals, count, 3);
        mpVertexArray->addBuffer(normalBuffer, 1);
    }

}