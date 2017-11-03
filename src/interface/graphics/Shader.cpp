//
// Created by teeebor on 2017-10-05.
//

#include "Shader.h"
#include <glbinding/gl/gl.h>
#include <vector>
#include "../../utility.h"

namespace proton {
    void Shader::load(std::string *shaders) {
        using namespace gl;
        id = glCreateProgram();
        unsigned int fragID = 0;
        unsigned int vertID = 0;
        unsigned int geomID = 0;
        if (!shaders[0].empty()) {
            vertID = buildShader(shaders[0], GL_VERTEX_SHADER);
        }
        if (!shaders[1].empty()) {
            fragID = buildShader(shaders[1], GL_FRAGMENT_SHADER);
        }
        if (!shaders[2].empty()) {
            geomID = buildShader(shaders[2], GL_GEOMETRY_SHADER);
        }

        if (fragID != 0) {
            glAttachShader(id, fragID);
        }
        if (vertID != 0) {
            glAttachShader(id, vertID);
        }
        if (geomID != 0) {
            glAttachShader(id, geomID);
        }

        glLinkProgram(id);
        glValidateProgram(id);

        if (fragID != 0) {
            glDeleteShader(fragID);
        }
        if (vertID != 0) {
            glDeleteShader(vertID);
        }
        if (geomID != 0) {
            glDeleteShader(geomID);
        }
        LOG("SHADER_LOADER","Shader loaded successfully!");
    }

    unsigned int Shader::buildShader(std::string &content, GLenum shaderType) {
        using namespace gl;
        unsigned int shaderID = glCreateShader(shaderType);
        const char *source = content.c_str();

        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);

        GLint result;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
        if (!result) {
            GLint length;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(static_cast<unsigned long long int>(length));
            glGetShaderInfoLog(shaderID, length, &length, &error[0]);
            LOG("SHADER_LOADER", "Shader has errors!" << std::endl << "\t" << &error[0]);
            glDeleteShader(shaderID);
            return 0;
        }
        return shaderID;
    }

    unsigned int Shader::getUniformLocation(const char *name) {
        using namespace gl;
        if(mUniforms.find(name) == mUniforms.end()){
            mUniforms[name]=glGetUniformLocation(id,name);
        }
        LOG("SHADER_LOADER", "Requesting uniform "<<name<<" (#"<<mUniforms[name]<<")");
        return static_cast<unsigned int>(mUniforms[name]);
    }


    void Shader::loadUniform1f(unsigned int location, float value) {
        glUniform1f(location, value);
    }

    void Shader::loadUniform1i(unsigned int location, int value) {
        glUniform1i(location, value);
    }

    void Shader::loadUniform2f(unsigned int location, const glm::vec2& value) {
        glUniform2f(location, value.x, value.y);
    }

    void Shader::loadUniform3f(unsigned int location, const glm::vec3& value) {
        glUniform3f(location, value.x, value.y, value.z);
    }

    void Shader::loadUniform4f(unsigned int location, const glm::vec4& value) {
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Shader::loadUniformMat4f(unsigned int location, const glm::mat4& uniform) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }

    void Shader::loadUniformMat4f(unsigned int location, glm::mat4& uniform) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }

    void Shader::loadUniform1f(const char *name, float value) {
        loadUniform1f(getUniformLocation(name), value);
    }

    void Shader::loadUniform1i(const char *name, int value) {
        loadUniform1i(getUniformLocation(name), value);
    }

    void Shader::loadUniform2f(const char *name, const glm::vec2& value) {
        loadUniform2f(getUniformLocation(name), value);
    }

    void Shader::loadUniform3f(const char *name, const glm::vec3& value) {
        loadUniform3f(getUniformLocation(name), value);
    }

    void Shader::loadUniform4f(const char *name, const glm::vec4& value) {
        loadUniform4f(getUniformLocation(name), value);
    }

    void Shader::loadUniformMat4f(const char *name, const glm::mat4& uniform) {
        loadUniformMat4f(getUniformLocation(name),uniform);
    }
    void Shader::loadUniformMat4f(const char *name, glm::mat4& uniform) {
        loadUniformMat4f(getUniformLocation(name), uniform);
    }

    void Shader::bind() {
        glUseProgram(id);
    }
    void Shader::unbind() {
        glUseProgram(0);
    }

    void Shader::loadData() {
        LOG("SHADER_ERR","NOT IMPLEMENTED");
    }
}