//
// Created by teeebor on 2017-10-25.
//

#pragma once


namespace proton {
    class Shader;
    class Component;
    class IndexBuffer;
    class VertexArray;
    class Buffer;
    class Renderer : public Component{
    private:
        Shader *mpShader;
        IndexBuffer* mpIndexBuffer;
        VertexArray* mpVertexArray;
        unsigned int renderMode;
        unsigned int mModelMatrixLocation;
    public:
        explicit Renderer(const char* shader);
        ~Renderer();
        void setModel(IndexBuffer* ibo, VertexArray* vao);
        void addBuffer(Buffer* buffer, unsigned short location);
        void setRendeMode(unsigned int renderMode);

        void render();
    };

}
