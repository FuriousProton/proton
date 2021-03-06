//
// Created by teeebor on 2017-10-25.
//

#pragma once

#include "../utility.h"
#include "../interface/Uniform.h"
#include <map>
#include "Component.h"
#include <glm/gtc/type_ptr.hpp>
#include <glbinding/gl/gl.h>

namespace proton {
    class Shader;

    class Component;

    class IndexBuffer;

    class VertexArray;

    class Buffer;

    class Texture;

    class PROTON_API Renderer : public Component {
    private:
        Shader *mpShader;
        std::map<const char *, Uniform *> mUniforms;
        IndexBuffer *mpIndexBuffer;
        VertexArray *mpVertexArray;
        std::vector<Texture*> mpTextures;

        GLenum renderMode;
    public:
        explicit Renderer(const char *shader);

        ~Renderer();

        void setModel(IndexBuffer *ibo, VertexArray *vao);

        void addBuffer(Buffer *buffer, unsigned short location);

        void setRendeMode(GLenum renderMode);

        void setTexture(Texture *texture, int index);
        int addTexture(Texture *texture);

        Shader *getShader() { return mpShader; }

        void calculateNormals(unsigned int *indices, int indexLen, float *vertex, int count);


        void set(const char *name, int v);

        void set(const char *name, float v);

        void set(const char *name, glm::vec2 &value);

        void set(const char *name, glm::vec3 &value);

        void set(const char *name, glm::vec4 &value);

        void set(const char *name, glm::mat4 &value);

        void render();

        void loadData();
    };

}
