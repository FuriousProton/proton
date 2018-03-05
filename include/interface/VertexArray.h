//
// Created by teeebor on 2017-10-30.
//

#pragma once
#include "../utility.h"

#include <vector>

namespace proton {
    class Buffer;

    class PROTON_API VertexArray {
    private:
        unsigned int mArrayID;
        std::vector<Buffer *> mBufferList;
    public:
        VertexArray();
        ~VertexArray();
        void addBuffer(Buffer *buffer, unsigned int index);
        void bind();
        void unbind();
    };
}
