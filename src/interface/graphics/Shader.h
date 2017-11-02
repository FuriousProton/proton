//
// Created by teeebor on 2017-10-05.
//

#pragma once

#include <string>
#include <glbinding/gl/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <map>

namespace proton{
    using namespace gl;
    class Shader {
    private:
            unsigned int id;
            std::map<const char*,int> mUniforms;
    public:
        void load(std::string *shaders);

        void bind();
        void unbind();

        void loadData();

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
    private:
        unsigned int buildShader(std::string &content, GLenum shaderType);
        unsigned int getUniformLocation(const char *name);
    };
}

