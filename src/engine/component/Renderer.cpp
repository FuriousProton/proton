//
// Created by teeebor on 2017-10-25.
//

#include "Renderer.h"
#include "Component.h"
#include "Transform.h"
#include <glbinding/gl/gl.h>
#include "../../interface/io/FileLoader.h"
#include "../../interface/graphics/Shader.h"
#include "../../interface/graphics/VertexArray.h"
#include "../../interface/graphics/IndexBuffer.h"
#include "../../interface/graphics/Buffer.h"
#include "../Scene.h"
#include "../entity/Camera.h"
#include "../../utility.h"

namespace proton{
    using namespace gl;
    Renderer::Renderer(const char *shader):Component() {
        mpShader =FileLoader::readShader(shader);
    }

    Renderer::~Renderer() {
        delete mpVertexArray;
        delete mpIndexBuffer;
        delete mpShader;
    }

    void Renderer::render() {
        mpShader->bind();
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
        //@TODO setting up additional matrices and textures
        mpShader->loadData();

        mpVertexArray->bind();
        mpIndexBuffer->bind();
        glDrawElements(static_cast<GLenum>(renderMode), mpIndexBuffer->getCount(), GL_UNSIGNED_INT, 0);

        mpShader->unbind();
        //@TODO unbinding textures

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

    void Renderer::setRendeMode(unsigned int renderMode) {
        renderMode=renderMode;
    }
}