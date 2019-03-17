//
// Created by teeebor on 2017-11-29.
//

#pragma once

#include "../utility.h"

#include <glbinding/gl/gl.h>

namespace proton{
    class Shader;
    const gl::GLenum TEXTURE_ENUMS[32]={gl::GL_TEXTURE0,gl::GL_TEXTURE1,gl::GL_TEXTURE2,gl::GL_TEXTURE3,gl::GL_TEXTURE4,gl::GL_TEXTURE5,gl::GL_TEXTURE6,gl::GL_TEXTURE7,gl::GL_TEXTURE8,gl::GL_TEXTURE9,gl::GL_TEXTURE10,gl::GL_TEXTURE11,gl::GL_TEXTURE12,gl::GL_TEXTURE13,gl::GL_TEXTURE14,gl::GL_TEXTURE15,gl::GL_TEXTURE16,gl::GL_TEXTURE17,gl::GL_TEXTURE18,gl::GL_TEXTURE19,gl::GL_TEXTURE20,gl::GL_TEXTURE21,gl::GL_TEXTURE22,gl::GL_TEXTURE23,gl::GL_TEXTURE24,gl::GL_TEXTURE25,gl::GL_TEXTURE26,gl::GL_TEXTURE27,gl::GL_TEXTURE28,gl::GL_TEXTURE29,gl::GL_TEXTURE30,gl::GL_TEXTURE31};
    class PROTON_API Texture {
    private:
        unsigned int textureID;
        gl::GLenum location;
        void *mpUniform = nullptr;
        Shader *mpShader = nullptr;
        bool useBinding;

    public:
        Texture(const char* path, int location);
        Texture(const char* path, const char* name,Shader *s, int location);
        ~Texture();
        void setTexture(const char* path);


        void bind();
        void unbind();

        unsigned int getTextureID();
    };
}

