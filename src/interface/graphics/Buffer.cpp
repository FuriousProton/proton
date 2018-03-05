//
// Created by teeebor on 2017-10-05.
//

#include <glbinding/gl/gl.h>
#include "../../../include/interface/Buffer.h"

namespace proton{
    using namespace gl;
    Buffer::Buffer(const void *data, int count, unsigned int componentCount) {
        load(data,count,componentCount);
    }

    void Buffer::load(const void *data, int count, unsigned int componentCount) {
        mComponentCount = componentCount;

        glGenBuffers(1, &mBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Buffer::~Buffer() {
        glDeleteBuffers(1,&mBufferId);
    }

    void Buffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
    }

    void Buffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    unsigned int Buffer::getComponentCount() {
        return mComponentCount;
    }
}