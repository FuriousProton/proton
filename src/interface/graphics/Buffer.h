//
// Created by teeebor on 2017-10-05.
//

#pragma once


namespace proton{
    class Buffer {
    private:
        unsigned int mBufferId;
        unsigned int mComponentCount;
    public:
        Buffer(const void *data, int count, unsigned int componentCount);
        ~Buffer();

        void bind() const;
        void unbind() const;

        unsigned int getComponentCount();

    private:
        void load(const void *data, int count, unsigned int componentCount);
    };
}

