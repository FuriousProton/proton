//
// Created by teeebor on 2017-10-05.
//

#pragma once

#include "../utility.h"

#include <glbinding/gl/gl.h>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace proton{
    struct PROTON_API UniformData{
        const char* key;
        int ID;
        UniformData(const char* _key,int _id):key(_key),ID(_id){};
    };

    using namespace gl;
    class Shader {
    private:
            unsigned int id;
            std::vector<UniformData*> mUniforms;
    public:

        Shader();
        void load(std::string *shaders);

        void bind();
        void unbind();


        void loadUniform1f(const char *name, float value);
        void loadUniform1i(const char *name, int value);

        void loadUniform2f(const char *name, const glm::vec2& value);
        void loadUniform3f(const char *name, const glm::vec3& value);
        void loadUniform4f(const char *name, const glm::vec4& value);

        void loadUniformMat4f(const char *name, const glm::mat4& uniform);
        void loadUniformMat4f(const char *name, glm::mat4& uniform);

        void loadUniform1f(unsigned int location, float value);
        void loadUniform1i(unsigned int location, int value);

        void loadUniform2f(unsigned int location, const glm::vec2& value);
        void loadUniform3f(unsigned int location, const glm::vec3& value);
        void loadUniform4f(unsigned int location, const glm::vec4& value);

        void loadUniformMat4f(unsigned int location, const glm::mat4& uniform);
        void loadUniformMat4f(unsigned int location, glm::mat4& uniform);

        int getUniformLocation(const char *name);

    private:
        unsigned int buildShader(std::string &content, gl::GLenum shaderType);
    };
}

