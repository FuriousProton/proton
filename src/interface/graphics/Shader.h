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

        void loadUniform1f(const GLchar *name, float value);
        void loadUniform1i(const char *name, int value);

        void loadUniform2f(const GLchar *name, const glm::vec2& value);
        void loadUniform3f(const GLchar *name, const glm::vec3& value);
        void loadUniform4f(const GLchar *name, const glm::vec4& value);

        void loadUniformMat4f(const GLchar *name, const glm::mat4& uniform);
        void loadUniformMat4f(const GLchar *name, glm::mat4& uniform);

        void loadUniform1f(GLuint location, float value);
        void loadUniform1i(GLuint location, int value);

        void loadUniform2f(GLuint location, const glm::vec2& value);
        void loadUniform3f(GLuint location, const glm::vec3& value);
        void loadUniform4f(GLuint location, const glm::vec4& value);

        void loadUniformMat4f(GLuint location, const glm::mat4& uniform);
        void loadUniformMat4f(GLuint location, glm::mat4& uniform);
    private:
        unsigned int buildShader(std::string &content, GLenum shaderType);
        GLuint getUniformLocation(const char *name);
    };
}

