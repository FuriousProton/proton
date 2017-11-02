//
// Created by teeebor on 2017-10-30.
//

#include "IndexBuffer.h"
#include <glbinding/gl/gl.h>

namespace proton{
    using namespace gl;

    IndexBuffer::IndexBuffer(unsigned int *data, int count) {
        mCount= static_cast<unsigned int>(count);
        glGenBuffers(1,&mBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,count * sizeof(unsigned int), data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1,&mBufferID);
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mBufferID);
    }


    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }

    unsigned int IndexBuffer::getCount() {
        return mCount;
    }

    unsigned int *IndexBuffer::getData() {
        return mData;
    }
}