//
// Created by teeebor on 2017-11-29.
//

#include "../../../include/interface/Uniform.h"
void Uniform::load(proton::Shader *s) {
    LOG("ERROR","Uniform type not implemented");
}

Uniform::Uniform(const char *name, proton::Shader *s) {
    mID= static_cast<unsigned int>(s->getUniformLocation(name));
}

void Uniform1i::load(proton::Shader *s) {
    s->loadUniform1i(mID, value);
}

Uniform1i::Uniform1i(const char *name, proton::Shader *s, int v):Uniform(name, s),value(v) {}


void Uniform1f::load(proton::Shader *s) {
    s->loadUniform1f(mID, value);
}

Uniform1f::Uniform1f(const char *name, proton::Shader *s, float v):Uniform(name, s),value(v) {}

void Uniform2f::load(proton::Shader *s) {
    s->loadUniform2f(mID, value);
}

Uniform2f::Uniform2f(const char *name, proton::Shader *s, glm::vec2 &v):Uniform(name, s),value(v) {}

void Uniform3f::load(proton::Shader *s) {
    s->loadUniform3f(mID, value);
}

Uniform3f::Uniform3f(const char *name, proton::Shader *s, glm::vec3 &v):Uniform(name, s),value(v) {}

void Uniform4f::load(proton::Shader *s) {
    s->loadUniform4f(mID, value);
}

Uniform4f::Uniform4f(const char *name, proton::Shader *s, glm::vec4 &v):Uniform(name, s),value(v) {}

void UniformMat4::load(proton::Shader *s) {
    s->loadUniformMat4f(mID, value);
}

UniformMat4::UniformMat4(const char *name, proton::Shader *s, glm::mat4 &v):Uniform(name, s),value(v) {}
