//
// Created by teeebor on 2017-10-30.
//

#pragma once
#include "../utility.h"

namespace proton {
    class PROTON_API IndexBuffer {
    private:
        unsigned int mBufferID;
        unsigned int mCount;
        unsigned int *mData;
    public:
        IndexBuffer(unsigned int *data, int count);

        ~IndexBuffer();

        void bind() const;

        void unbind() const;


        unsigned int getCount();

        unsigned int *getData();
    };
}

