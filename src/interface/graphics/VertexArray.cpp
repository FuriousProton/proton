//
// Created by teeebor on 2017-10-30.
//

#include <glbinding/gl/gl.h>
#include "VertexArray.h"
#include "Buffer.h"
namespace proton{
    using namespace gl;
    VertexArray::VertexArray() {
        glGenVertexArrays(1,&mArrayID);
    }

    VertexArray::~VertexArray() {
        delete[] mBufferList;
    }

    void VertexArray::addBuffer(Buffer *buffer, unsigned int index) {
        bind();
        buffer->bind();
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0,0,);
        buffer->unbind();
        unbind();
    }

    void VertexArray::bind() {
        glBindVertexArray(mArrayID);
    }

    void VertexArray::unbind() {
        glBindVertexArray(0);
    }


}