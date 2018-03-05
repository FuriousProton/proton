//
// Created by teeebor on 2017-10-25.
//

#include "../../../include/component/Renderer.h"
#include "../../../include/component/Component.h"
#include "../../../include/component/Transform.h"
#include <glbinding/gl/gl.h>
#include "../../../include/io/FileLoader.h"
#include "../../../include/interface/Shader.h"
#include "../../../include/interface/VertexArray.h"
#include "../../../include/interface/IndexBuffer.h"
#include "../../../include/interface/Buffer.h"
#include "../../../include/Scene.h"
#include "../../../include/entity/Camera.h"
#include "../../../include/interface/Texture.h"
#include "../../../include/utility.h"

namespace proton{
    using namespace gl;
    Renderer::Renderer(const char *shader):Component() {
        mpShader =FileLoader::readShader(shader);
        mpTexture= nullptr;
    }

    Renderer::~Renderer() {
        delete mpVertexArray;
        delete mpIndexBuffer;
        delete mpShader;
    }

    void Renderer::render() {
        mpShader->bind();

        glDepthMask(GL_TRUE);
        if(Scene::activeScene){
            if(Scene::activeScene->mainCamera()){
                mpShader->loadUniformMat4f("mvp.view",Scene::activeScene->mainCamera()->getViewMatrix());
                mpShader->loadUniformMat4f("mvp.projection",Scene::activeScene->mainCamera()->getProjectionMatrix());
                mpShader->loadUniformMat4f("mvp.model",mpEntity->transform().getTransformationMatrix());
            } else{
                LOG("ERROR","No main camera added");
            }
        } else{
            LOG("ERROR","No scene loaded");
        }
        loadData();
        mpVertexArray->bind();
        mpIndexBuffer->bind();
        if(mpTexture){
            mpTexture->bind();
        }
        glDrawElements(static_cast<GLenum>(renderMode), mpIndexBuffer->getCount(), GL_UNSIGNED_INT, 0);

        mpShader->unbind();
        if(mpTexture){
            mpTexture->unbind();
        }

        mpVertexArray->unbind();
        mpIndexBuffer->unbind();
    }

    void Renderer::setModel(IndexBuffer *ibo, VertexArray *vao) {
        renderMode = (unsigned int) GL_TRIANGLES;
        mpIndexBuffer = ibo;
        mpVertexArray = vao;
    }

    void Renderer::addBuffer(Buffer *buffer, unsigned short location) {
        mpVertexArray->addBuffer(buffer,location);
    }

    void Renderer::setRendeMode(unsigned int r) {
        renderMode=r;
    }

    void Renderer::loadData() {
        for (std::pair<const char *const, Uniform *> & x : mUniforms){
            x.second->load(mpShader);
        }
    }


    void Renderer::set(const char *name, int v){
        mUniforms[name]=new Uniform1i(name, mpShader, v);
    }
    void Renderer::set(const char *name, float v){
        mUniforms[name]=new Uniform1f(name, mpShader, v);
    }
    void Renderer::set(const char *name, glm::vec2& v){
        mUniforms[name]=new Uniform2f(name, mpShader, v);
    }
    void Renderer::set(const char *name, glm::vec3& v){
        mUniforms[name]=new Uniform3f(name, mpShader, v);
    }
    void Renderer::set(const char *name, glm::vec4& v){
        mUniforms[name]=new Uniform4f(name, mpShader, v);
    }
    void Renderer::set(const char *name, glm::mat4& v){
        mUniforms[name]=new UniformMat4(name, mpShader, v);
    }

    void Renderer::setTexture(Texture *texture) {
        mpTexture=texture;
    }

}