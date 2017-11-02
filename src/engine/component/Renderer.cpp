//
// Created by teeebor on 2017-10-25.
//

#include "Renderer.h"
#include "Component.h"
#include <glbinding/gl/gl.h>
#include "../../interface/io/FileLoader.h"
#include "../../interface/graphics/Shader.h"
#include "../../interface/graphics/VertexArray.h"
#include "../../interface/graphics/IndexBuffer.h"
#include "../../interface/graphics/Buffer.h"

namespace proton{
    using namespace gl;
    Renderer::Renderer(const char *shader):Component() {
        mpShader =FileLoader::readShader(shader);
    }

    Renderer::~Renderer() {
        delete mpShader;
    }

    void Renderer::render() {
        mpShader->bind();
        //@TODO setting up matrices
        mpShader->loadData();

        mpVertexArray->bind();
        mpIndexBuffer->bind();


        mpShader->unbind();
        //@TODO unbinding textures

        mpVertexArray->bind();
        mpIndexBuffer->bind();
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